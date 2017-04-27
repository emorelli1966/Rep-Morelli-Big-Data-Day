/*
 * Sketch para transformar sinais de ruído em números e realizando uma classificação (baixo, médio ou alto)
 * Antes, deve-se conferir as conexões entre a placa Arduino e o sensor de som:
 * OUT ligado em ~10
 * GND ligado em GND
 * VCC ligado em 5v
 */
int num_leitura = 64; //Define o numero de medicoes  
int pinosinal = 10; //Pino ligado ao pino "OUT" do modulo sensor de som  
long sinal;   //Armazena o valor lido do Sensor de Som  
long maisAlto = 0; // armazena valor mais alto captado no intervalo
long nivel =0; //Armazena o valor medio  
  
void setup()  
{   
  pinMode(pinosinal, INPUT); //Define o pino de sinal como Entrada  
  Serial.begin(9600);  
 
}  
   
void loop()  
{  
  //Efetua N leituras do sinal  
  for (int i=0; i<num_leitura ; i++)  
  {  
    sinal = analogRead(pinosinal);  // analogRead lê à taxa de 10.000 por segundo. Converte saída em um valor entre 0 e 1023
                                
    if (sinal > maisAlto)
    {
        maisAlto = sinal;
    }
  }  

  nivel  = maisAlto;
       
  //Verifica o nivel de sinal e exibe na tela    
  if (nivel >0 && nivel < 100)  
  {  
    Serial.print("Nivel Baixo");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  

  if (nivel >100 && nivel < 200)  
  {  
    Serial.print("Nivel Medio");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  

  if (nivel > 200)  
  {  
     Serial.print("Nivel Alto");  
    Serial.print(" - Media : ");  
    Serial.println(nivel);  
  }  

  //Reinicia a soma dos valores das medicoes  
  maisAlto = 0;
  delay(5000);  // pausa de 5 segundos
} 
