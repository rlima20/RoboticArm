#include <Servo.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial bluetooth(0, 1);
Servo base, primeiro, segundo, terceiro, punho, garra;

int automation = 0;
int endereco = 0;

void setup() {
  base.attach(3); 
  primeiro.attach(5); 
  segundo.attach(6); 
  terceiro.attach(9); 
  punho.attach(10); 
  garra.attach(11); 
  
  Serial.begin(9600);
  bluetooth.begin(9600);
  setInitialPosition(); 
}

void loop() {
  unsigned int posicao = bluetooth.read();
  unsigned int posicao2 = bluetooth.read();  
  unsigned int posicaoReal = (posicao2 * 256)+ posicao;

  int memoria = lerMemoriaEeprom();
  
  if (memoria == 1){
      Serial.print("Lendo numero da memoria EEPROM: ");
      Serial.println(memoria);  
        automacao(); 
  }else if (memoria == 0){
      Serial.print("Lendo numero da memoria EEPROM: ");
      Serial.println(memoria);
  }

      if(bluetooth.available() >= 2){
        Serial.println("Conectado");
        controle(posicao, posicao2, posicaoReal); 
      }else{
        Serial.println("Conectando .....");
  }
}

void setInitialPosition(){
  Serial.println("Setting Initial Position...");
  garra.write(140);
  punho.write(150);
  terceiro.write(150);
  segundo.write(0);
  primeiro.write(16);
  base.write(79);
}

void printValue(int posicao, String motor){
  Serial.print(motor);
  Serial.print(": ");
  Serial.println(posicao);
  Serial.println("----------------");
}

int lerMemoriaEeprom(){
  int leitura = EEPROM.read(endereco);
  return leitura;
}

void automacao(){
  Serial.println("Automação rodando.....");
  for(int pos = 79; pos <= 180; pos++){
  base.write(pos);
  delay(15);
  }
  delay(500);
  for(int pos = 180; pos >= 79; pos--){
    base.write(pos);
    delay(15);
  }
  delay(2000);
}

void controle(unsigned int posicao, unsigned int posicao2, unsigned int posicaoReal){
    if (posicaoReal >= 1000 && posicaoReal <= 1180){
    int pBase = posicaoReal;
    printValue(pBase, "Base");
    pBase = map(pBase, 1000, 1180, 0, 180);
    base.write(pBase);
    delay(10);
    }

    if (posicaoReal >= 2000 && posicaoReal <= 2180){
    int pPrimeiro = posicaoReal;
    printValue(pPrimeiro, "Primeiro");
    pPrimeiro = map(pPrimeiro, 2000, 2180, 0, 180);
    primeiro.write(pPrimeiro);
    delay(10);
    }

    if (posicaoReal >= 3000 && posicaoReal <= 3180){
    int pSegundo = posicaoReal;
    printValue(pSegundo, "Segundo");
    pSegundo = map(pSegundo, 3000, 3180, 0, 180);
    segundo.write(pSegundo);
    delay(10);
    }

    if (posicaoReal >= 4000 && posicaoReal <= 4180){
    int pTerceiro = posicaoReal;
    printValue(pTerceiro, "Terceiro");
    pTerceiro = map(pTerceiro, 4000, 4180, 0, 180);
    terceiro.write(pTerceiro);
    delay(10);
    }

    if (posicaoReal >= 5000 && posicaoReal <= 5180){
    int pPunho = posicaoReal;
    printValue(pPunho, "Punho");
    pPunho = map(pPunho, 5000, 5180, 0, 180);
    punho.write(pPunho);
    delay(10);
    }

    if (posicaoReal >= 6000 && posicaoReal <= 6180){
    int pGarra = posicaoReal;
    printValue(pGarra, "Garra");
    pGarra = map(pGarra, 6000, 6180, 0, 180);
    garra.write(pGarra);
    delay(10);
    }

    if (posicaoReal == 7000){
    automation = 1;
    Serial.print("Gravando numero na memoria EEPROM : ");
    Serial.println(automation);
    EEPROM.write(endereco, automation);
    delay(10);
    }

    if (posicaoReal == 8000){
    automation = 0;
    Serial.print("Gravando numero na memoria EEPROM : ");
    Serial.println(automation);
    EEPROM.write(endereco, automation);
    delay(10);
    }
}
