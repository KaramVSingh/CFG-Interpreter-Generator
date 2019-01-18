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

    evaluate = (callback) => {
        if(this.state.name === '' || this.state.regex === '') {
            this.setState({
                error: true
            }, () => {
                callback();
            });
        } else {
            if(this.state.name.match(/^[a-zA-Z_]+$/)) {
                this.setState({
                    error: false
                }, () => {
                    callback();
                });
            } else {
                this.setState({
                    error: true
                }, () => {
                    callback();
                });
            }
        }
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