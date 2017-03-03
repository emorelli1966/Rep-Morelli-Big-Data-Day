#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>   // Biblioteca instalada para realizar a comunicação com o protocolo MQTT

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 14);   // IP local
IPAddress server(159,203,163,230);  // IP Servidor
int cnt;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Chegou mensagem [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Procurando MQTT......");
    // Tentativa de conexão
    if (client.connect("arduinoClient")) {
      Serial.println("Conectou");
      // Atuando como publicador...
      client.publish("pubArduino","Arduino mandando mensagem inicial");
      // ... e assinante
      client.subscribe("pubArduino");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
       delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(57600); // atenção à velocidade de transmissão

  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Pausa para arrumações internas
  delay(1500);
  cnt = 0;
}

void loop()
{
  char smedida[10]; 
  if (!client.connected()) {
    reconnect();
  }
  else
  {
     snprintf(smedida, 10, "%d", cnt++);
     client.publish("pubArduino","arduino informa: estou vivo!");
     client.publish("pubArduino",smedida);
     client.subscribe("pubArduino");
     delay(5000);
  }
  client.loop();
}
