#include "SDcard.h"
#include "TFT_ili9341.h"
#include <SPI.h>
#include <SD.h>
#define LCD_CS PD_1
#define LCD_RS PD_2

void ListaNombres(File archivo,String archives[]){
  int n = 0; //para cada uno de los archivos que pueden existir
  while(true){
    File dummy = archivo.openNextFile(); //abre el siguiente archivo
    if(!dummy){ break;} //deja de hacerlo, no hay mas archivos
    archives[n] = dummy.name(); //agrega los nombres de los archivos
    n++; //lo coloca en el siguiente string
    }
  }

void imprimirArchivo(const char *nombre){
  File archivo; //dummy para la funcion
  archivo = SD.open(nombre,FILE_READ); //abre el archivo con el nombre en modo lectura
  if (archivo){ //si esta disponible
    Serial.println(nombre);
    while(archivo.available()){ //imprime su nombre y sus lineas hasta encontrar un vacio
      Serial.write(archivo.read());
      }
      archivo.close();
    }
  else{ //imprime que es error de apertura
    Serial.println("error de apertura");
    }
    
  
  }

int hex2bin(char c){ //convertir los hex del texto en binario
  if (c >= '0' && c <= '9') //numeros
    return c - '0' ;
  if (c >= 'A' && c <= 'F')//letras en mayusculas
    return c - 'A' + 10 ;
  if (c >= 'a' && c <= 'f')//letras en minusculas
    return c - 'a' + 10 ;
}

void bitmapSD(File f,unsigned int w,unsigned int h,unsigned int posx,unsigned int posy){
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  
  SetWindows(posx,posy,posx+w-1,posy+h-1); //para indicar que escribe en toda la pantalla
  
  uint8_t color; //almacenar el valor entero del dato
  uint8_t color2; //almacenar el valor entero del dato
  f.seek(0); //colocar al inicio del archivo por seguridad
  while(f.available()){
    color  = hex2bin(f.read());
    color2 = hex2bin(f.read());
    unsigned char color3 = (color*16) + color2; //MSB y LSB obtenidos del texto
    LCD_DATA(color3); //imprimir parte por parte
  }
   digitalWrite(LCD_CS, HIGH);
  
  }

void spriteSD(File f,unsigned int x,unsigned int y){
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  unsigned int x2,y2;
  x2 = x+31;
  y2 = y+31;
  SetWindows(x,y,x2,y2); //para indicar que escribe en toda la pantalla
  
  uint8_t color; //almacenar el valor entero del dato
  uint8_t color2; //almacenar el valor entero del dato
  f.seek(0); //colocar al inicio del archivo por seguridad
  while(f.available()){
    color  = hex2bin(f.read());
    color2 = hex2bin(f.read());
    unsigned char color3 = (color*16) + color2; //MSB y LSB obtenidos del texto
    LCD_DATA(color3); //imprimir parte por parte
  }
   digitalWrite(LCD_CS, HIGH);
  
  }
