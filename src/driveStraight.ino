void goStraightEX()
{
  double orientation = 0; 
  //strght_trig = true;
  
  //Temporary variable for control system(power)
  double power = 350;//300
  double powerLeft = power; //default = 250
  double powerRight = power;
  double diffValue = 0;
  double correction = 0;
  
  //Clear the current interupt variable
  resetEncoder();

  //Distance
   double distance = 285.5; 
  
   //PID
   PID PID_straightEX(&diffValue, &correction, &orientation, kpStraightEX, kiStraightEX, kdStraightEX, DIRECT);
   PID_straightEX.SetMode(AUTOMATIC);
   PID_straightEX.SetSampleTime(sampleTime/2);
   
  while((distance == -1|| (encoderPinLeftTicks + encoderPinRightTicks)/2 < distance))
  {
     if(PID_straightEX.Compute())
     {
       diffValue = rightLeftTicksDiff();

       powerRight = 0.9969 * power - correction; //
       powerLeft = power + correction;
       
       md.setSpeeds(-1*(int)(powerRight), (int)powerLeft);
              
      }
//      Serial.print(powerLeft);Serial.print("\t");
//       Serial.print(powerRight);Serial.print("\t");
//       Serial.println(powerLeft-powerRight);
    }
    brake();
}

void goStraightFP(int grid)
{
  double orientation = 0; 
  
  //Temporary variable for control system(power)
  double power = 380;
  double powerLeft = power;
  double powerRight = power;
  double diffValue = 0;
  double correction = 0;
  
  //Clear the current interupt variable
  resetEncoder();

  //Distance
   double distance = 0;
  switch(grid)
  {
    case 0: distance = 0.5; break;
    case 1: distance = 297.16; break;
    case 2: distance = 590.68; break;
    case 3: distance = 902.6; break;
    case 4: distance = 1230.29; break;
    case 5: distance = 1526.56; break;
    case 6: distance = 1823.86; break;
    case 7: distance = 2142.82; break;
    case 8: distance = 2400.04; break;
    case 9: distance = 2669.76; break;
    case 10: distance = 2965.76; break;
    case 11: distance = 3270.43; break;
    case 12: distance = 3517.85; break;
    case 13: distance = 3830.83; break;
    case 14: distance = 4135.40; break;
    case 15: distance = 4454.41; break;
    case 16: distance = 4803.03; break;
    default: distance = 304.8799 *grid; 
  } 
  
   //PID
   PID PID_straightFP(&diffValue, &correction, &orientation, kpStraightFP, kiStraightFP, kdStraightFP, DIRECT);
   PID_straightFP.SetMode(AUTOMATIC);
   PID_straightFP.SetSampleTime(sampleTime/2);

   //Serial.println(readSensor(Mid_mid));
   
  while(((distance == -1|| (encoderPinLeftTicks + encoderPinRightTicks)/2 < distance)))  
    {
     if(PID_straightFP.Compute())
     {
       diffValue = rightLeftTicksDiff();

       powerRight = 0.9969 * power - correction;
      powerLeft = power + correction;
      
//      Serial.print(powerLeft);Serial.print("\t");
//       Serial.print(powerRight);Serial.print("\t");
//       Serial.println(powerLeft-powerRight);
//      
      }
       md.setSpeeds(-1*(int)(powerRight), (int)powerLeft);
       
           
    }
    
    brakeFP();
}
