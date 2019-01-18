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
        var data = [];
        var names = {};
        var error = '';

        this.refCollection.forEach((ref) => {
            var curr = ref.getObject();
            data.push(curr);
            if(curr['error'] !== undefined) {
                // the token resulted in an error:
                error = curr['error'];
                this.setState({
                    error: error,
                });

            } else if(curr['name'] in names) {
                // there is a repeat name token error
                error = 'Two tokens cannot share the same name.'
                this.setState({
                    error: error,
                });

            } else {
                names[curr['name']] = true;
            }
        });

        if(error === '') {
            // we do not have an error
            this.setState({
                error: ''
            });

            return data;
        } else {
            return {
                error: error
            };
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