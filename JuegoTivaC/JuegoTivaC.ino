#include "TFT_ili9341.h"
#include "SDcard.h"
#include <SPI.h>
#include <SD.h>

File lectura; //para leer un archivo de la SD
uint8_t animacion;

void setup() {
  Serial.begin(9600);
  LCD_Init();
  LCD_Clear(0xf4f4);

  SPI.setModule(0); //modulo 0 de SPI para usar con la SD
  pinMode(PA_3,OUTPUT); //CS de la SD como salida
  
  if(!SD.begin(PA_3)){ //inicia la SD y determina si esta insertada de forma correcta
    LCD_Print("Falta almacenamiento",100,110,1,0xffff,0x0000);
    return; //si no lo esta, no deja que avance el juego por seguridad
    }
  LCD_Print("Almacenamiento",55,35,1,0x0000,0xf4f4);  //si lo esta, lo indica y corre con el inicio normalmente
  LCD_Print("encontrado",55,55,1,0x0000,0xf4f4);
  delay(1000);
  
  lectura = SD.open("Bitmap2.TXT",FILE_READ);
  bitmapSD(lectura, 320, 240);
  lectura.close();
  delay(1000);

  

}
  

void loop() {
  switch(animacion){
    case 0:
      lectura = SD.open("Frame1.TXT", FILE_READ);
      spriteSD(lectura,100,100);
      lectura.close();
      break;
    case 1:
      lectura = SD.open("Frame2.TXT", FILE_READ);
      spriteSD(lectura,100,100);
      lectura.close();
      break;
    }
    delay(100);
    animacion ++;
    if(animacion > 1) animacion = 0;
  
}
