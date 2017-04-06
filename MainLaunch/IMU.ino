boolean initSensors() {
  if(!accel.begin()){ return false; }
  if(!mag.begin()){ return false; } 
  return true;
}

void readIMU(){
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;

  /* Read the accelerometer and magnetometer */
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  /* Use the new fusionGetOrientation function to merge accel/mag data */  
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation)){
    yaw = orientation.heading;
    pitch = orientation.pitch;
    roll = orientation.roll;
  }
  delay(10);
}

