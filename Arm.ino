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

  garra.write(88);
  punho.write(180);
  terceiro.write(180);
  segundo.write(0);
  primeiro.write(16);
  base.write(150);
  
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (lerMemoriaEeprom != 1){
      controlaBraco();
  }
}

void printValue(int posicao, String motor){
  Serial.print(motor);
  Serial.print(": ");
  Serial.println(posicao);
  Serial.println("----------------");
}

int lerMemoriaEeprom(){
  int leitura = EEPROM.read(endereco);
  Serial.print("Lendo numero da memoria EEPROM : ");
  Serial.println(leitura);
  return leitura;
}

void controlaBraco(){
  if(bluetooth.available() >= 2){
  unsigned int posicaoBase = bluetooth.read();
  unsigned int posicaoBase2 = bluetooth.read();  
  unsigned int posicaoReal = (posicaoBase2 * 256)+ posicaoBase;

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
    delay(2000);
    }

    if (posicaoReal == 8000){
    automation = 0;
    Serial.print("Gravando numero na memoria EEPROM : ");
    Serial.println(automation);
    EEPROM.write(endereco, automation);
    delay(2000);
    }

    if (posicaoReal >= 11000){
      printValue(posicaoReal, "Base");
    }
  }
}

/*
void fazAutomacao(){
  if(bluetooth.available() >= 2){
  unsigned int posicaoBase = bluetooth.read();
  unsigned int posicaoBase2 = bluetooth.read();  
  unsigned int posicaoReal = (posicaoBase2 * 256)+ posicaoBase;

    if (posicaoReal >= 11000 && posicaoReal <= 11180){
    int pBase = posicaoReal;
    printValue(pBase, "Base");
    pBase = map(pBase, 11000, 11180, 0, 180);
    base.write(pBase);
    delay(10);
    }

    if (posicaoReal >= 12000 && posicaoReal <= 12180){
    int pPrimeiro = posicaoReal;
    printValue(pPrimeiro, "Primeiro");
    pPrimeiro = map(pPrimeiro, 12000, 12180, 0, 180);
    primeiro.write(pPrimeiro);
    delay(10);
    }

    if (posicaoReal >= 13000 && posicaoReal <= 13180){
    int pSegundo = posicaoReal;
    printValue(pSegundo, "Segundo");
    pSegundo = map(pSegundo, 13000, 13180, 0, 180);
    segundo.write(pSegundo);
    delay(10);
    }

    if (posicaoReal >= 14000 && posicaoReal <= 14180){
    int pTerceiro = posicaoReal;
    printValue(pTerceiro, "Terceiro");
    pTerceiro = map(pTerceiro, 14000, 14180, 0, 180);
    terceiro.write(pTerceiro);
    delay(10);
    }

    if (posicaoReal >= 15000 && posicaoReal <= 15180){
    int pPunho = posicaoReal;
    printValue(pPunho, "Punho");
    pPunho = map(pPunho, 15000, 15180, 0, 180);
    punho.write(pPunho);
    delay(10);
    }

    if (posicaoReal >= 16000 && posicaoReal <= 16180){
    int pGarra = posicaoReal;
    printValue(pGarra, "Garra");
    pGarra = map(pGarra, 16000, 16180, 0, 180);
    garra.write(pGarra);
    delay(10);
   }
  } 
}*/
