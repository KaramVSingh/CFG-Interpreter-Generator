import React from 'react';
import TokenEditor from './token-editor';
import TerminalEditor from './terminal-editor';

class CfgEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            cfg: {},
            name: '',
            canContinue: false,
            start: '',
        };
    }

    propagateUpdate = () => {
        this.setState({
            cfg: this.getObject(),
        });
    }

    getObject = () => {
        var terminalNames = {};
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
                terminalNames[terminalEditor[i].name] = true;
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

            if(this.state.name === '' || this.state.name.includes(';') || this.state.name.includes('&') || this.state.name.includes('|')) {
                this.setState({
                    canContinue: false,
                });

                return;
            }

            if(terminalNames[this.state.start] === undefined) {
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
        var name = evt.target.value.replace(/\s+/g, '');
        this.setState({
            name: name,
        }, () => {
            this.propagateUpdate();
        });
    }

    updateStart(evt) {
        this.setState({
            start: evt.target.value,
        }, () => {
            this.propagateUpdate();
        });
    }

    submit = () => {
        var data = {
            name: this.state.name, 
            start: this.state.start,
            cfg: this.state.cfg
        };

        console.log(JSON.stringify(data))

        const request = new Request('http://localhost:8080/api/', {
            'method': 'POST',
            mode: "cors", // no-cors, cors, *same-origin
            cache: "no-cache", // *default, no-cache, reload, force-cache, only-if-cached
            credentials: "same-origin", // include, *same-origin, omit
            headers: {
                "Content-Type": "application/json",
                // "Content-Type": "application/x-www-form-urlencoded",
            },
            redirect: "follow", // manual, *follow, error
            'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.109 Safari/537.36',
            'Access-Control-Allow-Origin' : '*',
            "Access-Control-Allow-Methods": "GET, POST, DELETE, PUT",
            referrer: "no-referrer", // no-referrer, *client*
            body: JSON.stringify(data)
        });

        fetch(request);
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
                    <h2>Specifics:</h2>
                    <table>
                        <tbody>
                            <tr>
                                <td>
                                    Grammar Name:
                                </td>
                                <td>
                                    <input type="text" value={this.state.name} onChange={evt => this.updateName(evt)}></input>
                                </td>
                            </tr>
                            <tr>
                                <td>
                                    First Terminal:
                                </td>
                                <td>
                                    <input type="text" value={this.state.start} onChange={evt => this.updateStart(evt)}></input>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <TokenEditor propagateUpdate={this.propagateUpdate} ref="tokenEditor" />
                    <TerminalEditor propagateUpdate={this.propagateUpdate} ref="terminalEditor" />
                    <button className="continue" disabled={!this.state.canContinue} onClick={this.submit}>Continue</button>
                </div>
            </div>
        );
    }
}

export default CfgEditor;