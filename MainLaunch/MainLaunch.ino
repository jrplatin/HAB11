/*
 * Main Flight Code for the Penn Aerospace Club's
 * High Altitude Balloon Project
 * 
 * Integrations:
 * SD Card, 9DOF IMU, Temperature, Humidity,
 * GPS, Geiger Counter Logging, Altitude Control,
 * Comprehensive Sanity System, Anemometer
 * 
 */
//======================================
// Libraries ===========================
#include <Wire.h>               //Temp/Humidity/IMU/OLED
#include <SPI.h>                //SD
#include <SD.h>                 //SD
#include <TinyGPS++.h>          //GPS
#include <Adafruit_SSD1306.h>   //OLED
#include "Adafruit_HTU21DF.h"   //Temp/Humidity
#include <Adafruit_Sensor.h>    //IMU
#include <Adafruit_LSM303_U.h>  //IMU
#include <Adafruit_L3GD20_U.h>  //IMU
#include <Adafruit_9DOF.h>      //IMU


//=====================================
//IMU =================================
Adafruit_9DOF                   dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified   accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified     mag   = Adafruit_LSM303_Mag_Unified(30302);
float yaw;
float pitch;
float roll;

//======================================
// Altitude Control ====================
long int cruiseCheckWindow = 10800000; //3 hr time frame
bool valveClosed = false;
bool isCruising = false;
bool manueverDone = false;
long int tCruise = 10800000;
//loop a/c
boolean isopen = false;
boolean opening = false;
boolean closing = false;
long int endop;
long int endcl;
#define SERVOPIN 6

//=======================================
// GPS Variables ========================
TinyGPSPlus gps;
double latit;   //degrees
double longit;  //degrees
double alt;     //meters
double alto;
double velDiff;
double vel[] = {0,0,0,0,0}; //meters 
long gpstime;   //HHMMSSCC
long gpsdate;   //DDMMYY
int numsats;
double course;  //degrees 
double speed;   //mph

//=========================================
// Geiger Variables =======================
int cps_o; int cps_b;
int cpm_o; int cpm_b;
float usv_o; float usv_b;

//OLED =====================================
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//SD Card ==================================
#define chipSelect 53

//Temp/Humidity ============================
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
float temp;                 //farenehit
float humidity;             //percentage

//Anemometer ===============================
#define ANEM A0
float windspeed;            //mph

//Sanity ===================================
boolean sane = false;
#define BUTTON 9
//==========================================

void setup() {
  //Serial
  Serial.begin(115200); //Computer
  Serial1.begin(9600); //GPS
  Serial2.begin(9600); //Geiger Blue
  Serial3.begin(9600); //Geiger Orange

  pinMode(SERVOPIN,OUTPUT);
  analogWrite(SERVOPIN,0);

  pinMode(ANEM,INPUT);

  //Sanity
  pinMode(BUTTON,INPUT);

  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

//=======================================
void loop() {
  while(!sane){ sanity(); }
  
  unsigned long nextloop = millis() + 1000;

  
  readIMU();
  readGPS();
  readGeigerB();
  readGeigerO();
  runAC();
  anemometer();

  //Temp/Hum
  temp = htu.readTemperature()*1.8 + 32;
  humidity = htu.readHumidity();

  //Data Logging
  String data = mkdata();
  writeSD(data);
  Serial.println(data);
  Serial.flush();

  while(millis() < nextloop);
}

void anemometer(){
  //Takes an analog input from 0.4V and 2V and maps it to 0m/s to 32m/s then to mph
  windspeed = ((analogRead(ANEM) - 82)/328.0 * 32.4)*2.23694;
}

