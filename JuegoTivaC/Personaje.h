#ifndef _Personaje_H
#define _Personaje_H

#ifndef _ENERGIA_H_
#include <Energia.h>
#endif

class Personaje{

  private:
    uint8_t HBposx, HBposy; //posicion en X y Y de la barra de salud
    int Posx, Posy; //posicion en X y Y del personaje al jugar
    uint8_t Numb; //para indicar el numero de jugador que es
    
  public:
    uint8_t pose; //que pose tomara
    short skinsel; //que skin se va a seleccionar
    uint8_t health; //vida del personaje
    Personaje(uint8_t Numb, uint8_t HBposx, uint8_t HBposy,unsigned int Posx,unsigned int Posy);
    void init(); //imprime la barra de salud
    void updateSp(); //actualizar el sprite del personaje para crear el movimiento
    void takedamage(uint8_t dano); //cuando el personaje recibe daño
    void healdamage(uint8_t dano); //sanar al personaje
  };



#endif
