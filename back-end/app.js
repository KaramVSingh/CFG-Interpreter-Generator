const express = require('express');
const app = express();

app.get('/api/', function (req, res) {
    // we get a context free grammar here, we want to respond with a lexer and parser
    return res.send('Hello world');
});

app.listen(process.env.PORT || 8080);