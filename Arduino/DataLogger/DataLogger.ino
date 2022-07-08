//////////Acelerometro/////////
#include <SPI.h>
#include <Wire.h>
const int MPU_ADDR = 0x68; // Dirección I2C del MPU-6050. Si AD0 esta en HIGH, la dirección I2C sera 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // 
int16_t accelerometer_x2, accelerometer_y2, accelerometer_z2; //
int16_t accelerometer_x3, accelerometer_y3, accelerometer_z3; // 
int16_t gyro_x, gyro_y, gyro_z; // 
int16_t gyro_x2, gyro_y2, gyro_z2; // 
int16_t gyro_x3, gyro_y3, gyro_z3; // 

char tmp_str[7]; // Variable temporal utilizada en la función de conversión 
char* convert_int16_to_str(int16_t i) { // Convierte int16 a string. 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
//////////Acelerometro/////////
//MPU6050 1
int ValorfiltradoAx1 = 0;
int ValorfiltradoAy1 = 0;
int ValorfiltradoAz1 = 0;
int ValorfiltradoGx1 = 0;
int ValorfiltradoGy1 = 0;
int ValorfiltradoGz1 = 0;
//MPU6050 2
int ValorfiltradoAx2 = 0;
int ValorfiltradoAy2 = 0;
int ValorfiltradoAz2 = 0;
int ValorfiltradoGx2 = 0;
int ValorfiltradoGy2 = 0;
int ValorfiltradoGz2 = 0;
//MPU6050 3
int ValorfiltradoAx3 = 0;
int ValorfiltradoAy3 = 0;
int ValorfiltradoAz3 = 0;
int ValorfiltradoGx3 = 0;
int ValorfiltradoGy3 = 0;
int ValorfiltradoGz3 = 0;


/////////Variables///////////
//#define alpha 0.05  //Alpha
#define alpha 0.2  //Alpha
int Valorfiltrado1 = 0;
int Valorfiltrado2 = 0;
int Valorfiltrado3 = 0;
int Valorfiltrado4 = 0;
int Valorfiltrado5 = 0;
int Valorfiltrado6 = 0;
int entrada1 = 0;
int entrada2 = 0;
int entrada3 = 0;
int entrada4 = 0;
int entrada5 = 0;
int entrada6 = 0;
int controlAc1 = 34;
int controlAc2 = 36;
int controlAc3 = 38;


/////////Variables///////////

void setup() {

  Serial.begin(115200);
  delay(10);

  pinMode(controlAc1, OUTPUT);
  pinMode(controlAc2, OUTPUT);
  pinMode(controlAc3, OUTPUT);
  digitalWrite(controlAc1, LOW);
  digitalWrite(controlAc2, LOW);
  digitalWrite(controlAc3, LOW);

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
  delay(10);
}

void loop() {

  entrada1 = analogRead(0);
  entrada2 = analogRead(1);
  entrada3 = analogRead(2);
  entrada4 = analogRead(3);
  entrada5 = analogRead(4);
  entrada6 = analogRead(5);

  Valorfiltrado1 = (alpha * entrada1) + ((1 - alpha) * Valorfiltrado1);
  Valorfiltrado2 = (alpha * entrada2) + ((1 - alpha) * Valorfiltrado2);
  Valorfiltrado3 = (alpha * entrada3) + ((1 - alpha) * Valorfiltrado3);
  Valorfiltrado4 = (alpha * entrada4) + ((1 - alpha) * Valorfiltrado4);
  Valorfiltrado5 = (alpha * entrada5) + ((1 - alpha) * Valorfiltrado5);
  Valorfiltrado6 = (alpha * entrada6) + ((1 - alpha) * Valorfiltrado6);

  ////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(controlAc1, LOW); digitalWrite(controlAc2, HIGH); digitalWrite(controlAc3, HIGH);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  ValorfiltradoAx1 = (alpha * accelerometer_x) + ((1 - alpha) * ValorfiltradoAx1);
  ValorfiltradoAy1 = (alpha * accelerometer_y) + ((1 - alpha) * ValorfiltradoAy1);
  ValorfiltradoAz1 = (alpha * accelerometer_z) + ((1 - alpha) * ValorfiltradoAz1);
  ValorfiltradoGx1 = (alpha * gyro_x) + ((1 - alpha) * ValorfiltradoGx1);
  ValorfiltradoGy1 = (alpha * gyro_y) + ((1 - alpha) * ValorfiltradoGy1);
  ValorfiltradoGz1 = (alpha * gyro_z) + ((1 - alpha) * ValorfiltradoGz1);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(controlAc1, HIGH); digitalWrite(controlAc2, LOW); digitalWrite(controlAc3, HIGH);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  accelerometer_x2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  gyro_x2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z2 = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  ValorfiltradoAx2 = (alpha * accelerometer_x2) + ((1 - alpha) * ValorfiltradoAx2);
  ValorfiltradoAy2 = (alpha * accelerometer_y2) + ((1 - alpha) * ValorfiltradoAy2);
  ValorfiltradoAz2 = (alpha * accelerometer_z2) + ((1 - alpha) * ValorfiltradoAz2);
  ValorfiltradoGx2 = (alpha * gyro_x2) + ((1 - alpha) * ValorfiltradoGx2);
  ValorfiltradoGy2 = (alpha * gyro_y2) + ((1 - alpha) * ValorfiltradoGy2);
  ValorfiltradoGz2 = (alpha * gyro_z2) + ((1 - alpha) * ValorfiltradoGz2);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(controlAc1, HIGH); digitalWrite(controlAc2, HIGH); digitalWrite(controlAc3, LOW);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  accelerometer_x3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  gyro_x3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z3 = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  ValorfiltradoAx3 = (alpha * accelerometer_x3) + ((1 - alpha) * ValorfiltradoAx3);
  ValorfiltradoAy3 = (alpha * accelerometer_y3) + ((1 - alpha) * ValorfiltradoAy3);
  ValorfiltradoAz3 = (alpha * accelerometer_z3) + ((1 - alpha) * ValorfiltradoAz3);
  ValorfiltradoGx3 = (alpha * gyro_x3) + ((1 - alpha) * ValorfiltradoGx3);
  ValorfiltradoGy3 = (alpha * gyro_y3) + ((1 - alpha) * ValorfiltradoGy3);
  ValorfiltradoGz3 = (alpha * gyro_z3) + ((1 - alpha) * ValorfiltradoGz3);
  ////////////////////////////////////////////////////////////////////////////////////////////////

  
//  Serial.print(map(Valorfiltrado1, 0, 1023, 0, 180)); //Pote 1 delt medial
//  Serial.print(",");
//  Serial.print(map(Valorfiltrado2, 0, 1023, 180, 360)); //Pote 2 delt anterior
//  Serial.print(",");
  Serial.print(map(Valorfiltrado3, 430, 1000, 135, 0)); //Pote 3 biceps
  Serial.print(","); 
//  Serial.print(map(Valorfiltrado4, 0, 1023, 540, 720)); //Pote 4 muñeca
//  Serial.print(",");
//  Serial.print(map(Valorfiltrado5, 0, 1023, 720, 900)); //Pote 5 metacarpofalangica
//  Serial.print(",");
//  Serial.print(map(Valorfiltrado6, 0, 1023, 900, 1080)); //Pote 6 falange prox-med
//  Serial.print(",");
  Serial.print(map(ValorfiltradoAx1, -4800, 4800, 1080, 1260)); // Acelerometro 1 eje x
  Serial.print(",");
  Serial.print(map(ValorfiltradoAy1, -4800, 4800, 1260, 1440)); // Acelerometro 1 eje y
  Serial.print(",");
  Serial.print(map(ValorfiltradoAz1, -4800, 4800, 1440, 1620)); // Acelerometro 1 eje z
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAx2, -4800, 4800, 1620, 1800)); // Acelerometro 2 eje x
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAy2, -4800, 4800, 1800, 1980)); // Acelerometro 2 eje y
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAz2, -4800, 4800, 1980, 2160)); // Acelerometro 2 eje z
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAx3, -4800, 4800, 2160, 2340)); // Acelerometro 2 eje x
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAy3, -4800, 4800, 2340, 2520)); // Acelerometro 2 eje y
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoAz3, -4800, 4800, 2520, 2700)); // Acelerometro 2 eje z
  Serial.print(",");
  Serial.print(map(ValorfiltradoGy1, -30000, 30000, 2880, 3060)); // Giroscopio 1 eje y
  Serial.print(",");
  Serial.println(map(ValorfiltradoGz1, -30000, 30000, 3060, 3240)); // Giroscopio 1 eje z
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoGy2, -30000, 30000, 3420, 3600)); // Giroscopio 2 eje y
//  Serial.print(",");
//  Serial.print(map(ValorfiltradoGz2, -30000, 30000, 3600, 3780)); // Giroscopio 2 eje z
//  Serial.print(",");
//  Serial.println(map(ValorfiltradoGy3, -30000, 30000, 3960, 4140)); // Giroscopio 2 eje y
////  Serial.print(",");
////  Serial.println(map(ValorfiltradoGz3, 30000, 30000, 4140, 4320)); // Giroscopio 2 eje z
  


}
