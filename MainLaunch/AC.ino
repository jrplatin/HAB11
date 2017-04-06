char checkAC(){   
  // if within correct altitude range and the valve is closed
  // start venting
  if (18288 >= alt && alt >= 12192 && valveClosed) {
    Serial.print("A"); //for testing
    return 'o';
    // takes 9s to open valve
    
  }

  // if at or above goal altitude and valve is open, close valve
  if (18288 <= alt && !valveClosed) {
    // now done with alt control venting
    manueverDone = true;
    Serial.print("B"); // for testing
    cruiseCheckWindow = millis() + 300000; //Set a 5 minute window to try to check for cruiseConditions
    valveClosed = true;
    return 'c';
  }
  
  // if the avg alt difference between readings is < 100
  // begin cruising

  //Check that average upward velocity is less than  a certain amount
  if (velDiff < 1 && manueverDone) {
    isCruising = true;
    // want to cruise for 5 mins
    tCruise = millis() + 300000;
    Serial.print("D"); // for testing
  }
  
  //if we are done cruing
  if (millis() > tCruise && isCruising) {
    // open valve
    isCruising = false;
    Serial.print("E");
    valveClosed = false;
    return 'o';
  }

  // if we fail to cruise, just descent
  if (millis() > cruiseCheckWindow && !isCruising && valveClosed) {
      isCruising = false;
      Serial.print("F");
      valveClosed = false;
      return 'o';
  }

  else return 'n';
}


void runAC(){
   if(!opening && !closing){
    char operation = checkAC(); 
    if(operation == 'o' && !isopen){ 
      opening = true; 
      endop = millis() + 8000;
      analogWrite(SERVOPIN,5);
      Serial.println("Opening Servo");
      Serial.println("End Time:" + String(endop));
    }
    else if(operation == 'c' && isopen){ 
      closing = true; 
      endcl = millis() + 8000;
      analogWrite(SERVOPIN,250);
      Serial.println("Closing Servo");
      Serial.println("End Time:" + String(endcl));
    }
  }
  if(opening){
    if(millis() >= endop){
      Serial.println(String(millis()));
      analogWrite(SERVOPIN,0);
      delay(10);
      opening = false;
      isopen = true;
      Serial.print("Finished Opening");
    }
  }
  else if(closing){
    if(millis() >= endcl){
      Serial.println(String(millis()));
      analogWrite(SERVOPIN,0);
      delay(10);
      closing = false;
      isopen = false;
      Serial.println("Finished Closed");
    }
  }
}

