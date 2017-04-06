void writeSD(String dataString){
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
}

String mkdata(){
  String data = 
  //Times
  String(gpstime) + "," + 
  String(gpsdate) + "," + 
  String(millis()) + "," + 
  //IMU Data
  String(yaw,4) + "," + 
  String(pitch,4) + "," +
  String(roll,4) + "," +
  //GPS
  String(latit,6) + "," + 
  String(longit,6) + "," + 
  String(alt,6) + "," + 
  String(course,2) + "," + 
  String(speed,2) + "," + 
  String(numsats) + "," + 
  String(velDiff,3) + "," + 
  //Geiger
  String(cps_b) + "," + 
  String(cpm_b) + "," + 
  String(usv_b,2) + "," + 
  String(cps_o) + "," + 
  String(cpm_o) + "," + 
  String(usv_o,2) + "," + 
  //Temperature
  String(temp,4) + "," +
  String(humidity, 4) + "," +
  //Windspeed
  String(windspeed, 4);
  
  return data;
}

