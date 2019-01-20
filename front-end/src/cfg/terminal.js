import React from 'react';
import Expression from './expression';

class Terminal extends React.Component {
    constructor(props) {
        super(props);

        this.index = props.index;
        this.propagateUpdate = props.propagateUpdate;
        this.refCollection = [];
        this.state = {
            name: '',
            error: 'Must provide name for terminal.',
            expressions: []
        };
    }

    addExpression = () => {
        this.refCollection.push(null);
        this.state.expressions.push(<Expression ref={(instance) => { this.refCollection[this.refCollection.length - 1] = instance; }} propagateUpdate={this.propagateUpdate} key={this.state.expressions.length} index={this.state.expressions.length} />);
        
        this.evaluate(this.propagateUpdate);
    }

    removeExpression = () => {
        this.refCollection.pop();
        this.state.expressions.pop();
        
        this.evaluate(this.propagateUpdate);
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

        for(i = 0; i < this.refCollection.length; i++) {
            // we need to check for expression based errors.
        }

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            // we want to highlight the bad ones
            /*
            var tempCollection = this.refCollection;
            Object.keys(terminalNames).forEach(function(name) {
                if(terminalNames[name].length !== 1) {
                    terminalNames[name].forEach((index) => {
                        tempCollection[index].setState({
                            error: true
                        });
                    });
                }
            });
            */

            return {
                error: errorDescription
            };
        } else {
            this.setState({
                error: ''
            });

            return data;
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