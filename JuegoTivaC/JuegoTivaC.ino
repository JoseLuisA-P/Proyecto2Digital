#include "TFT_ili9341.h"
#include "SDcard.h"
#include <SPI.h>
#include <SD.h>
#include "Personaje.h"

Personaje player1(0,30,30,30,120); //objeto del personaje 1
Personaje player2(2,200,30,200,120); //objeto del personaje 2

File lectura; //para leer un archivo de la SD
uint8_t animacion = 0; //mover las animaciones de los personajes
uint8_t mensel = 0; //seleccionar el menu
bool onete; //utilizado para activar los eventos de una sola vez
unsigned long prevTime = 0; //para el delay sin detener la ejecucion
int intervalo; //intervalo para los cambios de bitmap en los personajes o titulos que titilan
int inMes; //mensaje obtenido por el serial
short P1sel, P2sel; //seleccionar los personajes y atributos de cada uno
short atck1,atck2; //seleccionar los ataques de los personajes
uint8_t atckVal; //valor del ataque tipo random

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

  LCD_Clear(0x62AA);
  
  //player1.init();
  //player2.init();
  onete = 1; //evento de una vez inicializado
  intervalo = 500; //primer intervalo, se indicara el cambio en las pantallas de intermedio
}
  

void loop() {
  unsigned long actTime = millis();
    if(actTime-prevTime > intervalo){ //generar delays sin detener la ejecucion del codigo
      prevTime = actTime;
      animacion++;
    }
    
  switch(mensel){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////pantalla de menu
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    case 0: 
      if(onete) { LCD_Print("Inicio del juego",30,50,2,0x0000,0x62AA); onete = 0;} //para imprimir una vez el texto de inicio
      
      if(animacion)LCD_Print("Presiona el boton para comenzar",30,150,1,0x0000,0x62AA);
      else FillRect(30,150,250,30,0x62AA); //animacion del texto de presionar START para ir a seleccion de personajes
      if(animacion > 1) animacion = 0; //dos estados para presionar, se modifica dependiendo la pantalla desplegada

      if(Serial.available()){ //leer el dato enviado por el control
        inMes = Serial.read();
        }

      if(inMes == '1')mensel = 1; //al presionar start cambia de pantalla
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de seleccion de personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
    case 1:
      if(!onete){  //preparando el evento de una vez para la pelea y colocando la pantalla de seleccion
        LCD_Clear(0x62AA);
        LCD_Print("SELECCIONA TU JUGADOR",80,30,1,0x0000,0x62AA);
        printPlayers();
        onete= 1; 
        inMes = 0;
        }
      if(Serial.available()){ //leer el dato enviado por el control
        inMes = Serial.read();
        switch(inMes){ //dependiendo del valor seleccionado, asi cambia la seleccion del personaje
          case '2':
            player1.skinsel ++;
            if(player1.skinsel>1)player1.skinsel = 0; //solo dos estados de cambio
            break;
          case '3':
            player2.skinsel ++;
            if(player2.skinsel >1)player2.skinsel = 0; //solo dos estados
            break;
          }
          choosePlayers();
          
        }

        if (inMes == '9'){
          mensel = 2;
          LCD_Clear(0x62AA);
          player1.init();
          player2.init();
          printIcon();
          updateLife();
          inMes = 0;
          intervalo = 200;
          animacion = 0;
          }
        else inMes = 0;
      break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de la pelea de personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 2: //pantalla de la pelea 
      randomSeed(prevTime);
      atckVal = random(10,15);
      player1.updateSp();
      player2.updateSp();
      player1.pose = animacion;
      player2.pose = animacion;
      if(animacion > 1) animacion = 0;
      if(Serial.available()){ //leer el dato enviado por el control
        inMes = Serial.read();
      switch(inMes){
      case '5':
        player2.pose = 4;
        player2.updateSp();
        player1.pose = 3;
        player1.updateSp();
        player1.takedamage(atckVal);
        updateLife();
        delay(200);
        break;
      case '6':
        player1.pose = 4;
        player1.updateSp();
        player2.pose = 3;
        player2.updateSp();
        player2.takedamage(atckVal);
        updateLife();
        delay(200);
        break;
      }
      inMes = 0;
      }

      if(player1.health == 0)mensel = 3;
      if(player2.health == 0)mensel = 4;
      
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de victoria de uno de los personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 3:
      LCD_Clear(0x62AA);
      LCD_Print("Gano2",100,120,2,0x00,0x62AA);
      mensel = 5;
      intervalo = 500;
      break;
    case 4:
      LCD_Clear(0x62AA);
      LCD_Print("Gano1",100,120,2,0x00,0x62AA);
      mensel = 5;
      intervalo = 500;
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de reinicio y para reiniciar los parametros de los jugadores
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 5:
      if(animacion)LCD_Print("Presiona start volver",30,150,1,0x0000,0x62AA);
      else FillRect(30,150,250,30,0x62AA); //animacion del texto de presionar START para ir a seleccion de personajes
      if(animacion > 1) animacion = 0;
      if(Serial.available()) inMes = Serial.read();

      if(inMes == '1'){
        mensel = 0;
        LCD_Clear(0x62AA);
        player1.health = 100;
        player2.health = 100;
      }
      else inMes = 0;
      
      break;
      
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Funciones utilizadas para desplegar personajes, objetos o seleccion.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPlayers(){ //Colocar los bitmaps de los personajes en la pantalla
      lectura = SD.open("P1S2DW.TXT", FILE_READ);
      spriteSD(lectura,100,60);
      lectura.close();

      lectura = SD.open("P2S2UP.TXT", FILE_READ);
      spriteSD(lectura,200,60);
      lectura.close();

      lectura = SD.open("Frame1.TXT", FILE_READ);
      spriteSD(lectura,100,120);
      lectura.close();
      
      lectura = SD.open("Frame1.TXT", FILE_READ);
      spriteSD(lectura,200,120);
      lectura.close();
  
  }

void printIcon(){ //imprimir los iconos de ataque, vida y otros de la pantalla
    lectura = SD.open("HPICON.TXT", FILE_READ);
    bitmapSD(lectura,16,16,14,30);
    bitmapSD(lectura,16,16,184,30);
    lectura.close();

    lectura = SD.open("ATKPH.TXT",FILE_READ);
    bitmapSD(lectura,30,30,30,160);
    bitmapSD(lectura,30,30,60,160);
    bitmapSD(lectura,30,30,90,160);
    lectura.close();
    
  }

void updateLife(){ //actualizar los valores de vida en cada ataque
  //imprime los valores de la salud restante de cada personaje, para sobreponer los valores y los cambios de centenas a decenas
  //y a unidad, se borra en cada actualizacion para imprimir el valor en limpio
  String vida1 = String(player1.health);
  if(player1.health >= 100)LCD_Print(vida1,30,46,1,0x0000,0x62AA);
  if(player1.health>=10 & player1.health<100){FillRect(30,46,40,10,0x62AA); LCD_Print(vida1,35,46,1,0x000,0x62AA);}
  if (player1.health<10) {FillRect(30,46,40,10,0x62AA); LCD_Print(vida1,45,46,1,0x000,0x62AA);}
  LCD_Print("/100",55,46,1,0x0000,0x62AA);
  
  String vida2 = String(player2.health);
  if(player2.health >= 100)LCD_Print(vida2,200,46,1,0x0000,0x62AA);
  if(player2.health>=10 & player2.health<100){FillRect(200,46,40,10,0x62AA); LCD_Print(vida2,205,46,1,0x000,0x62AA);}
  if (player2.health<10) {FillRect(200,46,40,10,0x62AA); LCD_Print(vida2,215,46,1,0x000,0x62AA);}
  LCD_Print("/100",225,46,1,0x0000,0x62AA);
  }

void choosePlayers(){
  //imprime cuadros alrededor de la seleccion de personaje, para indicar que personaje se utilizara en la pelea
  switch(player1.skinsel){
    case 0: //seleccionar el segundo personaje
      Rect(100,60,32,32,0x00);
      Rect(100,120,32,32,0xE841);
      break;
    case 1: //seleccionar el primer personaje
      Rect(100,60,32,32,0xE841);
      Rect(100,120,32,32,0x00);
      break;
    
    }

  switch(player2.skinsel){
    case 0: //seleccionar el segundo personaje
      Rect(200,60,32,32,0x00);
      Rect(200,120,32,32,0xE841);
      break;
    case 1: //seleccionar el primer personaje
      Rect(200,60,32,32,0xE841);
      Rect(200,120,32,32,0x00);
      break;
    }
  }
