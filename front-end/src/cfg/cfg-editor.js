import React from 'react';
import TokenEditor from './token-editor';

class CfgEditor extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            cfg: {},
        };
    }

    updateTokens = (tokens) => {
        this.setState({
            cfg: {
                tokens: tokens,
            },
        }, () => {
            console.log(this.state.cfg);
        });
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
                    <TokenEditor callback={this.updateTokens}/>
                </div>
            </div>
        );
    }
}

export default CfgEditor;