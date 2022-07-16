// Copyright 2022 Facundo Nieto

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Este código permite la utilización de la interfaz grafica de Blynk para el control del brazo robótico
// La interfaz cuenta con potenciometros lineales digitales y una consola para el ingreso de comandos
// Se pueden mover todos los actuadores en todo su rango de movimiento y tambien se pueden realizar movimientos/poses predefinidos
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////Blue///////////
#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#include <SPI.h>
#include <BlynkSimpleSerialBLE.h>
char auth[] = "vUeeQgVthORBwRq6YFmfDlIrHvQojWBe";
WidgetTerminal terminal(V1);
//////////Blue///////////

//////////Servos/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 //175 this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  550 //575 this is the 'maximum' pulse length count (out of 4096)
#define FREQUENCY  50
//////////Servos/////////

//////////Filtro/////////
#define alpha 0.05   //Alpha
int ValorfiltradoX = 0;
int ValorfiltradoY = 0;
int ValorfiltradoZ = 0;
//////////Filtro/////////

//////////Acelerometro/////////
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
//////////Acelerometro/////////

  int acelex=0;
  int aceley= 0;
  int acelez=0;


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

////////Funciones////////////

BLYNK_WRITE(V1)
{

  if (String("1") == param.asStr()) {
    posx = posx + k;
    posxX = posxX - k;
    pwm.setPWM(1, 0, posx );
    pwm.setPWM(2, 0, posxX );
    terminal.println("1");
  }

  if (String("2") == param.asStr()) {
    posx = posx - k;
    posxX = posxX + k;
    pwm.setPWM(1, 0, posx);
    pwm.setPWM(2, 0, posxX);
    delay(10);
    terminal.println("2");
  }

  if (String("4") == param.asStr()) {
    posy = posy + k;
    posyY = posyY - k;
    pwm.setPWM(3, 0, posy);
    pwm.setPWM(4, 0, posyY);
    terminal.println("4");
  }

  if (String("5") == param.asStr()) {
    posy = posy - k;
    posyY = posyY + k;
    pwm.setPWM(3, 0, posy);
    pwm.setPWM(4, 0, posyY);
    terminal.println("5");
  }

  if (String("3") == param.asStr()) {
    ////////// izquierda
    posz = posz + k;
    pwm.setPWM(0, 0, posz);
    terminal.println("3");
  }
  if (String("6") == param.asStr()) {
    //derecha
    posz = posz - k;
    pwm.setPWM(0, 0, posz);
    terminal.println("6");
  }

  if (String("Inicio") == param.asStr()) {

    posx = 350;
    posxX = 350;
    posy = 350;
    posyY = 350;
    posz = 350;
    pwm.setPWM(1, 0, posx );
    pwm.setPWM(2, 0, posxX );
    pwm.setPWM(3, 0, posy );
    pwm.setPWM(4, 0, posyY );
    pwm.setPWM(0, 0, posz );
    terminal.println("Inicio");
  }
  
  if (String("x") == param.asStr()) { //ejemplo de rutina predefinida

    do {

      for (pos = 200; pos <= 550; pos += 2) { // subida

        pospri = map(pos, 100, 600, 600, 100);
        pwm.setPWM(0, 0, posz  = pos);
        pwm.setPWM(1, 0, posx  = pos);
        pwm.setPWM(2, 0, posxX = pospri);
        pwm.setPWM(3, 0, posy  = pos);
        pwm.setPWM(4, 0, posyY = pospri);
        delay(1);
      }
      
      for (pos = 550; pos >= 200; pos -= 2) { // bajada

        pospri = map(pos, 100, 600, 600, 100);
        pwm.setPWM(0, 0, posz  = pos);
        pwm.setPWM(1, 0, posx  = pos);
        pwm.setPWM(2, 0, posxX = pospri);
        pwm.setPWM(3, 0, posy  = pos);
        pwm.setPWM(4, 0, posyY = pospri);
        delay(1);
      }

   //   funciona = param.asStr();
    }
  //  while (funciona != "fin");
    while (param.asStr() == "x");

  }
  
  
  if (String("acelerometro") == param.asStr()) {

do {
 
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  // temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
ValorfiltradoX = (alpha*accelerometer_x) + ((1-alpha)*ValorfiltradoX);
ValorfiltradoY = (alpha*accelerometer_y) + ((1-alpha)*ValorfiltradoY);
ValorfiltradoZ = (alpha*accelerometer_z) + ((1-alpha)*ValorfiltradoZ);

moverMotorDobleAcelerometro(ValorfiltradoX,  motorA , motorAa );
moverMotorDobleAcelerometro(ValorfiltradoY,  motorB , motorBb );
moverMotorAcelerometro( ValorfiltradoZ, 0);

//delay (10);         
funciona = param.asStr();
}

   while (funciona != "fin");
    terminal.println("acelerometro");
  }




  else {

    terminal.print("No se encuentra comando: ");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
    terminal.println("Intente nuevamente");
    terminal.println();


  }

  // Ensure everything is sent
  terminal.flush();

}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorBlue ( pinValue , motor1 );

}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorBlue ( pinValue , motor2 );

}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorBlue ( pinValue , motor3 );

}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorInversoBlue ( pinValue , motor4 );

}

BLYNK_WRITE(V6)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorInversoBlue ( pinValue , motor5 );

}

BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorInversoBlue ( pinValue , motor6 );

}

BLYNK_WRITE(V8)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorDobleBlue(  pinValue, motorA, motorAa);

}
BLYNK_WRITE(V9)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorDobleBlue(  pinValue, motorB, motorBb);

}

BLYNK_WRITE(V10)
{
  int pinValue = param.asInt(); // Asignamos el valor del pin virtual a una variable
  moverMotorBlue(  pinValue, motorZ);

}

//BLYNK_WRITE(V11) 
//
//{
//
//acelex= param[0].asFloat();
//aceley= param[1].asFloat();
//acelez= param[2].asFloat();
//
//Serial.println(acelex); 
//Serial.println(aceley); 
//Serial.println(acelez); 
//
//ValorfiltradoX = (alpha*acelex) + ((1-alpha)*ValorfiltradoX);
//ValorfiltradoY = (alpha*aceley) + ((1-alpha)*ValorfiltradoY);
//ValorfiltradoZ = (alpha*acelez) + ((1-alpha)*ValorfiltradoZ);
//
//moverMotorDobleAcelerometro(ValorfiltradoX,  motorA , motorAa );
//moverMotorDobleAcelerometro(ValorfiltradoY,  motorB , motorBb );
//moverMotorAcelerometro( ValorfiltradoZ, 0);
//
//}


void moverMotor( int pote, int motor)
{
  int pulse_wide, pulse_width, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  pulse_wide = map(potVal, 0, 1023, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  Serial.println(potVal);


}

void moverMotorInverso( int pote, int motor)
{
  int pulse_wide, pulse_width1, pulse_width2, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  pulse_wide = map(potVal, 0, 1023, 100, 2300);
  pulse_width1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  pulse_width2 = map (pulse_width1, 150 , 500 , 500, 150);

  pwm.setPWM(motor, 0, pulse_width2);
  Serial.println(potVal);


}

void moverMotorDoble( int pote, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2, potVal;

  // lector de valores del potenciometro

  potVal = analogRead(pote);

  //conversor
  pulse_wide = map(potVal, 0, 1023, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  Serial.println(potVal);


}

void moverMotorAcelerometro( int ejeacelerometro, int motor)
{
  int pulse_wide, pulse_width;

  pulse_wide = map(ejeacelerometro, -4096, 4096, 100, 2300);//acele

  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  Serial.println(ejeacelerometro);
}

void moverMotorDobleAcelerometro( int ejeacelerometro, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2;

  pulse_wide = map(ejeacelerometro, -4096, 4096, 250, 2300);


  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  ancho_pulso2 = ancho_pulso2 + 30; //correccion
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  Serial.println(ancho_pulso1);
  Serial.println(ancho_pulso2);


}
void moverMotorDobleBlue( int ejeacelerometro, int motor1, int motor2)
{
  int pulse_wide, ancho_pulso1, ancho_pulso2;

  pulse_wide = map(ejeacelerometro, 0, 255, 250, 2300);

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

  pulse_wide = map(pot, 0, 255, 100, 2300);
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  Serial.println(pot);

}

void moverMotorInversoBlue( int pot, int motor)
{
  int pulse_wide, pulse_width1, pulse_width2;

  pulse_wide = map(pot, 0, 255, 100, 2300);
  pulse_width1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  pulse_width2 = map (pulse_width1, 150 , 500 , 500, 150);

  pwm.setPWM(motor, 0, pulse_width2);
  Serial.println(pot);

}

////////Funciones////////////


void setup()
{

  //////////// Blynk ////////////
  // Debug console
  DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");
  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch

  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  //////////// Blynk ////////////

  //////////// Servos ////////////
  pwm.begin();
  pwm.setPWMFreq(50);  // Revisar frecuencia 50 o 60 Hz
  //////////// Servos ////////////

  //////////acelerometro/////////
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Empieza la transmicion al acelerometro
  Wire.write(0x6B); // vamos al registro PWR_MGMT_1
  Wire.write(0); // y lo colocamos en 0, esto enciende el mpu6050
  Wire.endTransmission(); // salimos

  //Aca configuramos el rango
  Wire.beginTransmission(MPU_ADDR); //entramos nuevamente
  Wire.write(0x1C); // En este registro definimos el rango
  Wire.write(0b00010000); //aca lo modificamos era 00 01 10 11 para 2;4;8;16
  Wire.endTransmission(true);
  //////////acelerometro/////////


  terminal.clear(); //limpiamos
  // Escribimos en el terminal //
  terminal.println("Iniciando ROBi");
  terminal.println(F("---------"));
  terminal.println("ROBi 3.0 Esta Listo!");
  terminal.println(F(";) ;) ;) ;) ;)"));
  terminal.flush();
}

void loop()
{
  Blynk.run();
}
