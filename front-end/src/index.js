import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';

class Token extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            name: '',
            regex: '',
            delimited: false,
        };
    }

    updateName(evt) {
        this.setState({
            name: evt.target.value
        });
    }

    updateRegex(evt) {
        this.setState({
            regex: evt.target.value
        });
    }

    updateDelimited = () => {
        this.setState({
            delimited: !this.state.delimited,
        });
    }

    render() {
        console.log(this.state)
        return (
            <div className="token">
            delimited?: <input type="checkbox" value={this.state.delimited} onClick={this.updateDelimited}></input>
            Token Name: <input value={this.state.name} type="text" onChange={evt => this.updateName(evt)}></input>
            -> <input value={this.state.regex} type="text" onChange={evt => this.updateRegex(evt)}></input>
            </div>
        );
    }
}

class AddTokenButton extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            callback: props.callback,
        };
    }

    render() {
        return (
            <button onClick={this.state.callback}>Add Token</button>
        );
    }
}

class TokenEditor extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tokens: [],
        };
    }

    addTokenCallback = () => {
        this.state.tokens.push(<Token key={this.state.tokens.length}/>);
        this.forceUpdate();
    }

    render() {
        return (
            <div className="token-container">
            <div className="options">
                <AddTokenButton callback={this.addTokenCallback}/>
            </div>
            <div className="token-list">
                {this.state.tokens}
            </div>
            </div>
        );
    }
}
  
class App extends React.Component {
    render() {
        return (
            <div className="Application">
            <TokenEditor />
            </div>
        );
    }
}

  
ReactDOM.render(
    <App />,
    document.getElementById('root')
);
  