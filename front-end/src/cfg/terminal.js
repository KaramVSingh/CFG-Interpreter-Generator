import React from 'react';
import Expression from './expression';

class Terminal extends React.Component {
    constructor(props) {
        super(props);

        this.index = props.index;
        this.propagateUpdate = props.propagateUpdate;
        this.refCollection = [];
        this.getFirst = props.getFirst;
        this.state = {
            name: '',
            error: 'Must provide name for terminal.',
            expressions: []
        };
    }

    first = () => {
        // should get the first of every expression:
        var data = []
        for(var i = 0; i < this.refCollection.length; i++) {
            data.push(this.refCollection[i].first());
        }

        return data;
    }

    addExpression = () => {
        this.refCollection.push(null);
        var expressions = this.state.expressions;
        expressions.push(<Expression ref={(instance) => { this.refCollection[this.refCollection.length - 1] = instance; }} propagateUpdate={this.propagateUpdate} key={this.state.expressions.length} index={this.state.expressions.length} />);
        this.setState({
            expressions: expressions
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    removeExpression = () => {
        var expressions = this.state.expressions;
        expressions.pop();
        this.setState({
            expressions: expressions
        }, () => {
            this.refCollection.pop();
            this.evaluate(this.propagateUpdate);
        });        
    }

    checkOverlap = (setA, setB) => {
        for(var i = 0; i < setA.length; i++) {
            for(var j = 0; j < setB.length; j++) {
                if(setA[i]['type'] === setB[j]['type'] && setA[i]['value'] === setB[j]['value']) {
                    return true;
                }
            }
        }

        return false;
    }

    getObject = () => {
        // first we need to check the terminal related errors
        if(this.isValid() !== '') {
            return {
                error: this.isValid()
            };
        }

        var errorDescription = '';
        var data = [];

        this.refCollection.forEach((ref) => {
            ref.evaluate(() => {});
        });

        var i = 0;
        var ref = null;
        for(i = 0; i < this.refCollection.length; i++) {
            ref = this.refCollection[i];
            var isValid = ref.isValid();
            data.push(ref.getObject());
            if(isValid !== '') {
                errorDescription = ref.getObject()['error'];
            }
        };

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            return {
                error: errorDescription
            };
        }

        var checkedExpressions = []
        for(i = 0; i < this.refCollection.length; i++) {
            // we need to check for expression based errors.
            var expression = this.refCollection[i].getObject();
            // we need to make sure that (1) the firsts are either different
            // of that (2) if they are the same, the terminals are the same

            // each ref is an expression. we can analyse the terminal expressions
            // we can look at the first of each expression unless its a terminal
            var j;
            for(j = 0; j < checkedExpressions.length; j++) {
                // now we need to compare the two expressions
                var expressionA = expression;
                var expressionB = checkedExpressions[j];

                var depth = 0;
                while(depth <= expressionA.length && depth <= expressionB.length) {
                    if(depth === expressionA.length || depth === expressionB.length) {
                        // we have an ambiguous grammar
                        errorDescription = 'Recursive Descent Error: Completely ambiguous expressions.';
                        break;
                    } 

                    if(expressionA[depth]['type'] !== expressionB[depth]['type'] || 
                    expressionA[depth]['value'] !== expressionB[depth]['value'] || 
                    expressionA[depth]['type'] !== 'TERMINAL') {
                        break;
                    }
                    
                    depth++;
                }

                if(errorDescription !== '') {
                    // we had an error in the above step
                    break;
                }

                // if were here then we have eliminated the equal firsts cases
                var firstA = expressionA[depth];
                var firstB = expressionB[depth];

                if(firstA['type'] === 'TERMINAL' || firstB['type'] === 'TERMINAL') {
                    if(firstA['type'] === 'TERMINAL' && firstB['type'] === 'TERMINAL') {
                        // we have two different terminals
                        // in this case we just want to check that the firsts have no overlap
                        if(this.checkOverlap(this.getFirst(firstA['value'], []), this.getFirst(firstB['value'], []))) {
                            errorDescription = 'Recursive Descent Error: First case overlap for expression with terminals ' + firstA['value'] + ' and ' + firstB['value'] + '.';
                            break;
                        }
                    } else if(firstA['type'] === 'TERMINAL') {
                        // we have only A as the terminal
                        if(this.checkOverlap(this.getFirst(firstA['value'], []), [firstB])) {
                            errorDescription = 'Recursive Descent Error: Token ' + firstB['value'] + ' exists in terminal ' + firstA['value'] + '.';
                            break;
                        }
                    } else {
                        // we have only B as the terminal
                        if(this.checkOverlap(this.getFirst(firstB['value'], []), [firstA])) {
                            errorDescription = 'Recursive Descent Error: Token ' + firstA['value'] + ' exists in terminal ' + firstB['value'] + '.';
                            break;
                        }
                    }
                } else {
                    if(firstA['type'] === firstB['type'] && firstA['value'] === firstB['value']) {
                        errorDescription = 'Recursive Descent Error: Token ' + firstA['value'] + ' is ambiguous.';
                        break;
                    }
                }
            }

            checkedExpressions.push(expression);
            if(errorDescription !== '') {
                break;
            }

        }

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            return {
                error: errorDescription
            };
        } else {
            this.setState({
                error: ''
            });

            return {
                name: this.state.name,
                data: data
            };
        }
    }

    updateName(evt) {
        this.setState({
            name: evt.target.value,
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    isValid = () => {
        if(this.state.name === '') {
            return 'Must provide name for terminal.';
        }

        if(!this.state.name.match(/^[a-zA-Z_]+$/)) {
            return 'Name can only contain A-Z, a-z, and _.';
        }

        if(this.state.expressions.length === 0) {
            return 'must have at least one expression.';
        }

        return '';
    }

    evaluate = (callback) => {
        this.setState({
            error: this.isValid()
        }, () => {
            callback();
        });
    }

    styleForError() {
        if(this.state.error !== '') {
            return {
                background: 'salmon'
            };
        } else {
            return {
                background: 'lightGrey'
            };
        }
    }

    render() {
        return (
            <div className="terminal" style={this.styleForError()}>
                <table>
                    <tbody>
                        <tr>
                            <td>
                                Name: <input type="text" value={this.state.name} onChange={evt => this.updateName(evt)}></input>
                                <br></br><button onClick={this.addExpression}>Add</button><button onClick={this.removeExpression}>Remove</button>
                            </td>
                            <td>
                                {this.state.expressions}
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        );
    }
}

export default Terminal