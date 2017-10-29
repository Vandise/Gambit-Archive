var WebSocketServer = require('ws').Server;
var http = require('http');

var server = http.createServer();
var wss = new WebSocketServer({server: server, path: '/rookVM'});

wss.on('connection', function(ws)
{

    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        console.log('>>> ' + data);
    });

    ws.on('close', function() {
      console.log('Connection closed!');
    });

    ws.on('error', function(e) {
      
    });

});

server.listen(8080);
console.log('Listening on port 8080...');