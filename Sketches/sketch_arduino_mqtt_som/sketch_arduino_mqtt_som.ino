/*
Sketch para integrar o sensor de som ao MQTT
Vamos captar sons partir do sensor, cujas transformações numéricas serão mostradas por um assinante
Podemos acompanhar o que estiver sendo publicado:
mosquitto_sub -h localhost -t sensores/som 
*/
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Ajustar valores a seguir para que façam sentido na Rede na qual será executado o Sketch
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip_local (192, 168, 1, 118);         // IP Arduino
IPAddress ip_server(192, 168, 0, 3);   // IP servidor MQTT 

// As variáveis a seguir serão utilizadas pelo sensor de som
int soundDetectedPin = 10; 			// Usa Pino 10 como canal de entrada ou saída para sons
int numReads  = 256; 				// Número de leituras analógicas 
int soundDetectedValue;
long accumulatedValue;
long avgValue;

// As variáveis a seguir serão utilizadas na comunicação via MQTT
EthernetClient ethClient;
PubSubClient client(ethClient);


// Função para estabelecer contato com a placa Arduino
void reconnect() {
  // Laço até que seja realizada a conexão
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT ...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("conectou!");
      // Uma vez conectado, manda sinal de fumaça
         client.publish("sensores/som","-1");
      } 
      else {
        Serial.print("Conexao falhou, codigo de retorno=");
        Serial.print(client.state());
        Serial.println(" Nova tentativa em 5 segundos");
        // Vamos esperar 5 segundos e tentar nova conexão
        delay(5000);
      }
  }
}

void setup()
{
  Serial.begin(9600);                   // Determina velocidade de cominicação com Monitor
  pinMode (soundDetectedPin, INPUT) ; 	// Caracteriza o Pino 10, previamente especificado como E/S, como canal de entrada
  Ethernet.begin(mac, ip_local);				// Prepara a placa de rede (ponte entre o arduino e o mundo exterior)
  client.setServer(ip_server, 1883);     // Estabelece uma ligação com a porta utilizada pelo protocolo mqtt
  delay(1500);							// Permite que o hardware se prepare
}

void loop()
{
  long medida;
  char smedida[10]; 
   
  if (!client.connected()) {
    reconnect();
  }
  else
  {
    accumulatedValue = 0;
    for (int i=0; i< numReads; i++)
    {
      soundDetectedValue = analogRead(soundDetectedPin);
      accumulatedValue = accumulatedValue + soundDetectedValue;
    }
    avgValue = accumulatedValue/numReads;

    snprintf(smedida, 10, "%d", avgValue);

    client.publish("sensores/som",smedida);

    delay(5000); // pausa para captura de "sons"

   
  } 
  client.loop(); 
}
