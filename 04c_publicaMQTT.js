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

// Cria uma conexão cliente
var client = mqtt.connect(url, options);

client.on ('connect', function() 
{ 
	client.publish ('/sensores/som', 'Mensagem publicada via NodeJS', 
		  function() {
    				console.log("Mensagem deve ter chegado ao destino!");
    				client.end(); // Depois de publicar, fecha a conexão
  			      });
});
