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
        if(this.state.error !== '') {
            return {
                error: this.state.error
            };
        } else {
            return {
                name: this.state.name,
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