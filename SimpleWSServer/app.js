var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({ port: 9111 });

wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
    if (message == "on"){
      sendOn();
    }
    if (message == "off"){
      sendOff();
    }
    wss.clients.forEach(function each(client){
      if (client !== ws) client.send(message);
    });
  });

  ws.send('connected');

  function sendOn() {
    ws.send('on', function ack(error){
    });
  }

  function sendOff() {
    ws.send('off', function ack(error){
    });
  }
});
