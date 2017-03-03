/*
	Modulo: integraMQTTcomMongoDB.js
*/

// Prepara ambiente: mqqt
var mqtt=require('mqtt'), url = require('url');
var mqtt_url = url.parse(process.env.CLOUDMQTT_URL || 'mqtt://localhost:1883');
var url = "mqtt://" + mqtt_url.host;
var options = {
  port: mqtt_url.port,
  clientId: 'mqttjs_' + Math.random().toString(16).substr(2, 8),
};
var deviceRoot="sensores/som" ;
var client;   

// Prepara ambiente: mongodb
var mongodb=require('mongodb');  
var mongodbClient=mongodb.MongoClient;  
var mongodbURI='mongodb://159.203.163.230:27017/sensores'  ;
var collection; 

// Conecta : 
mongodbClient.connect(mongodbURI,preparaDestino);

// Preparar destino:
function preparaDestino(err,db) {  
  if(err) throw err;

  collection=db.collection("dados_sensores");
 
  client = mqtt.connect(url, options);
  client.subscribe(deviceRoot,	function() { client.on ('message', insereEvento);});
}

// Grava dados:
function insereEvento (topic,payload) {  

  console.log ("Gravando: " + payload.toString());
  var key="arduino";

  collection.update (  
    { _id:key },
    { $push: { events: { event: { value:payload.toString(), when:new Date() } } } },
    { upsert:true },
    function(err,docs) {
      if(err) { console.log("Falhou update"); } 
    }
  )

}

