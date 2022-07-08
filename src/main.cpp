/* =======================================================================
   Gerador de função

   GPIOs disponíveis: 25 e 26
   Valor de 8 bits (0 a 255) → (0V a 3,3V)
   dacWrite(pin,value);
   
   ESP-WROOM-32U
   Board: DevKitV1
   Compilador: VS Code (Ext PlatformIO)

   Autor: Eng. Vinícius Souza -> /in/eng-viniciussouza/
   Data:  Julho de 2022
======================================================================= */

#include <main.h>
#include <BluetoothSerial.h>

BluetoothSerial BTSerial;

void setup() {
  Serial.begin(9600);
  BTSerial.begin("FIT - DAC_GEN");
}

void loop() {
  if(BTSerial.available()) {
    incomingByte = BTSerial.read();
    if((incomingByte != 255) && (incomingByte > 3)) (incomingByte >= 48 && incomingByte<=57) ? incomingNumber = ((int) (incomingByte) - 48) : opcao = (char) (incomingByte);
  }
  switch(opcao) {
    case 'S': case 's': 
      Senoidal();
    break;
    case 'T': case 't': 
      Triangular();
    break;
    case 'D': case 'd': 
      DenteSerra();
    break;
    case 'Q': case 'q': 
      Quadrada(pwmP[incomingNumber], pwmN[incomingNumber]);
    break;
    default:
      dacWrite(PIN, 0);
    break;
  }
}

void Senoidal() {
  val++;
  dacWrite(PIN, sine_wave[val]);
}

void Triangular() {
  if(!ctrl) {
    val++;
    if(val > 254) ctrl = 1;
  } else {
    val--;
    if(val < 1) ctrl = 0;
  }
  dacWrite(PIN, val);
}

void DenteSerra() {
  dacWrite(PIN, val);
  val += 2;
}

void Quadrada(uint16_t pwmP, uint16_t pwmN) {
  dacWrite(PIN, 255);
  delayMicroseconds(pwmP);
  if(pwmN != 0x00) {
    dacWrite(PIN, 0);
    delayMicroseconds(pwmN);
  }
}
