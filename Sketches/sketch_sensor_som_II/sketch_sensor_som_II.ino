/*
 * Sketch para transformar sinais de ruído em números procurando identificar instantes de silêncio
 * Antes, deve-se conferir as conexões entre a placa Arduino e o sensor de som:
 * OUT ligado em ~10
 * GND ligado em GND
 * VCC ligado em 5v
 */

int soundDetectedPin = 10; // Pino de entrada
int soundDetected = HIGH; // Flag valendo 1 identificando a ocorrencia de um som
int numReads  = 512; // quantas leituras analógicas serão realizadas 
boolean bAlarm = false;
int soundDetectedValue;
long accumulatedValue;
long avgValue;


unsigned long lastSoundDetectTime; // Ultima vez na qual detectamos um ruido


int soundAlarmTime = 500; // Duração do alarme, em milisegundos. Neste caso, meio segundo!


void setup ()
{
  Serial.begin(9600);  
  pinMode (soundDetectedPin, INPUT) ; // associamos o pino de entrada no sensor de som
}
void loop ()
{
  soundDetected = digitalRead (soundDetectedPin) ; // identificamos se houve som
  accumulatedValue = 0;
  for (int i=0; i< numReads; i++)
  {
      soundDetectedValue = analogRead(soundDetectedPin);   // mapeia voltagem de entrada (entre 0 e 5 volts) em um inteiro (entre 0 e 1023). Mais detalhes em https://www.arduino.cc/en/Reference/AnalogRead
      accumulatedValue = accumulatedValue + soundDetectedValue;
  }
  avgValue = accumulatedValue/numReads;

 // Serial.println (avgValue);
 
  if (soundDetected == HIGH) // Se houve som...
  {
    lastSoundDetectTime = millis(); // registramos instante corrente. neste caso, para guardar a última vez em que foi captado algum ruído
    if (!bAlarm){
      Serial.print("Som detectado! Valor: ");
      Serial.println (avgValue);
      Serial.println ("-------------------");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastSoundDetectTime) > soundAlarmTime  &&  bAlarm){
      Serial.println("Voltamos ao silencio");
      bAlarm = false;
    }
  }
  //delay(5000); // pausa de 5 segundos antes da próxima medida
}
