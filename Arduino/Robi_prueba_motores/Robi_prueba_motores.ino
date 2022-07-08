#include <SPI.h>

//////////Servos/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> //Funcionando en version 2.3.1 (ahora esta la 2.4 tener cuidado)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
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
  pulse_wide = map(valor, bajo, alto, 150, 3000);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  //  Serial.println(potVal);

}

void moverMotorValorCustom2( int valor, int motor, int bajo, int alto)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  //  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(valor, bajo, alto, 250, 3000);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm2.setPWM(motor, 0, pulse_width);
  //  Serial.println(potVal);

}

void moverMotorValorMANOANTERIORCustom2( int valor,  int bajo, int alto)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  //  potVal = analogRead(pote);

  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(valor, bajo, alto, 460, 2700);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm2.setPWM(1, 0, pulse_width);
  pwm2.setPWM(2, 0, pulse_width);
  pwm2.setPWM(3, 0, pulse_width);
  pwm2.setPWM(4, 0, pulse_width);
  pwm2.setPWM(5, 0, pulse_width);
  pwm2.setPWM(6, 0, pulse_width);

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
//  pulse_wide = map(valor, bajo, alto, 150, 2700);
  pulse_wide = map(valor, bajo, alto, 1425, 2700);

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


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

////////Funciones////////////


void setup() {
  // put your setup code here, to run once:

    Serial.begin(500000);

  while (!Serial) {
  }
  Serial.setTimeout(1);

  delay(10);

  //////////// Servos ////////////
  pwm.begin();
  pwm.setPWMFreq(60);  // Revisar frecuencia 50 o 60 Hz

  pwm2.begin();
  pwm2.setPWMFreq(60);  // Revisar frecuencia 50 o 60 Hz
  
  //////////// Servos ////////////
  pinMode(LED_BUILTIN, OUTPUT);
}


#define alpha 0.02  //Alpha

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

int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0 ;
int c5 = 0 ;

String deltmedval;
String deltantval;
String bicval;
String pronval;
//String muñeval;
String falangval;

String serialData;
int pin = 13;

void loop() {
  
//  entrada1 = analogRead(0);
//  entrada2 = analogRead(1);
//  entrada3 = analogRead(2);
//  entrada4 = analogRead(3);
//  entrada5 = analogRead(4);
//  Valorfiltrado1 = (alpha * entrada1) + ((1 - alpha) * Valorfiltrado1);
//  Valorfiltrado2 = (alpha * entrada2) + ((1 - alpha) * Valorfiltrado2);
//  Valorfiltrado3 = (alpha * entrada3) + ((1 - alpha) * Valorfiltrado3);
//  Valorfiltrado4 = (alpha * entrada4) + ((1 - alpha) * Valorfiltrado4);
//  Valorfiltrado5 = (alpha * entrada5) + ((1 - alpha) * Valorfiltrado5);


  if (Serial.available() > 0) {
    serialData = Serial.readString();
    deltmedval = getValue(serialData, ',', 0);
    deltantval = getValue(serialData, ',', 1);
    bicval = getValue(serialData, ',', 2);
    pronval = getValue(serialData, ',', 3);
    falangval = getValue(serialData, ',', 4);

    c1 = deltmedval.toInt();
    c2 = deltantval.toInt();
    c3 = bicval.toInt();
    c4 = pronval.toInt();
    c5 = falangval.toInt();

  }
//      Serial.println(c1);
//    Serial.println(c2);

//  moverMotorValorCustom( c1, 7, -150, 999); //abduccion aduccion deltoides medial
  moverMotorValorCustom( c1, 7, -150, 999); //abduccion aduccion deltoides medial
  moverMotorDobleValorCustom( c2, 1, 2, 1200, 0 );// deltoides anterior
  moverMotorDobleValorCustom( c3, 3, 4, 2000, 0 );
  moverMotorValorCustom2( c4, 15, -150, 999);
  moverMotorValorMANOANTERIORCustom2( c5,  100,0);


  ////moverMotorPote( 0, 0);

//  moverMotorValorCustomMG90( Valorfiltrado1, 5, -150, 999);
//  moverMotorValorMANOANTERIORCustom2( Valorfiltrado1,  -150, 1000);
//  moverMotorDobleValorCustom( Valorfiltrado1, 1, 2, -900, 1000 );
//  moverMotorDobleValorCustom( Valorfiltrado1, 3, 4, -1000, 1000 );



//suavizador
delay(10);
//suavizador

// moverMotorValorCustom2( Valorfiltrado2, 15, -150, 999);
//  moverMotorDoblePote( 1, 1, 2);
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
