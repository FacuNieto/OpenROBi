#include <SPI.h>

//////////Servos/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> //Funcionando en version 2.3.1 (ahora esta la 2.4 tener cuidado)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 //175 this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  550 //575 this is the 'maximum' pulse length count (out of 4096)
#define FREQUENCY  50
//////////Servos/////////


/////////Variables///////////
// our servo # counter
uint8_t servonum = 0;
//Falan grandes
int pos1 = 350;
int pos2 = 350;
int pos3 = 350;
int pos4 = 350;
//Falan pequeñas
int pos11 = 350;
int pos22 = 350;
int pos33 = 350;
int pos44 = 350;

int pospri = 0;
int posx = 350;
int posxX = 350;
int posy = 350;
int posyY = 350;
int posz = 350;
int controlA = A0;
int controlB = A1;
int controlC = A2;
//boton
int boton1 = 11 ;
int VALOR = 0;

// motores Brazo
int motorZ = 0;
int motorA = 1 ;
int motorAa = 2 ;
int motorB = 3;
int motorBb = 4 ;

// Motores Dedos:
int motor1 = 5 ; //Falange proximal meñique
int motor2 = 6 ; //Falange proximal anular
int motor3 = 7 ; //Falange proximal medio
int motor4 = 8 ; //Falange proximal indice
int motor5 = 9 ; //Metacarpiano pulgar 1
int motor6 = 10 ; //Metacarpiano pulgar 2
int motor1b = 11 ; //falange distal


//
int pos ;
int a ;
int k = 20 ;

char TECLA;       // almacena la tecla presionada
String funciona;
/////////Variables///////////


void moverMotorPote( int pote, int motor)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(potVal, 0, 1023, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  //  Serial.println(potVal);

}

void moverMotorPoteCustom( int pote, int motor, int bajo, int alto)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(potVal, bajo, alto, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  //  Serial.println(potVal);

}

void moverMotorValorCustom( int valor, int motor, int bajo, int alto)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  //  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(valor, bajo, alto, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  //  Serial.println(potVal);

}

void moverMotorEntrada( int entrada, int motor)
{
  int pulse_wide, pulse_width;

  // lector de valores del potenciometro


  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(entrada, 0, 1000, 100, 2300);//acele
  //pulse_wide = map(entrada, -32768, 32768, 100, 2300);//gyro
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  Serial.println(entrada);
}


void moverMotorDoblePote( int pote, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(potVal, 0, 1023, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  //Serial.println(potVal);
  // delay (10);

}

void moverMotorDoblePoteCustom( int pote, int motor1, int motor2, int bajo, int alto )
{
  int pulse_wide, ancho_pulso1, ancho_pulso2, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(potVal, bajo, alto, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  //Serial.println(potVal);
  // delay (10);

}

void moverMotorDobleValorCustom( int valor, int motor1, int motor2, int bajo, int alto )
{
  int pulse_wide, ancho_pulso1, ancho_pulso2, potVal;

  // lector de valores del potenciometro

  //  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(valor, bajo, alto, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  //Serial.println(potVal);
  // delay (10);

}

void moverMotorDobleEntrada( int entrada, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2;

  // lector de valores del potenciometro

  // potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  // pulse_wide = map(ejeacelerometro, 0, 1023, 250, 2300);
  pulse_wide = map(entrada, 0, 1000, 250, 2300);
  // pulse_wide = map(ejeacelerometro, -32768, 32768, 100, 2300);//gyro

  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  ancho_pulso2 = ancho_pulso2 + 30; //correccion
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  Serial.println(ancho_pulso1);
  Serial.println(ancho_pulso2);

  // delay (10);

}

void moverMotorDobleBlue( int ejeacelerometro, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2;

  // lector de valores del potenciometro

  // potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  // pulse_wide = map(ejeacelerometro, 0, 1023, 250, 2300);
  pulse_wide = map(ejeacelerometro, 0, 255, 250, 2300);
  // pulse_wide = map(ejeacelerometro, -32768, 32768, 100, 2300);//gyro

  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  ancho_pulso2 = ancho_pulso2 + 30; //correccion
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  Serial.println(ancho_pulso1);
  Serial.println(ancho_pulso2);

  // delay (10);

}



void moverMotorBlue( int pot, int motor)
{
  int pulse_wide, pulse_width;
  // lector de valores del potenciometro
  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(pot, 0, 255, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  Serial.println(pot);

}

void moverMotorInversoBlue( int pot, int motor)
{
  int pulse_wide, pulse_width1, pulse_width2;

  // lector de valores del potenciometro
  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(pot, 0, 255, 100, 2300);
  pulse_width1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  pulse_width2 = map (pulse_width1, 150 , 500 , 500, 150);

  pwm.setPWM(motor, 0, pulse_width2);
  Serial.println(pot);

}

////////Funciones////////////


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  //////////// Servos ////////////
  pwm.begin();
  pwm.setPWMFreq(60);  // Revisar frecuencia 50 o 60 Hz
  //////////// Servos ////////////
  pinMode(LED_BUILTIN, OUTPUT);
}


#define alpha 0.05  //Alpha

int Valorfiltrado1 = 0;
int Valorfiltrado2 = 0;
int Valorfiltrado3 = 0;
int Valorfiltrado4 = 0;
int Valorfiltrado5 = 0;
int entrada1 = 0;
int entrada2 = 0;
int entrada3 = 0;
int entrada4 = 0;
int entrada5 = 0;
int aux = 0;
int aux2 = 0;

char lectura ;

void loop() {
  entrada1 = analogRead(0);
  entrada2 = analogRead(1);
  entrada3 = analogRead(2);
  entrada4 = analogRead(3);
  entrada5 = analogRead(4);

  Valorfiltrado1 = (alpha * entrada1) + ((1 - alpha) * Valorfiltrado1);
  Valorfiltrado2 = (alpha * entrada2) + ((1 - alpha) * Valorfiltrado2);
  Valorfiltrado3 = (alpha * entrada3) + ((1 - alpha) * Valorfiltrado3);
  Valorfiltrado4 = (alpha * entrada4) + ((1 - alpha) * Valorfiltrado4);
  Valorfiltrado5 = (alpha * entrada5) + ((1 - alpha) * Valorfiltrado5);

  aux = int(map(Valorfiltrado1, 0, 1024, 180, 540));
  aux2 = int(map(Valorfiltrado2, 0, 1024, 180, 540));

  //Serial.println(afaf);
//  delay(10);
  
//  if (Serial.available() > 0) {
//
//    delay(10);
    lectura = Serial.read();
//    delay(10);
//
    String astring = String(aux, DEC);
        String bstring = String(aux2, DEC);

//
    if (lectura == 't' ) {
//
//      delay(200);
      Serial.println(astring + ',' + bstring );
      delay(15);
      Serial.end();
      Serial.begin(115200);
//
    }
//  }


  //Serial.println(map(Valorfiltrado1,0,1023,0,180));
  //
  //Serial.print(",");
  //Serial.print(Valorfiltrado2);
  //Serial.print(",");
  //Serial.print(Valorfiltrado3);
  //Serial.print(",");
  //Serial.print(Valorfiltrado4);
  //Serial.print(",");
  //Serial.print(Valorfiltrado5);
  //Serial.print(",");
  //Serial.println(analogRead(5));

  ////moverMotorPote( 0, 0);
  //moverMotorValorCustom( Valorfiltrado1, 0, 510, 170); //abduccion aduccion deltoides medial
  ////moverMotorDoblePote( 1, 1, 2);
  //moverMotorDobleValorCustom( Valorfiltrado2, 1, 2, 400, 710 );//flexo extensión deltoides anterior
  ////moverMotorDoblePote( 2, 3, 4);
  //moverMotorDobleValorCustom( Valorfiltrado3, 3, 4, 190, 600 );//flexo extensión articulación glenohumeral
  ////moverMotorPote( 3, 5);
  //moverMotorValorCustom( Valorfiltrado4, 5, 0, 650);
  ////moverMotorPote( 4, 6);
  //moverMotorValorCustom(Valorfiltrado5, 6, 20, 500);
  ////moverMotorPote( 5, 7);


  //      for (pos = 250; pos <= 750; pos += 1) { // bajada
  //
  //        moverMotorEntrada( pos, 0);
  //        moverMotorDobleEntrada( pos+500, 1, 2);
  ////        pospri = map(pos, 100, 600, 600, 100);
  ////        pwm.setPWM(0, 0, posz  = pos);
  ////        pwm.setPWM(1, 0, posx  = pos);
  ////        pwm.setPWM(2, 0, posxX = pospri);
  ////        pwm.setPWM(3, 0, posy  = pos);
  ////        pwm.setPWM(4, 0, posyY = pospri);
  //        delay(10);
  //      }
  //      for (pos = 750; pos >= 250; pos -= 1) { // bajada
  //
  //        moverMotorEntrada( pos, 0);
  //        moverMotorDobleEntrada( pos-500, 1, 2);
  ////        pospri = map(pos, 100, 600, 600, 100);
  ////        pwm.setPWM(0, 0, posz  = pos);
  ////        pwm.setPWM(1, 0, posx  = pos);
  ////        pwm.setPWM(2, 0, posxX = pospri);
  ////        pwm.setPWM(3, 0, posy  = pos);
  ////        pwm.setPWM(4, 0, posyY = pospri);
  //        delay(10);
  //      }

}
