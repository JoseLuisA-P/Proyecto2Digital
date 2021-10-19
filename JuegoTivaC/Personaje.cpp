#include "Personaje.h"
#include "SDcard.h"
#include "TFT_ili9341.h"

File lectura2;
//constructor
Personaje::Personaje(uint8_t Numb, uint8_t HBposx, uint8_t HBposy,unsigned int Posx,unsigned int Posy){
  //indica que el atributo es el mismo que lo declarado en el inicio
  this -> Numb = Numb;
  this -> HBposx = HBposx;
  this -> HBposy = HBposy;
  this -> Posx = Posx;
  this -> Posy = Posy;
  }

//inicializar el personaje
void Personaje::init(){
  FillRect(HBposx,HBposy,100,16,0xD0A2); //colocar la barra de vida donde se indico
  this -> health = 100; //colocar su vida al maximo
  }

void Personaje::updateSp(){
  const char* dato1 = "Frame1.TXT";
  const char* dato2 = "Frame2.TXT";
  const char* dato3 = "P1S1UP.TXT";
  const char* dato4 = "P1S1DW.TXT";
  const char* dato5 = "NINA1.TXT";
  const char* dato6 = "NINA2.TXT";
  const char* dato7 = "NINADAM.TXT";
  const char* dato8 = "NINAHIT.TXT";
  const char* dato9 = "NINO1.TXT";
  const char* dato10 = "NINO2.TXT";
  const char* dato11 = "NINOHIT.TXT";
  const char* dato12 = "NINODAM.TXT";
  const char* dato13 = "AZUL1.TXT";
  const char* dato14 = "AZUL2.TXT";
  const char* dato15 = "AZULHIT.TXT";
  const char* dato16 = "AZULDAM.TXT";
  const char* dato17 = "ROJO1.TXT";
  const char* dato18 = "ROJO2.TXT";
  const char* dato19 = "ROJOHIT.TXT";
  const char* dato20 = "ROJODAM.TXT";
  
  switch(Numb+skinsel){
  
  case 0:  //skin 1 del personaje 1
   
  switch(pose){
    case 0: //pose 1
      lectura2 = SD.open(dato13, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1: //pose 2
      lectura2 = SD.open(dato14, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 3: //recibe daño
      lectura2 = SD.open(dato16, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    case 4: //golpea
      lectura2 = SD.open(dato15, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    }
    
  break;

  case 1:  //skin 2 del personaje 1
   
  switch(pose){
    case 0: //pose 1
      lectura2 = SD.open(dato10, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1: //pose 2
      lectura2 = SD.open(dato9, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 3: //recibe daño
      lectura2 = SD.open(dato12, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    case 4: //golpea
      lectura2 = SD.open(dato11, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    }
    
  break;

  case 2:  //skin 1 del personaje 2
   
  switch(pose){
    case 0: //pose 1
      lectura2 = SD.open(dato17, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1: //pose 2
      lectura2 = SD.open(dato18, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 3: //recibe daño
      lectura2 = SD.open(dato20, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    case 4: //golpea
      lectura2 = SD.open(dato19, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    }
    
  break;

  case 3:  //skin 2 del personaje 2
   
  switch(pose){
    case 0: //pose 1
      lectura2 = SD.open(dato5, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 1: //pose 2
      lectura2 = SD.open(dato6, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
    break;
    case 3: //recibe daño
      lectura2 = SD.open(dato7, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
   case 4: //golpea
      lectura2 = SD.open(dato8, FILE_READ);
      spriteSD(lectura2,Posx,Posy);
      lectura2.close();
      break;
    }
    
  break;
  
  }
  
  }


void Personaje::takedamage(uint8_t dano){
  if(health> dano)health = health - dano;
  else health = 0;
  if(health>0)FillRect((HBposx+health),HBposy,100-health,16,0x00); //colorea poco a poco la barra de vida para simular daño
  else FillRect(HBposx,HBposy,100,16,0x00);
  }

void Personaje::healdamage(uint8_t dano){
  if((100-health) > dano){
    FillRect((HBposx+health),HBposy,dano,16,0xD0A2); //colorea poco a poco la barra de vida para simular aumento de vida
    health = health + dano;
  }
  else {
    health = 100;
    FillRect(HBposx,HBposy,100,16,0xD0A2);
  }
  
  }
