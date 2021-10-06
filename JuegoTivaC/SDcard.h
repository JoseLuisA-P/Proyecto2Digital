#ifndef _SD_CARD_H
#define _SD_CARD_H

#ifndef _ENERGIA_H_
#include <Energia.h>
#endif
#include <SD.h>

void ListaNombres(File archivo,String archives[]);
void imprimirArchivo(const char *nombre);
int hex2bin(char c);
void bitmapSD(File f, int w, int h);
void spriteSD(File f,unsigned int x,unsigned int y);

#endif
