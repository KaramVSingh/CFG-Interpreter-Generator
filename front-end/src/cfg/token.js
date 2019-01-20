import React from 'react';

class Token extends React.Component {
    constructor(props) {
        super(props);
        this.index = props.index;
        this.propagateUpdate = props.propagateUpdate;

        this.state = {
            name: '',
            regex: '',
            delimiting: false,
            error: true,
        };
    }

    cleanRegex = () => {
        var newRegex = "";
        var escapeCount = 0;
        for(var i = 0; i < this.state.regex.length; i++) {
            if(this.state.regex[i] === "^") {
                if(this.state.regex[i - 1] === "[") {
                    newRegex = newRegex.concat(this.state.regex[i]);
                } else if(this.state.regex[i - 1] === "\\") {
                    if(escapeCount % 2 === 1) {
                        newRegex = newRegex.concat(this.state.regex[i]);
                    } else {
                        newRegex = newRegex.concat("\\^");
                    }
                } else {
                    newRegex = newRegex.concat("\\^");
                }

                escapeCount = 0;
            } else if(this.state.regex[i] === "$") {
                if(escapeCount % 2 === 1) {
                    newRegex = newRegex.concat(this.state.regex[i]);
                } else {
                    newRegex = newRegex.concat("\\$");
                }

                escapeCount = 0;
            } else if(this.state.regex[i] === "\\") {
                escapeCount += 1;
                newRegex = newRegex.concat(this.state.regex[i]);
            } else {
                escapeCount = 0;
                newRegex = newRegex.concat(this.state.regex[i]);
            }
        }

        this.setState({
            regex: newRegex,
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    getObject = () => {
        if(this.state.error) {
            return {
                error: 'Provide both Name and Regular Expression. Name must contain A-Z, a-z, or _.',
            };
        } else {
            return {
                name: this.state.name,
                regex: this.state.regex,
                delimiting: this.state.delimiting,
            };
        }
    }

    updateName(evt) {
        this.setState({
            name: evt.target.value,
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    updateRegex(evt) {
        this.setState({
            regex: evt.target.value,
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    updateDelimiting() {
        this.setState({
            delimiting: !this.state.delimiting,
        }, () => {
            this.evaluate(this.propagateUpdate);
        });
    }

    isValid = () => {
        if(this.state.name === '' || this.state.regex === '') {
            return false;
        } else {
            if(this.state.name.match(/^[a-zA-Z_]+$/)) {
                return true;
            } else {
                return false;
            }
        }
    }

    evaluate = (callback) => {
        this.setState({
            error: !this.isValid()
        }, () => {
            callback();
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

export default Token;