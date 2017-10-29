/*
  
  Shared Between the two servers
  
*/

var dateTime = require('node-datetime');
var clients = [];
var msgCounter = 0;

/*
  
  RookVM Server
  
*/

var WebSocketServer = require('ws').Server;
var http = require('http');

var server = http.createServer();
var wss = new WebSocketServer({server: server, path: '/RookVM'});

wss.on('connection', function(ws) {

    console.log('connected');

    ws.on('connect', function(){
      console.log("does things");
    });

    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        clients.forEach(function(client){
          var fmt = data.split('|');
          var dt = dateTime.create();
          var formatted = dt.format('Y-m-d H:M:S:N');

          formatted = String(formatted) + "-" + msgCounter;

          console.log(fmt[0] + ' >>> ' + fmt[1]);
          client.emit(fmt[0], {
            timestamp: formatted,
            data: fmt[1]
          });
          msgCounter++;
        });
    });

    ws.on('close', function() {
      console.log('Connection closed!');
    });
  
    ws.on('error', function(e) {

    });

});

server.listen(8080);
console.log('RookVM listening on port 8080...');

/*
  
  UI Server
  
*/

var uiServer = http.createServer(function(req, res) {
  res.writeHead(200, {'Content-Type': 'application/json'});
  res.end(JSON.stringify({ value: value }));
});

uiServer.listen(44500);
var io = require('socket.io').listen(uiServer);

io.on('connection', function(socket) {

  console.log('UI connected');
  clients.push(socket);

});

console.log('UIServer listening on port 44500...');