var mqtt = require('mqtt'), url = require('url');
// Parse 
var mqtt_url = url.parse(process.env.CLOUDMQTT_URL || 'mqtt://localhost:1883');
var url = "mqtt://" + mqtt_url.host;

var options = {
  port: mqtt_url.port,
  clientId: 'mqttjs_' + Math.random().toString(16).substr(2, 8),
  protocolVersion: 3,
  protocolId: 'MQIsdp'
};


// Create uma conexão cliente
var client = mqtt.connect(url, options);

 
client.on('connect', function () {
  client.subscribe('/sensores/som')
})
 
client.on('message', function (topic, message) {
  console.log(message.toString())
  client.end()
})