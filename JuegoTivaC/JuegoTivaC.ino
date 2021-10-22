#include "TFT_ili9341.h"
#include "SDcard.h"
#include <SPI.h>
#include <SD.h>
#include "Personaje.h"

Personaje player1(0,30,30,60,120); //objeto del personaje 1
Personaje player2(2,200,30,225,120); //objeto del personaje 2

File lectura; //para leer un archivo de la SD
uint8_t animacion = 0; //mover las animaciones de los personajes
uint8_t mensel = 0; //seleccionar el menu
bool onete, onete2; //utilizado para activar los eventos de una sola vez
unsigned long prevTime = 0; //para el delay sin detener la ejecucion
int intervalo; //intervalo para los cambios de bitmap en los personajes o titulos que titilan
int inMes; //mensaje obtenido por el serial
short P1sel, P2sel; //seleccionar los personajes y atributos de cada uno
uint8_t atckVal; //valor del ataque tipo random
short turno;//seleccionar el turno del personaje
short skip1, skip2; //para saltar turno de personaje 1 o 2
short healtick1,healtick2; //cooldown de habilidad especial de personaje 1 o 2
bool ganador; //para ver quien es el ganador

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
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

  LCD_Clear(0x0000);
  LCD_Print("Integrantes:",30,30,2,0xffff,0x0000);
  LCD_Print("Jose Alvarez",30,60,2,0xffff,0x0000);
  LCD_Print("19392",30,90,2,0xffff,0x0000);
  LCD_Print("Valerie Valdez",30,120,2,0xffff,0x0000);
  LCD_Print("19659",30,150,2,0xffff,0x0000);
  delay(5000);
  
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
      if(onete) { 
        lectura = SD.open("OPSCREEN.TXT",FILE_READ);
        bitmapSD(lectura,320,240,0,0);
        lectura.close();
        onete = 0;
        } //para imprimir una vez el texto de inicio
      
      if(animacion)LCD_Print("Presiona el boton para comenzar",50,200,1,0xffff,0x0000);
      else FillRect(50,200,250,30,0x0000); //animacion del texto de presionar START para ir a seleccion de personajes
      if(animacion > 1) animacion = 0; //dos estados para presionar, se modifica dependiendo la pantalla desplegada

      if(Serial3.available()){ //leer el dato enviado por el control
        inMes = Serial3.read();
        }

      if(inMes == '0')mensel = 1; //al presionar start cambia de pantalla
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de seleccion de personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
    case 1:
    
      if(onete == 0){  //preparando el evento de una vez para la pelea y colocando la pantalla de seleccion
        lectura = SD.open("SELPLAY.TXT",FILE_READ);
        bitmapSD(lectura,320,240,0,0);
        lectura.close();
        printPlayers();
        onete= 1; 
        inMes = 0;
        }
        
      if(Serial3.available()){ //leer el dato enviado por el control
        inMes = Serial3.read();
        switch(inMes){ //dependiendo del valor seleccionado, asi cambia la seleccion del personaje
          case '1':
            player1.skinsel ++;
            if(player1.skinsel>1)player1.skinsel = 0; //solo dos estados de cambio
            break;
          case '4':
            player2.skinsel ++;
            if(player2.skinsel >1)player2.skinsel = 0; //solo dos estados
            break;
          }
          choosePlayers();
          
        }

        if (inMes == '0'){
          mensel = 2;
          LCD_Clear(0x0000);
          lectura = SD.open("FONPEL.TXT", FILE_READ); //FONDO DE LA PELEA
          bitmapSD(lectura,320,240,0,0);
          lectura.close();
          player1.init();
          player2.init();
          printIcon();
          updateLife();
          inMes = 0;
          intervalo = 200;
          onete = 1;
          healtick1 = 3;
          healtick2 = 3;
          skip1 = 0;
          skip2 = 0;
          }
        else inMes = 0;
      break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de la pelea de personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 2: //pantalla de la pelea 
      randomSeed(prevTime%10); //generar valores aleatorios variados
      if(onete){ //asegurar las poses como las iniciales
        onete = 0; 
        animacion  = 0;
        player1.pose = animacion;
        player2.pose = animacion;
        short turnodec = random(1,11);
        if(turnodec<5) turno = 0;
        if(turnodec>5) turno = 1;
        }
     
      player1.updateSp(); //actualizar la posicion de los personajes
      player2.updateSp();
      if(skip1 == 0)player1.pose = animacion; //actualizar a los nuevos valores
      else player1.pose = 1; //carga del ataque
      if(skip2 == 0)player2.pose = animacion;
      else player2.pose = 1; //carga del ataque
      if(animacion > 1) animacion = 0; //no pasarse de las posiciones de los personajes
      if(Serial3.available()){ //leer el dato enviado por el control
        inMes = Serial3.read();
        }
      if(!turno) LCD_Print("Turno P1",100,82,2,0x0000,0xFFFF); //indicar el turno de los personajes
      else LCD_Print("Turno P2",100,82,2,0x0000,0xFFFF);
      
      switch(turno){
        case 0: //el personaje 1 puede atacar
          if(skip1 == 2){ //luego de saltar el turno, ataca y salta turno
            if(player1.health > 30)atckVal = random(20,50); //valores aleatorios de ataque normal
            if(player1.health < 30)atckVal = random(30,60);
            rutinaAtaque1(atckVal); //rutina de daño a P2 y animacion P1
            updateLife();
            delay(500);
            skip1 = 0;
            turno = 1;
            }
          if(skip1 == 1){ //salta el turno e indica quien debe de cambiar
            skip1 = 2;
            FillRect(100,82,200,20,0xFFFF);
            LCD_Print("P1 SKIP",110,82,2,0x0000,0xFFFF);
            delay(1000);
            turno = 1;
            }
          if(skip1 == 0){
          switch(inMes){
            case '1':
              updateSelAtk(0);
              delay(200);
              atckVal = random(10,15); //valores aleatorios de ataque normal
              rutinaAtaque1(atckVal); //rutina de daño a P2 y animacion P1
              updateLife();
              delay(200);
              turno = 1;
              break;
            case '2':
              updateSelAtk(1);
              delay(200);
              skip1 = 1;
              turno = 1;
              break;
            case '3':
              updateSelAtk(2);
              delay(200);
              uint8_t san1 = random(12,21); //valor aleatorio para curar
              if(healtick1 > 0){ //solamente si aun puede seguir curando
                player1.healdamage(san1); //sanar al personaje y actualizar barra de vida
                updateLife(); //actualizar la vida numerica
                healtick1--; //disminuir las veces para curar
                updateHealing1(healtick1); //actualizar el indicador para curar
                turno = 1;
              }  
              break;
            }
          }
          break;
          
        case 1: //el personaje 2 puede atacar
            if(skip2 == 2){ //luego de saltar el turno, ataca y salta turno
              if(player2.health > 30)atckVal = random(20,50); //valores aleatorios de ataque normal
              if(player2.health < 30)atckVal = random(30,60);
              rutinaAtaque2(atckVal);//rutina de daño a P1 y animacion P2
              updateLife();
              delay(500);
              skip2 = 0;
              turno = 0;
            }
            
            if(skip2 == 1){//salta el turno e indica quien debe de cambiar
              skip2 = 2;
              FillRect(100,82,200,20,0xFFFF);
              LCD_Print("P2 SKIP",110,82,2,0x0000,0xFFFF);
              delay(1000);
              turno = 0;
            }
            
           if(skip2 == 0){
            switch(inMes){
            case '4':
              updateSelAtk(3);
              delay(200);
              atckVal = random(10,15); //valores aleatorios de ataque normal
              rutinaAtaque2(atckVal); //rutina de daño a P1 y animacion P2
              updateLife();
              delay(200);
              turno = 0;
              break;
            case '5':
              updateSelAtk(4);
              delay(200);
              skip2 = 1;
              turno = 0;
              break;
            case '6':
              updateSelAtk(5);
              delay(200);
              uint8_t san2 = random(12,21);
              if(healtick2 > 0){
              player2.healdamage(san2);
              updateLife();
              healtick2--;
              updateHealing2(healtick2);
              turno = 0;
              }
              break;
            }
          }
          break;
        }
      
      inMes = 0;

      if(player1.health == 0)mensel = 3;
      if(player2.health == 0)mensel = 4;
      
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de victoria de uno de los personajes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 3:
      LCD_Clear(0x0000);
      LCD_Print("GANADOR P2",80,30,2,0xFFFF,0x0000);
      mensel = 5;
      ganador = 1;
      intervalo = 500;
      if((2 + player2.skinsel) == 3)lectura = SD.open("NINA1.TXT", FILE_READ);
      if((2 + player2.skinsel) == 2)lectura = SD.open("ROJO1.TXT", FILE_READ);
      spriteSD(lectura,150,100);
      lectura.close();
      Serial3.write(66);
      break;
    case 4:
      LCD_Clear(0x0000);
      LCD_Print("GANADOR P1",80,30,2,0xFFFF,0x0000);
      mensel = 5;
      ganador = 0;
      intervalo = 500;
      if((player1.skinsel) == 1)lectura = SD.open("NINO1.TXT", FILE_READ);
      if((player1.skinsel) == 0)lectura = SD.open("AZUL1.TXT", FILE_READ);
      spriteSD(lectura,150,100);
      lectura.close();
      Serial3.write(65);
      break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //pantalla de reinicio y para reiniciar los parametros de los jugadores
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 5:
      if(animacion)LCD_Print("Presiona start volver",80,150,1,0xFFFF,0x0000);
      else FillRect(30,150,250,30,0x0000); //animacion del texto de presionar START para ir a seleccion de personajes
      if(animacion > 1) animacion = 0;
      if(Serial3.available()) inMes = Serial3.read();

      updateWinner(animacion);
      
      if(inMes == '0'){
        mensel = 0;
        LCD_Clear(0x0000);
        player1.health = 100;
        player2.health = 100;
        onete = 1;
      }
      else inMes = 0;
      
      break;
      
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Funciones utilizadas para desplegar personajes, objetos o seleccion.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printPlayers(){ //Colocar los bitmaps de los personajes en la pantalla
      lectura = SD.open("NINO1.TXT", FILE_READ);
      spriteSD(lectura,100,60);
      lectura.close();

      lectura = SD.open("NINA1.TXT", FILE_READ);
      spriteSD(lectura,200,60);
      lectura.close();

      lectura = SD.open("AZUL1.TXT", FILE_READ);
      spriteSD(lectura,100,120);
      lectura.close();
      
      lectura = SD.open("ROJO1.TXT", FILE_READ);
      spriteSD(lectura,200,120);
      lectura.close();
  
  }

void printIcon(){ //imprimir los iconos de ataque, vida y otros de la pantalla
    lectura = SD.open("HPICON.TXT", FILE_READ); //iconos de salud del persoaje
    bitmapSD(lectura,16,16,14,30);
    bitmapSD(lectura,16,16,184,30);
    lectura.close();

    lectura = SD.open("NATK.TXT",FILE_READ);
    bitmapSD(lectura,30,30,20,160); //ataque normal
    bitmapSD(lectura,30,30,190,160); //ataque normal
    lectura.close();    

    lectura = SD.open("CATK.TXT",FILE_READ);
    bitmapSD(lectura,30,30,60,160); //ataque cargado
    bitmapSD(lectura,30,30,230,160); //ataque cargado
    lectura.close();    

    lectura = SD.open("HATK.TXT",FILE_READ);
    bitmapSD(lectura,30,30,100,160); //sanarse
    bitmapSD(lectura,30,30,270,160); //sanarse
    lectura.close();    
    
    FillRect(18,194,34,20,0X4AC7); //diferenciadores de salud de personaje
    FillRect(58,194,34,20, 0X4AC7);
    FillRect(98,194,34,20, 0X4AC7);
    
    FillRect(20,196,30,16, 0X4FC7); //barras de salud para curar al personaje 1
    FillRect(60,196,30,16, 0X4FC7);
    FillRect(100,196,30,16, 0X4FC7);

    FillRect(188,194,34,20,0X4AC7); //diferenciadores de salud de personaje
    FillRect(228,194,34,20, 0X4AC7);
    FillRect(268,194,34,20, 0X4AC7);
    
    FillRect(190,196,30,16, 0X4FC7); //barras de salud para curar al personaje 2
    FillRect(230,196,30,16, 0X4FC7);
    FillRect(270,196,30,16, 0X4FC7);
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

void updateHealing1(short estado){
  //actualizar cuantas oportunidades para sanar quedan luego de haber utilizado el ataque para sanar.
  switch(estado){
      case 2:
      FillRect(100,196,30,16, 0X0000);
      break;
      case 1: 
      FillRect(60,196,30,16, 0X0000);
      break;
      case 0:
      FillRect(20,196,30,16, 0X0000);
      break;
    }
  }

void updateHealing2(short estado){
  //actualizar cuantas oportunidades para sanar quedan luego de haber utilizado el ataque para sanar.
  switch(estado){
      case 2:
      FillRect(270,196,30,16, 0X0000);
      break;
      case 1: 
      FillRect(230,196,30,16, 0X0000);
      break;
      case 0:
      FillRect(190,196,30,16, 0X0000);
      break;
    }
  }

void rutinaAtaque1(uint8_t ataque){ 
  //Rutina de ataques de P1, animacion de golpe P1 y recibir golpe P2, actualizar vida de P2 acorde al daño y la vida desplegada
  //asi como la barra de salud.
    player1.pose = 4;
    player1.updateSp();
    player2.pose = 3;
    player2.updateSp();
    player2.takedamage(ataque);
  }

void rutinaAtaque2(uint8_t ataque){
  //Rutina de ataques de P2, animacion de golpe P2 y recibir golpe P1, actualizar vida de P1 acorde al daño y la vida desplegada
  //asi como la barra de salud.
    player2.pose = 4;
    player2.updateSp();
    player1.pose = 3;
    player1.updateSp();
    player1.takedamage(atckVal);
  }

void updateSelAtk(short actualizar){
  switch(actualizar){
    case 0: //seleccionar primer ataque personaje 1
    Rect(20,160,30,30,0xE841);
    Rect(60,160,30,30,0x00);
    Rect(100,160,30,30,0x00);
    break;
    
    case 1: //seleccionar segundo ataque personaje 1
    Rect(20,160,30,30,0x00);
    Rect(60,160,30,30,0xE841);
    Rect(100,160,30,30,0x00);
    break;
    
    case 2: //seleccionar curacion personaje 1
    Rect(20,160,30,30,0x00);
    Rect(60,160,30,30,0x00);
    Rect(100,160,30,30,0xE841);
    break;
    
    case 3://seleccionar primer ataque personaje 2
    Rect(190,160,30,30,0xE841);
    Rect(230,160,30,30,0x00);
    Rect(270,160,30,30,0x00);
    break;
    
    case 4://seleccionar segundo ataque personaje 2
    Rect(190,160,30,30,0x00);
    Rect(230,160,30,30,0xE841);
    Rect(270,160,30,30,0x00);
    break;

    case 5://seleccionar curacion personaje 2
    Rect(190,160,30,30,0x00);
    Rect(230,160,30,30,0x00);
    Rect(270,160,30,30,0xE841);
    break;
    
    }
  }  

void updateWinner(uint8_t estado){
  switch(estado){
    case 0:
      lectura = SD.open("CROWN1.TXT", FILE_READ);
      spriteSD(lectura,150,65);
      lectura.close();
    break;
    case 1:
      lectura = SD.open("CROWN2.TXT", FILE_READ);
      spriteSD(lectura,150,65);
      lectura.close();
    break;
    }
  
  }
