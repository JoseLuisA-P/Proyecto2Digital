#ifndef _Personaje_H
#define _Personaje_H

#ifndef _ENERGIA_H_
#include <Energia.h>
#endif

class Personaje{

  private:
    uint8_t HBposx, HBposy;
    uint8_t Posx, Posy;
    
    
  public:
    uint8_t pose;
    Personaje(uint8_t HBposx, uint8_t HBposy, uint8_t Posx, uint8_t Posy);
    void init(); //imprime la barra de salud
    void updateSp(); //actualizar el sprite del personaje para crear el movimiento
  };



#endif
