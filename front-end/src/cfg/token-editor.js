import React from 'react';
import Token from './token';

class TokenEditor extends React.Component {
    constructor(props) {
        super(props);

        this.propagateUpdate = props.propagateUpdate;
        this.refCollection = [];
        this.state = {
            tokens: [],
            error: '',
        };
    }

    addToken = () => {
        this.refCollection.push(null);
        this.state.tokens.push(<Token ref={(instance) => { this.refCollection[this.refCollection.length - 1] = instance; }} propagateUpdate={this.propagateUpdate} key={this.state.tokens.length} index={this.state.tokens.length} />);
        
        this.forceUpdate(() => {
            this.propagateUpdate();
        });
    }

    getObject = () => {
        var tokenNames = {};
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
            if(!isValid) {
                errorDescription = ref.getObject()['error'];
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
            if(ref.state.name in tokenNames) {
                tokenNames[ref.state.name].push(i);
                errorDescription = 'Two Tokens cannot share the same name.';
            } else {
                tokenNames[ref.state.name] = [i];
            }
        }

        if(errorDescription !== '') {
            this.setState({
                error: errorDescription
            });

            // we want to highlight the bad ones
            var tempCollection = this.refCollection;
            Object.keys(tokenNames).forEach(function(name) {
                if(tokenNames[name].length !== 1) {
                    tokenNames[name].forEach((index) => {
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
            <div className="token-editor">
                <div className="header">
                    <h1>Declared Tokens:</h1>
                    A token can be referenced in a Non-terminal expression. They are referenced by name
                    and have a corresponding regular expression which defines the structure of the token.
                    They can also be delimiting (i.e. ""). 
                    They are prioritized in-order so ensure that any overlapping regular expressions are 
                    sorted properly. Please also ensure that your regular expressions do not accept white
                    space.
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