#ifndef _Personaje_H
#define _Personaje_H

#ifndef _ENERGIA_H_
#include <Energia.h>
#endif

class Personaje{

  private:
    uint8_t HBposx, HBposy; //posicion en X y Y de la barra de salud
    uint8_t Posx, Posy; //posicion en X y Y del personaje al jugar
    uint8_t Numb; //para indicar el numero de jugador que es
    
  public:
    uint8_t pose;
    short skinsel;
    Personaje(uint8_t Numb, uint8_t HBposx, uint8_t HBposy, uint8_t Posx, uint8_t Posy);
    void init(); //imprime la barra de salud
    void updateSp(); //actualizar el sprite del personaje para crear el movimiento
  };



#endif
