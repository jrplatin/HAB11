void readGeigerB() {
  String datastring = "";

  if(Serial2.available()>0){
    while(Serial2.available()>0){ datastring += (String)(char)Serial2.read(); }
    cps_b = datastring.substring(datastring.indexOf(" ")+1, datastring.indexOf(',',datastring.indexOf(" "))).toInt();
    cpm_b = datastring.substring(datastring.indexOf(" ",datastring.indexOf('M'))+1, datastring.indexOf(',',datastring.indexOf("M,")+2)).toInt();
    usv_b = datastring.substring(datastring.indexOf(" ",datastring.indexOf('r'))+1, datastring.indexOf(',',datastring.indexOf("r,")+2)).toFloat();
  }
  delay(10);
}

void readGeigerO() {
  String datastring = "";
  if(Serial3.available()>0){
    while(Serial3.available()>0){ datastring += (String)(char)Serial3.read(); }
    cps_o = datastring.substring(datastring.indexOf(" ")+1, datastring.indexOf(',',datastring.indexOf(" "))).toInt();
    cpm_o = datastring.substring(datastring.indexOf(" ",datastring.indexOf('M'))+1, datastring.indexOf(',',datastring.indexOf("M,")+2)).toInt();
    usv_o = datastring.substring(datastring.indexOf(" ",datastring.indexOf('r'))+1, datastring.indexOf(',',datastring.indexOf("r,")+2)).toFloat();
  }
  delay(10);
}

