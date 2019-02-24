import React from 'react';

class Expression extends React.Component {
    constructor(props) {
        super(props);

        this.index = props.index;
        this.propagateUpdate = props.propagateUpdate;
        this.state = {
            error: '',
            text: '',
            objects: [{
                type: null,
                value: null,
            }]
        };
    }

    first = () => {
        return this.state.objects[0];
    }

    getObject = () => {
        if(this.state.error !== '') {
            return {
                error: this.state.error
            };
        } else if(this.isValid() !== '') {
            return {
                error: this.isValid()
            };
        } else {
            return this.state.objects;
        }
    }

    isValid = () => {
        if(this.state.objects[0].type === null) {
            return 'Expression must have a definition.';
        } else {
            return '';
        }
    }

    evaluate = (callback) => {
        this.setState({
            error: this.isValid()
        }, () => {
            callback();
        });
    }

    cleanText(callback) {
        return callback();
        
        /*

        var newText = "";
        var escapeCount = 0;
        for(var i = 0; i < this.state.text.length; i++) {
            if(this.state.text[i] === '\\') {
                escapeCount++;
            } else {
                if(this.state.text[i] === '^' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '$' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '*' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '+' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '[' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === ']' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '{' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '}' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === '(' && escapeCount % 2 === 0) {
                    newText += '\\';
                } else if(this.state.text[i] === ')' && escapeCount % 2 === 0) {
                    newText += '\\';
                }
                escapeCount = 0;
            }

            newText += this.state.text[i];
        }

        this.setState({
            text: newText,
        }, () => {
            callback();
        });

        */
    }

    updateObjects(callback) {
        // this function divides the text into objects
        var newObjects = [];
        var words = this.state.text.split(/[ \t\r\n]+/);

        if(words.length === 1 && words[0] === '') {
            newObjects.push({
                type: null,
                value: null,
            });
        }

        for (var i = 0; i < words.length; i++) {
            var word = words[i];
            if(word !== '') {
                if(word.match(/^TOKEN:[A-Za-z_]+$/)) {
                    // we have a token
                    newObjects.push({
                        type: 'DECLARED TOKEN',
                        value: word.slice(6, word.length)
                    });
                } else if(word.match(/^TERMINAL:[A-Za-z_]+$/)) {
                    // we have a terminal
                    newObjects.push({
                        type: 'TERMINAL',
                        value: word.slice(9, word.length)
                    });
                } else {
                    // we have a regular implied token
                    newObjects.push({
                        type: 'IMPLIED TOKEN',
                        value: word
                    });
                }
            }
        }

        this.setState({
            objects: newObjects
        }, () => {
            return callback();
        });
    }

    updateText(evt) {
        this.setState({
            text: evt.target.value,
        }, () => {
            this.cleanText(() => {
                this.updateObjects(() => {
                    this.evaluate(this.propagateUpdate);
                });
            });
        });
    }

    styleForType(type) {
        if(type === 'DECLARED TOKEN') {
            return {
                background: 'lightyellow',
                padding: '2.5px',
                paddingLeft: '4px',
                paddingRight: '4px',
                display: 'inline-block',
                marginRight: '10px',
                flexDirection: 'row',
                marginBottom: '10px'
            }
        } else if(type === 'TERMINAL') {
            return {
                background: 'paleturquoise',
                padding: '2.5px',
                paddingLeft: '4px',
                paddingRight: '4px',
                display: 'inline-block',
                marginRight: '10px',
                flexDirection: 'row',
                marginBottom: '10px'
            }
        } else {
            return {
                background: 'palegreen',
                padding: '2.5px',
                paddingLeft: '4px',
                paddingRight: '4px',
                display: 'inline-block',
                marginRight: '10px',
                flexDirection: 'row',
                marginBottom: '10px'
            }
        }
    }

    render() {
        var objects = [];
        objects = this.state.objects.map((object, index) => {
            if(object.type != null) {
                return (
                    <div className="object" key={index} style={this.styleForType(object.type)}>
                        {object.value}
                    </div>
                );
            } else {
                return (<div key="0"></div>);
            }
            
        });

        return (
            <div className="expression">
                <input type="text" value={this.state.text} onChange={evt => this.updateText(evt)}></input>
                <br></br>
                {objects}
            </div>
        );
    }
}

export default Expression;