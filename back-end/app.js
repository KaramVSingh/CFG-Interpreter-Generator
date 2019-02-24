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

function renderTabs(n) {
    string = ''
    for(var i = 0; i < n; i++) {
        string += '\t';
    }

    return string;
}

function populate(string, vars) {
    var newString = '';
    var index = 0;
    for(var i = 0; i < string.length; i++) {
        if(string[i] === '$') {
            newString += vars[index];
            index++;
        } else {
            newString += string[i];
        }
    }

    return newString;
}

function cClean(string) {
    // takes a string and makes it safe for c
    var newText = "";
    var escapeCount = 0;

    for(var i = 0; i < string.length; i++) {
        if(string[i] === '\\') {
            escapeCount++;
        } else {
            if(string[i] === '"' && escapeCount % 2 === 0) {
                newText += '\\';
            }

            escapeCount = 0;
        }

        newText += string[i];
    }

    return newText;
}

function fullClean(string) {
    // takes a string and makes it safe for regex
    var newText = "";
    var escapeCount = 0;

    for(var i = 0; i < string.length; i++) {
        if(string[i] === '\\') {
            escapeCount++;
        } else {
            if(string[i] === '^' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '$' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '*' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '+' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '[' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === ']' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '{' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '}' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === '(' && escapeCount % 2 === 0) {
                newText += '\\';
            } else if(string[i] === ')' && escapeCount % 2 === 0) {
                newText += '\\';
            }
            escapeCount = 0;
        }

        newText += string[i];
    }

    return cClean(newText);
}

function getFirstHelper(terminal, terminals, visited) {
    if(terminal.name in visited) {
        return visited[terminal.name];
    }

    var first = []
    var i;
    for(i = 0; i < terminal.data.length; i++) {
        var expression = terminal.data[i];
        if(expression[0] === null || expression[0].type === 'IMPLIED TOKEN' || expression[0].type === 'DECLARED TOKEN') {
            // then we have a first
            if(!first.includes(expression[0])) {
                first.push(expression[0])
            }
        } else {
            // this is if we have a terminal
            // one of the terminals in terminals has the same name as expression 0
            var newTerminal = null;
            var j;
            for(j = 0; j < terminals.length; j++) {
                if(terminals[j].name === expression[0].value) {
                    newTerminal = terminals[j];
                    break;
                }
            }

            var newFirst = getFirstHelper(newTerminal, terminals, visited);
            for(j = 0; j < newFirst.length; j++) {
                if(!first.includes(newFirst[j])) {
                    first.push(newFirst[j]);
                }
            }
        }
    }

    visited[terminal.name] = first;
    return first;
}

function getFirst(terminal, terminals) {
    // this function will return a list of all of the firsts for the terminal
    return getFirstHelper(terminal, terminals, {});
}

function convertToId(token, tokens) {
    for(var i = 0; i < tokens.length; i++) {
        if(tokens[i].type === 'DECLARED TOKEN' && token.type === 'DECLARED TOKEN') {
            if(tokens[i].name === token.value) {
                return i;
            }
        }
        
        if(tokens[i].type === 'IMPLIED TOKEN' && token.type === 'IMPLIED TOKEN') {
            if(tokens[i].value === token.value) {
                return i;
            }
        }
    }

    return null;
}

app.post('/api/', function (req, res, next) {
    const body = req.body;

    // we get a context free grammar here, we want to respond with a lexer and parser
    var makefile = fs.createWriteStream('c-dev/' + body['name'] + '_Makefile', {});
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

    if(tokens.length > 0) {
        var tempTokens = [];

        for(i = 0; i < tokens.length; i++) {
            var add = true;
            for(j = 0; j < tempTokens.length; j++) {
                if(tokens[i].type === tempTokens[j].type && tokens[i].value === tempTokens[j].value) {
                    // repeat
                    add = false;
                }
            }

            if(add) {
                tempTokens.push(tokens[i])
            }
        }
        
        tokens = tempTokens;
    }

    for(i = 0; i < body['cfg']['tokens'].length; i++) {
        var now = body['cfg']['tokens'][i];
        now['type'] = 'DECLARED TOKEN';
        tokens.push(now);
    }

    // console.log(tokens)

    // console.log(tokens);
    // now we have a list of all the tokens in the correct order
    var lnMake = 0;
    lineReader.eachLine('c-statics/Makefile', function(line, last) {
        lnMake += 1;
        line = line.replace(/lexer/g, body['name'] + '_lexer');
        line = line.replace(/main/g, body['name'] + '_main');
        line = line.replace(/parser/g, body['name'] + '_parser');

        makefile.write(line + '\n');
    }, () => {
        makefile.end();
    });

    var lnMain = 0;
    lineReader.eachLine('c-statics/main.c', function(line, last) {
        lnMain += 1;
        if(lnMain === 1) {
            main.write('#include "' + body['name'] + '_lexer.h"\n');
        } else if(lnMain === 2) {
            main.write('#include "' + body['name'] + '_parser.h"\n');
        } else {
            main.write(line + '\n');
        }
    }, () => {
        main.end();
    });

    // now the main.c is done, we need to do the lexer.h and .c
    var lnLexerHeader = 0;
    lineReader.eachLine('c-statics/lexer.h', function(line, last) {
        // nothing language specific
        lexerHeader.write(line + '\n');
    }, () => {
        lexerHeader.end();
    });

    var lnLexerSource = 0;
    lineReader.eachLine('c-statics/lexer.c', function(line, last) {
        lnLexerSource += 1;
        if(lnLexerSource === 1) {
            lexerSource.write('#include "' + body['name'] + '_lexer.h"\n');
        } else if(lnLexerSource === 17) {
            // we need to add the tokens
            lexerSource.write('\tchar *patterns[' + tokens.length +'] = {');
            for(i = 0; i < tokens.length; i++) {
                lexerSource.write('"')
                // for each token
                if(tokens[i]['type'] === "IMPLIED TOKEN") {
                    // we want to cleanup the token before writing
                    lexerSource.write(fullClean(tokens[i]['value']));
                } else {
                    lexerSource.write(cClean(tokens[i]['regex']));
                }

                lexerSource.write('"')
                if(i !== tokens.length - 1) {
                    lexerSource.write(', ');
                }
            }

            lexerSource.write('};\n');
        } else if(lnLexerSource === 18) {
            // we need to add the delmiters
            lexerSource.write('\tint is_delimiting[' + tokens.length +'] = {');
            for(i = 0; i < tokens.length; i++) {
                if(tokens[i]['type'] === "IMPLIED TOKEN") {
                    lexerSource.write('0');
                } else {
                    if(tokens[i]['delimiting'] === true) {
                        lexerSource.write('1');
                    } else {
                        lexerSource.write('0');
                    }
                }

                if(i !== tokens.length - 1) {
                    lexerSource.write(', ');
                }
            }

            lexerSource.write('};\n');
        } else if(lnLexerSource === 19) {
            lexerSource.write('\tint n_tokens = ' + tokens.length +';\n');
        } else {
            lexerSource.write(line + '\n');
        }
    }, () => {
        lexerSource.end();
    });

    // now we need to get information about all of the terminals
    const terminals = body['cfg']['terminals'];

    var lnParserHeader = 0;
    lineReader.eachLine('c-statics/parser.h', function(line, last) {
        lnParserHeader += 1;
        if(lnParserHeader === 4) {
            parserHeader.write('#include "' + body['name'] + '_lexer.h"\n');
        } else if(lnParserHeader === 23) {
            // we want to list all of the terminals
            for(i = 0; i < terminals.length; i++) {
                parserHeader.write('tuple_t parse_' + terminals[i].name + '(token_t *h);\n');
            }
        } else {
            parserHeader.write(line + '\n');
        }
    }, () => {
        parserHeader.end();
    });

    var snippets = [];
    // we want to make sure that we have loaded the snippets by this point
    lineReader.eachLine('c-statics/parser.snippets', function(line, last) {
        snippets.push(line);
    }, () => {
        var lnParserSource = 0;
        lineReader.eachLine('c-statics/parser.c', function(line, last) {
            lnParserSource += 1;
            if(lnParserSource === 4) {
                parserSource.write('#include "' + body['name'] + '_parser.h"\n');
            } else if(lnParserSource === 20) {
                parserSource.write('\treturn parse_' + body['start'] + '(h).node;\n')
            } else if(lnParserSource === 47) {
                // we need to perform the parser creation
                var firsts = {}
                for(i = 0; i < terminals.length; i++) {
                    var terminal = terminals[i];
                    // here is where the real logic is:
                    // first we need to get the firsts() of all the non-terminals
                    var first = getFirst(terminal, terminals);
                    firsts[terminal.name] = first;
                }
    
                // now that we have all of the firsts, we can proceed to create the code
                for(i = 0; i < terminals.length; i++) {
                    // for each terminal in terminals
                    var terminal = terminals[i];
                    var tabs = 0;

                    // write the function prototype
                    parserSource.write(renderTabs(tabs) + populate(snippets[0], [terminal.name]) + '\n');
                    tabs++;

                    for(j = 1; j < 8; j++) {
                        if(j === 7) {
                            parserSource.write(renderTabs(tabs) + populate(snippets[j], [terminal.name]) + '\n');
                        } else {
                            parserSource.write(renderTabs(tabs) + populate(snippets[j], [terminal.name.length]) + '\n');
                        }
                    }

                    // function headers are now done, now we just need to do function logic
                    // start by doing initial parses on terminals to get to first differentiating tokens
                    // to do this we start by getting the shortest expression
                    var shortestExprLength = terminal.data[0].length;
                    for(j = 0; j < terminal.data.length; j++) {
                        if(terminal.data[j].length < shortestExprLength) {
                            shortestExprLength = terminal.data[j].length;
                        }
                    }

                    // now that we have the shortest exp, while the exprs are terminals of the same type
                    // we can add the parse_terminal code by first determining the number of terminals to be parsed
                    var numTerminalsToBeParsed = 0;
                    var k;
                    for(j = 0; j < shortestExprLength; j++) {
                        var expression_1 = terminal.data[0];

                        if(expression_1[0] === null) {
                            break;
                        }

                        var correctTerminalName = expression_1[j].value;
                        var hitEnd = false;
                        for(k = 0; k < terminal.data.length; k++) {
                            if(terminal.data[k][j].type !== 'TERMINAL' || terminal.data[k][j].value !== correctTerminalName) {
                                hitEnd = true;
                                break;
                            }
                        }

                        if(hitEnd) {
                            break;
                        }

                        numTerminalsToBeParsed++;
                    }

                    parserSource.write('\n');
                    var k;
                    for(j = 0; j < numTerminalsToBeParsed; j++) {
                        for(k = 8; k < 13; k++) {
                            parserSource.write(renderTabs(tabs) + populate(snippets[k], [terminal.data[0][j].value]) + '\n');
                        }

                        parserSource.write('\n');
                    }

                    // now we want to generate code for each of the possible expression paths by checking lookaheads
                    for(j = 0; j < terminal.data.length; j++) {
                        var index = numTerminalsToBeParsed;
                        tabs = 1;
                        // for each expression
                        var expression = terminal.data[j];
                        // now we want to start doing the lookahead stuff

                        // currentWord can be a TERMINAL, a TOKEN, cannot be nothing
                        // for each word in the remainder of the expression, we want to check the lookaheads to ensure
                        // that they match
                        while(index < expression.length) {
                            var currentWord = expression[index];
                            var lookaheads = [];
                            if(currentWord.type === 'TERMINAL') {
                                // the if statememnt should be the first of the terminal
                                for(k = 0; k < firsts[currentWord.value].length; k++) {
                                    lookaheads.push(convertToId(firsts[currentWord.value][k], tokens));
                                }
                            } else {
                                lookaheads.push(convertToId(currentWord, tokens));
                            }

                            // now that we have all of the lookaheads, we want to convert it into the formatted string
                            newString = ''
                            for(k = 0; k < lookaheads.length; k++) {
                                newString += populate(snippets[14], [lookaheads[k]]);
                                if(k !== lookaheads.length - 1) {
                                    newString += ' || '
                                }
                            }

                            // snippet 13 has the if stmt
                            // we want to add else if it at the base of the expression pyramid
                            var ifSnippet = snippets[13];
                            if(index === shortestExprLength - 1 && j !== 0) {
                                ifSnippet = ' else ' + ifSnippet;
                            } else {
                                ifSnippet = renderTabs(tabs) + ifSnippet;
                            }

                            // we have the formatted string
                            // now we need to add it to the if statement and push it into the file
                            parserSource.write(populate(ifSnippet, [newString]) + '\n');
                            tabs++;

                            index++;
                        }

                        // here we can close all of the curly braces
                        while(tabs > 1) {
                            tabs--;
                            parserSource.write(renderTabs(tabs) + '}');

                            // you only conditionally want the \n if you are not at the bottom of the pyramid
                            if(tabs !== 1) {
                                parserSource.write('\n');
                            }
                        }

                        // add an else at the end of each function
                        if(j === terminal.data.length - 1) {
                            // all we need to add is an else:
                            parserSource.write(' else {\n');
                            parserSource.write('\n');
                            parserSource.write(renderTabs(tabs) + '}\n');
                        }
                    }

                    // close the function
                    parserSource.write('}\n\n');
                }
            } else {
                parserSource.write(line + '\n');
            }
        }, () => {
            parserSource.end();
        });
    });

    
    res.send({});
});

app.listen(process.env.PORT || 8080);