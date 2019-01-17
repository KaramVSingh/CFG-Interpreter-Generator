import React from 'react';
import Token from './token';

class TokenEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            tokens: [],
            data: {
                error: false,
                tokens: []
            },
            update: props.callback,
        };
    }

    checkNameRepeatError() {
        var hist = {}
        var error = false;
        this.state.data.tokens.forEach((token) => {
            if(token.name in hist) {
                error = true;
            }

            hist[token.name] = true;
        });

        return error;
    }

    updateToken = (id, name, regex, delimiter, error) => {
        var temp = this.state.data.tokens;
        temp[id] = {
            name: name,
            regex: regex,
            delimiter: delimiter,
            error: error,
        };

        // if any of the tokens have an error or the tokens have the same name
        var globalError = false;

        temp.forEach((token) => {
            globalError = globalError || token.error;
        });

        globalError = globalError || this.checkNameRepeatError();

        this.setState({
            data: {
                error: globalError,
                tokens: temp,
            },
        }, () => this.state.update(this.state.data));
    }

    addToken = () => {
        this.state.tokens.push(<Token key={this.state.tokens.length} index={this.state.tokens.length} callback={this.updateToken}/>);
        this.state.data.tokens.push({
            name: "",
            regex: "",
            delimiting: false,
            error: true,
        });
        this.forceUpdate();
    }
    
    render() {
        var errorMessage;
        if(this.checkNameRepeatError()) {
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
                    They can also be delimiting (i.e. ""). 
                    They are prioritized in-order so ensure that any overlapping regular expressions are 
                    sorted properly.
                    <br></br>
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

export default TokenEditor;