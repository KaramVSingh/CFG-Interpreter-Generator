const express = require('express');
const app = express();
const fs = require('fs');
const bodyParser = require('body-parser');
const lineReader = require('line-reader');

app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
    extended: true
})); 

app.use(bodyParser.json());

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
  });

app.post('/api/', function (req, res, next) {
    const body = req.body;

    // we get a context free grammar here, we want to respond with a lexer and parser
    var main = fs.createWriteStream('c-dev/' + body['name'] + '_main.c', {});
    var lexerSource = fs.createWriteStream('c-dev/' + body['name'] + '_lexer.c', {});
    var lexerHeader = fs.createWriteStream('c-dev/' + body['name'] + '_lexer.h', {});
    var parserSource = fs.createWriteStream('c-dev/' + body['name'] + '_parser.c', {});
    var parserHeader = fs.createWriteStream('c-dev/' + body['name'] + '_parser.h', {});

    // starting with the lexer
    // first we should get every implied token, then we need to sort them by length
    // after that we need every declared token and to put them at the end

    var tokens = [];

    var i;
    var j;
    var k;

    for(i = 0; i < body['cfg']['terminals'].length; i++) {
        var terminal = body['cfg']['terminals'][i];
        var expressions = terminal['data'];

        for(j = 0; j < expressions.length; j++) {
            var expression = expressions[j];

            for(k = 0; k < expression.length; k++) {
                var curr = expression[k];
                if(curr['type'] === 'IMPLIED TOKEN') {
                    tokens.push(curr);
                }
            }
        }
    }

    tokens.sort((a, b) => {
        if(a['value'].length > b['value'].length) {
            return -1;
        } else {
            return 1;
        }
    });

    for(i = 0; i < body['cfg']['tokens'].length; i++) {
        var now = body['cfg']['tokens'][i];
        now['type'] = 'DECLARED TOKEN';
        tokens.push(now);
    }

    // console.log(tokens);
    // now we have a list of all the tokens in the correct order
    lineReader.eachLine('c-statics/main.c', function(line, last) {
        main.write(line + '\n')
    }, () => {
        main.end();
    });
    
    lexerHeader.close();
    lexerSource.close();
    parserHeader.close();
    parserSource.close();
    
    res.send({});
});

app.listen(process.env.PORT || 8080);