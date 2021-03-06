 /* 
  Valerie Valdez                                                                  Carné: 19659
  Universidad del Valle de Guatemala                                              Sección 10
  
                                          Electrónica Digital
                                              Proyecto # 2
                                       Controles para el juego
 */

//******************************************************************************************
//                                  V A R I A B L E S 
//******************************************************************************************
char Message;                         // Variable para la comunicación serial
const int pushB1 = 2;                 // Botón 1er jugador attached pin 2
const int pushB2 = 3;                 // Botón especial attached pin 3
const int pushB3 = 4;                 // El otro especial attached pin 4
const int pushB4 = 5;                 // Botón 1er jugador attached pin 5
const int pushB5 = 6;                 // Botón especial attached pin 6
const int pushB6 = 7;                 // El otro especial attached pin 7
const int START = 8;                  // Botón de inicio attached al pin 8

int FLAG = 0;                         // Banderas para los botones
int FLAG2 = 0;                        // Banderas para los botones
int FLAG3 = 0;                        // Banderas para los botones
int FLAG4 = 0;                        // Banderas para los botones
int FLAG5 = 0;                        // Banderas para los botones
int FLAG6 = 0;                        // Banderas para los botones
int FLAG7 = 0;                        // Banderas para los botones

unsigned char INICIO = 1;             // Flag para el Inicio

//******************************************************************************************
//                                     S E T   U P 
//******************************************************************************************
void setup() {
  Serial.begin(9600);                 // Inicializar C. serial a 9600 bits per second
  delay(100);
  pinMode(pushB1, INPUT_PULLUP);      // Hacer el pin un input pull up  
  pinMode(pushB2, INPUT_PULLUP);        
  pinMode(pushB3, INPUT_PULLUP);      
  pinMode(pushB4, INPUT_PULLUP);      // Botón 2do jugador 
  pinMode(pushB5, INPUT_PULLUP);      // Botón especial 
  pinMode(pushB6, INPUT_PULLUP);      // El otro especial
  pinMode(START, INPUT_PULLUP);     
  
  pinMode(11,OUTPUT);                  // Pin para el Buzer jugador 1
  pinMode(12,OUTPUT);                  // Pin buzzer jugador 2

}

//*****************************************************************************************
//                               L O O P   P R I N C I P A L
//*****************************************************************************************
void loop() {
    delay(10);
    if (digitalRead(START) == HIGH){    // Botón para iniciar
        FLAG7 = 1;                      // Bandera para el antirrebote
          }
    else{
        if(FLAG7 == 1){                 // Si la FLAG está encendida entonces apgarla
           FLAG7 = 0;                   // Apagar bandera   
           Serial.write('0');

          // Música de inicio
          tone(12,1174.7);              // D
          delay(350);
          noTone(12);
          delay(55);
          tone(12,1174.7);              // D
          delay(125);
          noTone(12);
          delay(25);
          tone(12,1174.7);              // D
          delay(125);
          noTone(12);
          delay(60);
          tone(12,1174.7);              // D
          delay(125);
          noTone(12);
          delay(60);
          
          tone(12,1318.5);              // D#
          delay(350);
            noTone(12);
          delay(70);   
          tone(12,1318.5);              // D#
          delay(275);
          noTone(12);
          delay(90);
          
          tone(12,1480);                // E
          delay(400);
          noTone(12);  
          delay(70);
        
          tone(12,1174.7);              // D
          delay(350);
          noTone(12);
          delay(70);
          
          tone(12,1318.5);             // D#
          delay(600);
          noTone(12);
          delay(100);

           INICIO = 0;
           }
       }
       

//                    P R I M E R   J U G A D O R

    if (INICIO == 0){                  // Si no se precionó START entonces no comienza

    if (digitalRead(pushB1) == HIGH){  // Primer botón: primer jugador
        FLAG = 1;                      // Bandera para el antirrebote
          }
    else{
        if(FLAG == 1){                 // Si la FLAG está encendida entonces apgarla
           FLAG = 0;                   // Apagar bandera   
           Serial.write('1');          // Se envía el dato ASCII = 1

           tone(11,392);               // Tonos para el ataque normal
           delay(20);
           noTone(11);
           delay(10);
           tone(11, 1000);
           delay(20);
           noTone(11);
           tone(11,500);
           noTone(11);     
           }
        }


    if (digitalRead(pushB2) == HIGH){  // Segundo botón: Botón especial
        FLAG2 = 1;                     // Bandera para el antirrebote
          }
    else{
        if(FLAG2 == 1){                // Si la FLAG está encendida entonces apgarla
           FLAG2 = 0;                  // Apagar bandera   
           Serial.write('2');          // Se envía el dato ASCII = 2
                     
           tone(11,50);                // Tonos para el ataque especial
           delay(7);
           noTone(11);
           delay(15);
           tone(11, 600);
           delay(10);
           noTone(11);
           tone(11,900);
           delay(15);
           noTone(11);
           }
        }


    if (digitalRead(pushB3) == HIGH){  // Tercer botón: EL otro especial
        FLAG3 = 1;                     // Bandera para el antirrebote
          }
    else{
        if(FLAG3 == 1){                // Si la FLAG está encendida entonces apgarla
           FLAG3 = 0;                  // Apagar bandera   
           Serial.write('3');          // Se envía el dato ASCII = 3

             tone(11,1);               // Tono del otro especial
             tone(11,300);   
             delay(20);
             tone(11, 500);
             delay(15);
             noTone(11);
           }
        }



//                 S E G U N D O    J U G A D O R 
    if (digitalRead(pushB4) == HIGH){  // Cuarto botón: 1ero del 2do
        FLAG4 = 1;                     // Bandera para el antirrebote
          }
    else{
        if(FLAG4 == 1){                // Si la FLAG está encendida entonces apgarla
           FLAG4 = 0;                  // Apagar bandera   
           Serial.write('4');          // Se envía el dato ASCII = 4
           
           tone(12,392);               // Tonos para el ataque normal
           delay(20);
           noTone(12);
           delay(10);
           tone(12, 1000);
           delay(20);
           noTone(12);
           tone(12,500);
           noTone(12);  
           }
        }


    if (digitalRead(pushB5) == HIGH){  // Quinto botón: 2do Especial
        FLAG5 = 1;                     // Bandera para el antirrebote
          }
    else{
        if(FLAG5 == 1){                // Si la FLAG está encendida entonces apgarla
           FLAG5 = 0;                  // Apagar bandera   
           Serial.write('5');          // Se envía el dato ASCII = 5
           
           tone(12,50);                // Tonos para el ataque especial
           delay(7);
           noTone(12);
           delay(15);
           tone(12, 600);
           delay(10);
           noTone(12);
           tone(12,900);
           delay(15);
           noTone(12);
           }
        }

    if (digitalRead(pushB6) == HIGH){   // Tercer botón: 2do El otro especial
        FLAG6 = 1;                      // Bandera para el antirrebote
          }
    else{
        if(FLAG6 == 1){                 // Si la FLAG está encendida entonces apgarla
           FLAG6 = 0;                   // Apagar bandera   
           Serial.write('6');           // Se envía el dato ASCII = 6
           
           tone(12,1);                  // Tono del otro especial
           tone(12,300);   
           delay(20);
           tone(12, 500);
           delay(15);
           noTone(12);
           }
        }


//             R E C I B I R    C O N    S E R I A L 
    if (Serial.available()){                      
       Message = Serial.read();          // Guardar lo leído en Message
        Serial.write(Message);
       delay(4);
      
        if(Message == 65){                 // Recibe un 1
          Serial.write('B');
          tone(11,392);                    // Tono del otro especial
          delay(60);
          noTone(11);
          delay(100);
          tone(11, 523.25);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,659.26);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,783.99);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1046.25);
          delay(60);
          noTone(11);
          delay(100);
          tone(11, 1318.5);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1568);
          delay(250);
          noTone(11);
          delay(60);
          tone(11, 1318.5);
          delay(250);
          noTone(11);
          delay(60);
        // Otra vez
          tone(11,415.3);
          delay(60);
          noTone(11);
          delay(100);
          tone(11, 523.25);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,622);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,830.61);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1046.25);
          delay(60);
          noTone(11);
          delay(100);
          tone(11, 1244.5);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1661.2);
          delay(250);
          noTone(11);
          delay(60);
          tone(11, 1244.5);
          delay(250);
          noTone(11);
          delay(60);
          // Última parte
          tone(11,466.16);
          delay(60);
          noTone(11);
          delay(80);
          tone(11, 587.33);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,698.46);
          delay(60);
          noTone(11);
          delay(60);
          tone(11,932.33);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1174.7);
          delay(60);
          noTone(11);
          delay(100);
          tone(11, 1396.9);
          delay(60);
          noTone(11);
          delay(60);
          tone(11, 1864.7);
          delay(250);
          noTone(11);
          delay(60);
          tone(11, 1864.7);
          delay(75);
          noTone(11);
          delay(60);
          tone(11, 1864.7);
          delay(75);
          noTone(11);
          delay(60);
          tone(11, 1864.7);
          delay(65);
          noTone(11);
          delay(50);
          tone(11, 2100);
          delay(350);
          noTone(11);
          delay(60);
          delay(1000);
          INICIO = 1; 
        }
        
        if(Message == 66){                 
          tone(12,392);                    // Tono del otro especial
          delay(60);
          noTone(12);
          delay(100);
          tone(12, 523.25);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,659.26);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,783.99);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1046.25);
          delay(60);
          noTone(12);
          delay(100);
          tone(12, 1318.5);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1568);
          delay(250);
          noTone(12);
          delay(60);
          tone(12, 1318.5);
          delay(250);
          noTone(12);
          delay(60);
        // Otra vez
          tone(12,415.3);
          delay(60);
          noTone(12);
          delay(100);
          tone(12, 523.25);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,622);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,830.61);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1046.25);
          delay(60);
          noTone(12);
          delay(100);
          tone(12, 1244.5);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1661.2);
          delay(250);
          noTone(12);
          delay(60);
          tone(12, 1244.5);
          delay(250);
          noTone(12);
          delay(60);
          // Última parte
          tone(12,466.16);
          delay(60);
          noTone(12);
          delay(80);
          tone(12, 587.33);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,698.46);
          delay(60);
          noTone(12);
          delay(60);
          tone(12,932.33);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1174.7);
          delay(60);
          noTone(12);
          delay(100);
          tone(12, 1396.9);
          delay(60);
          noTone(12);
          delay(60);
          tone(12, 1864.7);
          delay(250);
          noTone(12);
          delay(60);
          tone(12, 1864.7);
          delay(75);
          noTone(12);
          delay(60);
          tone(12, 1864.7);
          delay(75);
          noTone(12);
          delay(60);
          tone(12, 1864.7);
          delay(65);
          noTone(12);
          delay(50);
          tone(12, 2100);
          delay(350);
          noTone(12);
          delay(60);
          delay(1000);
          INICIO = 1; 
            }
    }
  }
}
