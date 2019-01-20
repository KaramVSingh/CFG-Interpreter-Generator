import React from 'react';

class Expression extends React.Component {
    constructor(props) {
        super(props);

        this.index = props.index;
        this.propagateUpdate = props.propagateUpdate;
        this.state = {
            error: 'Must provide expression definition.',
            text: '',
            objects: []
        }
    }

    getObject = () => {
        if(this.state.error !== '') {
            return {
                error: this.state.error
            };
        } else {
            return this.state.objects;
        }
    }

    isValid = () => {
        if(this.state.objects.length === 0) {
            return 'Must provide expression definition.';
        }

        return '';
    }

    evaluate = (callback) => {
        this.setState({
            error: this.isValid()
        }, () => {
            callback();
        });
    }

    updateObjects(callback) {
        // this function divides the text into objects
        var newObjects = [];
        var words = this.state.text.split(/[ \t\r\n]+/);

        for (var i = 0; i < words.length; i++) {
            var word = words[i];
            if(word !== '') {

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
            this.updateObjects(() => {
                this.evaluate(this.propagateUpdate);
            });
        });
    }

    render() {
        return (
            <div className="expression">
                <input type="text" value={this.state.text} onChange={evt => this.updateText(evt)}></input>
            </div>
        );
    }
}

export default Expression;