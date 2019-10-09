void caliRight() {
  //Serial.println("CaliRight();");
  int countc = 0;
  bool tried_left = false;
  bool tried_right = false;
  float ir_diff = readIR5() - readIR6();

    while (abs(ir_diff) > 0.2 && countc < 100 && not (tried_left && tried_right)) {

      //delay(10);

      if (ir_diff  < 0) {
        //left
        rotateLeft(0);
        tried_left = true;
      }
      else if (ir_diff > 0) {
        //right
        rotateRight(0);
 
        tried_right = true;
      }
      countc++;
      ir_diff = readIR5() - readIR6();
    }
  
  
}

void caliDistance() {
  //Serial.println("CaliDistance();");
//irSamples();
int dist = 5;

while(readIR2() >dist && readIR3() >dist && readIR4() >dist)goStraightFP(0);
while(readIR2() <dist || readIR3() <dist || readIR4() <dist)goBackFP(0);

//while((median(irArr2,50) >4.8) && (median(irArr3,50) >4.8) && (median(irArr4,50) >4.8))goStraightFP(0);
//while((median(irArr2,50) <4.8) || (median(irArr3,50) <4.8) || (median(irArr4,50) <4.8))goBackFP(0);

}

void caliAngle() {
  caliRight();
  caliFront();
  //right
  rotateRight(1);
  caliFront();
  //left
  rotateLeft(1);
  caliFront();
  caliRight();
  delay(10);
  caliRight();
  delay(10);
  caliRight();
  delay(10);
  caliRight();
  delay(10);
  caliRight();
  Serial.println("obs:done");
}


void caliFront () {

  caliDistance();


  //make robot parallel

  

 int offsetIR2 = 0;
 int offsetIR4 = 0;

 switch (estShort(readIR2())){

  case 2: {offsetIR2 = 10;break;}

  case 3: {offsetIR2 = 20;break;}
 
   default: {offsetIR2 = 0;break;}
 }

  switch (estShort(readIR4())){

  case 2: offsetIR4 = 10;break;

  case 3: offsetIR4 = 20;break;
 
   default: offsetIR4 = 0;break;
  }  
  
  int ir_diff = 0;
  ir_diff = ((readIR2()-offsetIR2) - (readIR4()-offsetIR4));
  int countc = 0;
  bool tried_left = false;
  bool tried_right = false;


  //using Fl and FR from front sensors
  while ((abs(ir_diff) > 0.3) && countc < 100  && not (tried_left && tried_right)) {
   // delay(10);
    
    if (ir_diff  < 0) {
      //left
      rotateLeft(0);
      tried_left = true;
     //  Serial.println("rotating left");
    }
    else if (ir_diff > 0 ) {
      //right
      rotateRight(0);
      tried_right = true;
     //  Serial.println("rotating right");
    }
    countc++;
    ir_diff = ((readIR2()-offsetIR2) - (readIR4()-offsetIR4));
  }


  

}
