import React from 'react';
import TokenEditor from './token-editor';

class CfgEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            cfg: {},
        };
    }

    propagateUpdate = () => {
        console.log(this.getObject());
    }

    getObject = () => {
        var tokenEditor = this.refs.TokenEditor.getObject();
        if(tokenEditor['error'] !== undefined) {
            // we have an error
            console.log('INVALID CFG')
        } else {
            return {
                tokens: tokenEditor,
            };
        }
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
                    <TokenEditor propagateUpdate={this.propagateUpdate} ref="TokenEditor" />
                </div>
            </div>
        );
    }
}

export default CfgEditor;