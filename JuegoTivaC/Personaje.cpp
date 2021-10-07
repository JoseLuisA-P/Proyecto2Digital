#include "Personaje.h"
#include "SDcard.h"
#include "TFT_ili9341.h"

File lectura2;

Personaje::Personaje(uint8_t Numb, uint8_t HBposx, uint8_t HBposy, uint8_t Posx, uint8_t Posy){
  //indica que el atributo es el mismo que lo declarado en el inicio
  this -> Numb = Numb;
  this -> HBposx = HBposx;
  this -> HBposy = HBposy;
  this -> Posx = Posx;
  this -> Posy = Posy;
  }

void Personaje::init(){
  FillRect(HBposx,HBposy,100,30,0xD0A2);
  
  }

void Personaje::updateSp(){
  const char* dato1 = "Frame1.TXT";
  const char* dato2 = "Frame2.TXT";
  switch(Numb*skinsel){
  
  case 0:  //skin 1 del personaje 1
   
  switch(pose){
    case 0:
      lectura2 = SD.open(dato1, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1:
      lectura2 = SD.open(dato2, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    }
    
  break;

  case 1:  //skin 2 del personaje 1
   
  switch(pose){
    case 0:
      lectura2 = SD.open(dato2, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1:
      lectura2 = SD.open(dato1, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    }
    
  break;

  case 2:  //skin 1 del personaje 2
   
  switch(pose){
    case 0:
      lectura2 = SD.open(dato1, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1:
      lectura2 = SD.open(dato2, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    }
    
  break;

  case 4:  //skin 2 del personaje 2
   
  switch(pose){
    case 0:
      lectura2 = SD.open(dato2, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1:
      lectura2 = SD.open(dato1, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    }
    
  break;
  
  }
  
  }
