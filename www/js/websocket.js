/*
Websocket (WS) server built with Express to utilize the MKR1000 and ArduinoHttpClient Library

Built from the example code offered at https://www.npmjs.com/package/ws

Modified by OllieBck Nov. 20, 2016
*/

var host = "job271.itp.io"
var ws = new WebSocket('ws://' + host + ':9111');
var light_state = null;
var tv_state = null;

function toggleLight(){
  // true == light is on  false == light is off
  if (light_state == true){
    var command = "light off";
    light_state = false;
  }

  else {
    var command = "light on";
    light_state = true;
  }

  ws.send(command);
}

function toggleTV(){
  // true == tv is on  false == tv is off
  if (tv_state == true){
    var command = "tv off";
    tv_state = false;
  }
  else {
    var command = "tv on";
    tv_state = true;
  }

  ws.send(command);
}

function volUp(){
  var command = "vol up";
  ws.send(command);
}

function volDown(){
  var command = "vol down";
  ws.send(command);
}

function tvForward(){
  var command = "forward";
  ws.send(command);
}

function tvBack(){
  var command = "back";
  ws.send(command);
}

function init(){
  ws.addEventListener('message', function(event){
    if (event.data == "connected"){
      alert(event.data); // for debugging, might be good to attach to a page element to alert to connection
    }

  });

  document.getElementById('light').addEventListener('click', function(){
    toggleLight();
  });

  document.getElementById('TV').addEventListener('click', function(){
    toggleTV();
  });

  document.getElementById('TVforward').addEventListener('click', function(){
    tvForward();
  });

  document.getElementById('TVback').addEventListener('click', function(){
    tvBack();
  });

  document.getElementById('TVvolUp').addEventListener('click', function(){
    volUp();
  });

  document.getElementById('TVvolDwn').addEventListener('click', function(){
    volDown();
  });


  /*
  // this piece of code presented in the examples wasn't working for me.
  ws.onmessage == function(event){
    console.log(event);
    document.getElementById('status').innerHTML = event.data;
  };
  */
}


window.addEventListener('load', init);
