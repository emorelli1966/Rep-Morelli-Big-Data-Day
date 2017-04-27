#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>   // Biblioteca instalada para realizar a comunicação com o protocolo MQTT

// Ajustes necessários para comunicação via rede
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,199);  // IP local : 192.168.1.199
IPAddress server(192,168,1,144); // Servidor: 192.168.1.144 (onde está rodando o broker MQTT - Mosquitto)
int cnt;
int cntTentativaConexao;

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
  char stentativa[10]; 
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
      snprintf(stentativa, 10, "%d", cntTentativaConexao++);
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.print(" tentativa: "); 
      Serial.print(stentativa); 
      Serial.println ("  em 5 segundos.");
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
  cntTentativaConexao = 1;
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
