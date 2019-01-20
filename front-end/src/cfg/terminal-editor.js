import React from 'react';
import Terminal from './terminal';

class TerminalEditor extends React.Component {
    constructor(props) {
        super(props);

        this.refCollection = [];
        this.propagateUpdate = props.propagateUpdate;
        this.state = {
            error: '',
            terminals: [],
        };
    }

    getObject = () => {
        var terminalNames = {};
        var errorDescription = '';
        var data = [];

        this.refCollection.forEach((ref, index) => {
            ref.evaluate(() => {});
        });

        var i = 0;
        var ref = null;
        for(i = 0; i < this.refCollection.length; i++) {
            ref = this.refCollection[i];
            var isValid = ref.isValid();
            var child = ref.getObject();
            data.push(child);
            if(isValid !== '' || child['error'] !== undefined) {
                errorDescription = child['error'];
            }
        }

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            return {
                error: errorDescription
            };
        }

        for(i = 0; i < this.refCollection.length; i++) {
            ref = this.refCollection[i];
            if(ref.state.name in terminalNames) {
                terminalNames[ref.state.name].push(i);
                errorDescription = 'Two Terminals cannot share the same name.';
            } else {
                terminalNames[ref.state.name] = [i];
            }
        }

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            // we want to highlight the bad ones
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

    addTerminal = () => {
        this.refCollection.push(null);
        this.state.terminals.push(<Terminal ref={(instance) => { this.refCollection[this.refCollection.length - 1] = instance; }} propagateUpdate={this.propagateUpdate} key={this.state.terminals.length} index={this.state.terminals.length} />);
        
        this.forceUpdate(() => {
            this.propagateUpdate();
        });
    }

    render() {
        var errorMessage;
        if(this.state.error.length !== 0) {
            errorMessage = (
                <div className="error-message">
                    {this.state.error}
                </div>
            )
        }

        return (
            <div className="terminal-editor">
                <div className="header">
                    <h1>Terminal Definitions:</h1>
                    Here you define the structure of the context free grammar. You can reference the tokens
                    declared in the "Declared Tokens" section by name. Each terminal has a set of expressions
                    which define all possible forms of the terminal. Ensure that the expressions you provide
                    are recursive descent friendly to ensure a working parser.
                    To define an expression, reference each token with TOKEN:TokenName, each terminal with
                    TERMINAL:TerminalName, and each implied token as written. Note that all whitespace will
                    be ignored once the tokenizer is generated.
                    <br></br>
                    <button onClick={this.addTerminal}>Add a terminal</button>
                </div>
                {errorMessage}
                <div className="body">
                    {this.state.terminals}
                </div>
            </div>
        );
    }
}

export default TerminalEditor;