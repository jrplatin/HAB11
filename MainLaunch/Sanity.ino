void sanity(){
  //========================================
  //Sanity Declarations ====================
  static boolean sd = false;  
  static boolean imu = false;
  static boolean temphum = false;
  static boolean gps_attached = false;
  static boolean geig_b_attached = false;
  static boolean geig_o_attached = false;
  static boolean ranservo = false;

  static boolean good_data = false;
  
  //==========================================
  //Sanity Checks ============================
  
  if(!sd){ if (SD.begin(chipSelect)) { sd = true; } }
  if(!imu){ if(initSensors()){ imu = true; } }
  if(!temphum){ if (htu.begin()) { temphum = true; } }
  //Servo Test
  if(!ranservo){
    analogWrite(SERVOPIN,5); delay(500);
    analogWrite(SERVOPIN,0); delay(500);
    analogWrite(SERVOPIN,250); delay(500);
    analogWrite(SERVOPIN,0); delay(10);
    ranservo = true;
  }
  //GPS, Geiger
  if(Serial1.available()){ gps_attached = true; }
  if(Serial2.available()){ geig_b_attached = true; }
  if(Serial3.available()){ geig_o_attached = true; }
  
  //========================================
  //Data Verification ======================
  if(gps_attached){ readGPS(); }
  if(imu){ readIMU(); }
  if(geig_b_attached){ readGeigerB(); }
  if(geig_o_attached){ readGeigerO(); }
  anemometer();
  
  //==========================================
  //Display Information ======================
  display.clearDisplay();
  display.setCursor(0,0);
  if(!sd) { display.print("SD- "); } else{ display.print("SD+ "); }
  if(!imu){ display.print("IMU- "); } else{ display.print("IMU+ "); }
  if(!temphum){ display.print("HTU- "); } else{ display.print("HTU+ "); }

  if(gps_attached){
    display.println("NS:" + String(numsats));
    display.println("Wind: " + String(windspeed,3));
    display.println("Lat: " + String(latit,6));
    display.println("Long: " + String(longit,6));
  } else { display.println("GPS-"); }

  if(imu){
    display.print(String(yaw,2) + ",");
    display.print(String(pitch,2) + ",");
    display.println(String(roll,2));
  }
  
  if(geig_b_attached){
    display.println("Blue:"+String(cps_b)+","+String(cpm_b)+","+String(usv_b,2));
  }
  if(geig_o_attached){
    display.println("Oran:"+String(cps_o)+","+String(cpm_o)+","+String(usv_o,2));
  }
  if(!geig_b_attached && !geig_o_attached){ display.println("Geiger-"); }

  //==========================================
  //Ending Sanity ============================
  if(sd && imu && gps_attached && digitalRead(BUTTON) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Button Pressed\nEnding Sanity\n\nHave a Great\nFlight!");
    display.display();
    sane = true;
    delay(3000);
    display.clearDisplay();
  }
  display.display();
  //==========================================
}

