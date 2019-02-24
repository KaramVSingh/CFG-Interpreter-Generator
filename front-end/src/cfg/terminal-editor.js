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

    first = (terminalName, visited) => {
        // we have the correct terminal, now we just need to write the dynamic function
        var ref = null;
        for(var i = 0; i < this.refCollection.length; i++) {
            if(this.refCollection[i].state.name === terminalName) {
                ref = this.refCollection[i];
            }
        }

        if(ref === null) {
            return {
                error: 'terminal: ' + terminalName + ' not found.'
            };
        };

        var firsts = ref.first();
        visited.push(terminalName);
        var results = [];
        
        for(i = 0; i < firsts.length; i++) {
            if(firsts[i].type === 'TERMINAL') {
                // we have to check that we have been here before
                for(var j = 0; j < visited.length - 1; j++) {
                    if(visited[j] === terminalName) {
                        console.log(visited)
                        var errorMessage = 'Grammar has "first loop" with: ';
                        for(var k = 0; k < visited.length; k++) {
                            errorMessage += '[ ' + visited[k] + ' ] -> ';
                        }
                        return {
                            error: errorMessage
                        };
                        // if we revisit the same place then we have a non
                        // recursive descent friendly grammar
                    }
                }

                // now we know that we are not in a loop
                var newVisited = []
                for(j = 0; j < visited.length; j++) {
                    newVisited.push(visited[j]);
                }

                var call = this.first(firsts[i].value, newVisited);
                if(call['error'] !== undefined) {
                    return {
                        error: call['error']
                    };
                }

                for(j = 0; j < call.length; j++) {
                    var add = true;
                    for(k = 0; k < results.length; k++) {
                        if(call[j].type === results[k].type && call[j].value === results[k].value) {
                            add = false;
                        }
                    }

                    if(add) {
                        results.push(call[j]);
                    }
                }
            } else {
                // if we have an implied or declared token
                add = true;
                for(j = 0; j < results.length; j++) {
                    if(results[j].type === firsts[i].type && results[j].value === firsts[i].value) {
                        add = false;
                    }
                }

                if(add) {
                    results.push(firsts[i]);
                }
            }
        }

        return results;
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

        for(i = 0; i < data.length; i++) {
            var checkError = this.first(data[i].name, []);
            if(checkError['error'] !== undefined) {
                errorDescription = checkError['error'];
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
            // now we need to ensure that each expression is using valid terminals
            // we already have terminal names to help
            for(var j = 0; j < data.length; j++) {
                // data has each terminal. we need each expression
                for(var k = 0; k < data[j]['data'].length; k++) {
                    // now we have each expression
                    var expression = data[j]['data'][k];
                    for(var l = 0; l < expression.length; l++) {
                        // now we have each curr
                        var curr = expression[l];
                        if(curr['type'] === 'TERMINAL') {
                            // then we need to check
                            if(terminalNames[curr['value']] === undefined) {
                                // we have a bad terminal use
                                errorDescription = 'Use of undeclared terminal ' + curr['value'] + '.'
                                this.setState({
                                    error: errorDescription
                                });

                                return {
                                    error: errorDescription
                                };
                            }
                        }
                    }

                }
            }


            this.setState({
                error: ''
            });

            return data;
        }
    }

    addTerminal = () => {
        this.refCollection.push(null);
        this.state.terminals.push(<Terminal getFirst={this.first} ref={(instance) => { this.refCollection[this.refCollection.length - 1] = instance; }} propagateUpdate={this.propagateUpdate} key={this.state.terminals.length} index={this.state.terminals.length} />);
        
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