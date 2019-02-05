import React from 'react';
import TokenEditor from './token-editor';
import TerminalEditor from './terminal-editor';

class CfgEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            cfg: {},
            name: '',
            canContinue: false
        };
    }

    propagateUpdate = () => {
        this.setState({
            cfg: this.getObject(),
        });
    }

    getObject = () => {
        var tokenEditor = this.refs.tokenEditor.getObject();
        var terminalEditor = this.refs.terminalEditor.getObject();
        if(tokenEditor['error'] !== undefined || terminalEditor['error'] !== undefined) {
            // we have an error
            this.setState({
                canContinue: false
            });

            return;
        } else {
            // here we need to check that each token declared in the terminals exists in the declared tokens
            for(var i = 0; i < terminalEditor.length; i++) {
                // for each terminal
                for(var j = 0; j < terminalEditor[i]['data'].length; j++) {
                    var expression = terminalEditor[i]['data'][j]
                    for(var k = 0; k < expression.length; k++) {
                        var curr = expression[k];

                        if(curr['type'] === "DECLARED TOKEN") {
                            // we need to check the tokens
                            var found = false;
                            for(var l = 0; l < tokenEditor.length; l++) {
                                if(tokenEditor[l]['name'] === curr['value']) {
                                    found = true;
                                }
                            }

                            if(!found) {
                                // we have an unreferenced error
                                this.refs.terminalEditor.setState({
                                    error: 'Use of undeclared token ' + curr['value'] + '.'
                                });

                                this.setState({
                                    canContinue: false,
                                });

                                return;
                            }
                        }
                    }
                }
            }

            if(this.state.name === '') {
                this.setState({
                    canContinue: false,
                });

                return;
            }

            this.setState({
                canContinue: true
            });

            return {
                tokens: tokenEditor,
                terminals: terminalEditor
            };
        }
    }

    updateName(evt) {
        this.setState({
            name: evt.target.value,
        }, () => {
            this.propagateUpdate();
        });
    }

    submit() {
        
    }

    render() {
        return (
            <div className="cfg-editor">
                <div className="header">
                    <h1>Context Free Grammar Editor:</h1>
                    Please ensure that the context free grammar is <i>Recursive Descent friendly</i>.
                    For more information on how this affects the grammar click here.
                </div>
                <div className="body">
                    <h2>Grammar Name:</h2><input type="text" value={this.state.name} onChange={evt => this.updateName(evt)}></input>
                    <TokenEditor propagateUpdate={this.propagateUpdate} ref="tokenEditor" />
                    <TerminalEditor propagateUpdate={this.propagateUpdate} ref="terminalEditor" />
                    <button className="continue" disabled={!this.state.canContinue} onClick={this.submit}>Continue</button>
                </div>
            </div>
        );
    }
}

export default CfgEditor;