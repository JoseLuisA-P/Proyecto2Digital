#include "Personaje.h"
#include "SDcard.h"
#include "TFT_ili9341.h"

File lectura2;

Personaje::Personaje(uint8_t HBposx, uint8_t HBposy, uint8_t Posx, uint8_t Posy){
  //indica que el atributo es el mismo que lo declarado en el inicio
  this -> HBposx = HBposx;
  this -> HBposy = HBposy;
  this -> Posx = Posx;
  this -> Posy = Posy;
  }

void Personaje::init(){
  FillRect(HBposx,HBposy,100,30,0xD0A2);
  
  }

void Personaje::updateSp(){
  switch(pose){
    case 0:
      lectura2 = SD.open("Frame1.TXT", FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1:
      lectura2 = SD.open("Frame2.TXT", FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    }
  
  }
