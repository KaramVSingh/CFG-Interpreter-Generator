import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';

class Token extends React.Component {
    constructor(props) {
        super(props);
        this.index = props.index;
        this.callback = props.callback;

        this.state = {
            name: '',
            regex: '',
            delimiting: false,
            error: true,
        };
    }

    updateName(evt) {
        this.setState({
            name: evt.target.value,
        }, () => {
            this.evaluate();
        });
    }

    updateRegex(evt) {
        this.setState({
            regex: evt.target.value,
        }, () => {
            this.evaluate();
        });
    }

    updateDelimiting() {
        this.setState({
            delimiting: !this.state.delimiting,
        }, () => {
            this.evaluate();
        });
    }

    evaluate = () => {
        if(this.state.name === '' || this.state.regex === '') {
            this.setState({
                error: true
            }, () => {
                this.callback(this.state.name, this.index);
            });
        } else {
            this.setState({
                error: false
            }, () => {
                this.callback(this.state.name, this.index);
            });
        }

        this.forceUpdate();
    }

    cleanRegex = () => {
        var start = 0;
        var end = this.state.regex.length;
        while(this.state.regex[start] === '^') {
            start = start + 1;
        }

        while(this.state.regex[end - 1] === '$' && this.state.regex[end - 2] !== '\\') {
            end = end - 1;
        }

        this.setState({
            regex: this.state.regex.slice(start, end),
        });
    }

    styleForError() {
        if(this.state.error) {
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
            <div className="token" style={this.styleForError()}>
                Delimiting: <input type="checkbox" onChange={evt => this.updateDelimiting()}></input>
                Name: <input type="text" value={this.state.name} onChange={evt => this.updateName(evt)}></input>
                Regular Expression: <input type="text" onBlur={this.cleanRegex} value={this.state.regex} onChange={evt => this.updateRegex(evt)}></input>
            </div>
        );
    }
}

class TokenEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            tokens: [],
            names: [],
            error: false
        };
    }

    addToken = () => {
        this.state.tokens.push(<Token key={this.state.tokens.length} index={this.state.tokens.length} callback={this.updateEditorName}/>);
        this.state.names.push('');
        this.forceUpdate();
    }

    updateEditorName = (name, index) => {
        var tempNames = this.state.names;
        tempNames[index] = name;
        this.setState({
            names: tempNames,
        }, () => {
            var tempHash = {};
            var foundError = false;
            this.state.names.forEach((value) => {
                if(value in tempHash) {
                    // we have an error
                    foundError = true;
                    this.setState({
                        error: true
                    });
                } else {
                    tempHash[value] = true;
                }
            });

            if(!foundError) {
                this.setState({
                    error: false
                });
            }
        });
    }
    
    render() {
        var errorMessage;
        if(this.state.error) {
            errorMessage = (
                <div className="error-message">
                    Two tokens cannot share the same name.
                </div>
            )
        }

        return (
            <div className="token-editor">
                <div className="header">
                    <h1>Declared Tokens:</h1>
                    A token can be referenced in a Non-terminal expression. They are referenced by name
                    and have a corresponding regular expression which defines the structure of the token.
                    They are prioritized in-order so ensure that any overlapping regular expressions are 
                    sorted properly.
                    <button onClick={this.addToken}>Add a token</button>
                </div>
                {errorMessage}
                <div className="body">
                    {this.state.tokens}
                </div>
            </div>
        );
    }
}

class CfgEditor extends React.Component {
    render() {
        return (
            <div className="cfg-editor">
                <div className="header">
                    <h1>Context Free Grammar Editor:</h1>
                    Please ensure that the context free grammar is <i>Recursive Descent friendly</i>.
                    For more information on how this affects the grammar click here.
                </div>
                <div className="body">
                    <TokenEditor />
                </div>
            </div>
        );
    }
}
  
ReactDOM.render(
    <CfgEditor />,
    document.getElementById('root')
);
  