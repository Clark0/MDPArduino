float ir_valR3;
float ir_valR4;
float ir_valR5;
float ir_valR6; 

//Raw values to OFFSET
// LEFT LONG 
float readIR1() {
  return 4 + 60.374 * pow(map(analogRead(irR1), 0, 1023, 0, 5000) / 1000.0, -1.16) -16;
}// 5,10,18,27,37,53,70

// FRONT LEFT
float readIR2() {
  return 27.728 * pow(map(analogRead(irR2), 0, 1023, 0, 5000) / 1000.0, -1.2045) -4;
}//5,15,25,35

// FRONT MIDDLE 
float readIR3() {
  return 27.728 * pow(map(analogRead(irR3), 0, 1023, 0, 5000) / 1000.0, -1.2045) -5;
}//5,15,24,31

// FRONT RIGHT
float readIR4() {
  return 27.728 * pow(map(analogRead(irR4), 0, 1023, 0, 5000) / 1000.0, -1.2045) -4.3;
}//5,15,25,29

// RIGHT FRONT SHORT
float readIR5() {
  return 27.728 * pow(map(analogRead(irR5), 0, 1023, 0, 5000) / 1000.0, -1.2045) -4.7;
}//5,12,23,30

// RIGHT MIDDLE SHORT
float readIR6() {
  return 27.728 * pow(map(analogRead(irR6), 0, 1023, 0, 5000) / 1000.0, -1.2045) -3;
}//5,10,20,30

void checkRawValues (){
  
//  Serial.println("obs:"+String(readIR1())+"|"
//                      +String(readIR2())+"|"
//                      +String(readIR3())+"|"
//                      +String(readIR4())+"|"
//                      +String(readIR5())+"|"
//                      +String(readIR6())
//                 );
        Serial.println("obs:"+String(median(irArr1,50))+"|"
                      +String(median(irArr2,50))+"|"
                      +String(median(irArr3,50))+"|"
                      +String(median(irArr4,50))+"|"
                      +String(median(irArr5,50))+"|"
                      +String(median(irArr6,50)));
  }




//collects samples for ir Array
float irSamples(int maxnum) {
  for (int i = 0; i < maxnum; i++) {
    irArr1[i] = readIR1();
    irArr2[i] = readIR2();
    irArr3[i] = readIR3();
    irArr4[i] = readIR4();
    irArr5[i] = readIR5();
    irArr6[i] = readIR6();
    delay(5);
  }

  
}





float median(float nums[], int n) {
  int k = n % 2 == 0 ? n / 2 : n / 2 + 1;
  return qselect(nums, 0, n - 1, k - 1);
}

float qselect(float A[], int start, int end, int k) {
  if (start == end) {
    return A[start];
  }

  int left = start, right = end;
  int index = (left + right) / 2;
  float pivot = A[index];

  while (left <= right) {
    while (left <= right && A[left] > pivot) {
      left++;
    }

    while (left <= right && A[right] < pivot) {
      right--;
    }

    if (left <= right) {
      float tmp = A[left];
      A[left] = A[right];
      A[right] = tmp;

      left++;
      right--;
    }
  }

  if (k >= start && k <= right) {
    return qselect(A, start, right, k);
  }
  if (k >= left && k <= end) {
    return qselect(A, left, end, k);
  }
  return A[right + 1];
}


void sendIRtoPC() {

  irSamples(50);
//to check raw values
// checkRawValues();

  // filtered reading to return in grids

  //automated front calibration
//  if((estShort(median(irArr2, 50))<4 && estShortFR(median(irArr4, 50))<4) 
//    ||(estShort(median(irArr2, 50))<4 && estShortFM(median(irArr3, 50))<4)
//    ||(estShortFM(median(irArr3, 50))<4 && estShortFR(median(irArr4, 50)))<4) {
//       caliFront();
//    }
 
  Serial.println("obs:" + String(estLong(median(irArr1, 50))) + "|"
                 + String(estShort(median(irArr2, 50))) + "|"
                 + String(estShortFM(median(irArr3, 50))) + "|"
                 + String(estShortFR(median(irArr4, 50))) + "|"
                 + String(estShort(median(irArr5, 50))) + "|"
                 + String(estShort(median(irArr6, 50)))
                );
}



int estShort(float reading) {
  if (reading < 9.5   && reading > 1) {
    return 1; 
  }
  else if (reading < 19) {
    return 2; 
  }
  else if (reading <= 30) {
    return 3;  
  }
  else {
    return 0;
  }
}

int estShortFM(float reading) {
  if (reading < 9.5   && reading > 1) {
    return 1; 
  }
  else if (reading < 19 ) {
    return 2; 
  }
  else if (reading <= 36) {
    return 3;  
  }
  else {
    return 0;
  }
}

int estShortFR(float reading) {
  if (reading < 9.5   && reading > 3) {
    return 1; 
  }
  else if (reading < 19) {
    return 2; 
  }
  else if (reading <= 26) {
    return 3;  
  }
  else {
    return 0;
  }
}


// 5,10,18,27,37,53,70
int estLong(float reading) {
  if (reading <7.2 && reading >=4) {
    return 1; 
  }
  else if (reading < 16 && reading >=7.2) {
    return 2; 
  }
  else if (reading < 24.5) {
    return 3; 
  }
  else if (reading < 30) {
    return 4; 
  }
   else if (reading < 42) {
    return 5; 
  }
  else {
    return 0;
  }
}
