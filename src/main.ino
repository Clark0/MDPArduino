#include <PID_v1.h>
#include <RunningMedian.h>

#include "DualVNH5019MotorShield.h"
#include "EnableInterrupt.h"
#include "SharpIR.h"


// version 12 HWLAB2 new

#define M1E1Right 3
#define M2E2Left 13

#define irR1 A0 
#define irR2 A1 
#define irR3 A2 
#define irR4 A3 
#define irR5 A4 
#define irR6 A5 



/// PID constant variables

double sampleTime = 100;

double kpStraightEX = 1.88; //1.68; //1.3 
double kiStraightEX = 0.2; //0.2; //1,2 for straight  
double kdStraightEX = 0.7; //0.6; //0.5

double kpStraightFP = 5; //2.8
double kiStraightFP = 0.0; //0.02
double kdStraightFP = 0.0;  //0.0

double kpRight = 0.8; //0.8
double kiRight = 0.5; //0.5
double kdRight = 0.2;  //0.2

double kpLeft = 0.7;
double kiLeft = 0.5;
double kdLeft = 0.2;

const int encoderPinLeft = 3;
const int encoderPinRight = 11;

//Interrupt
volatile long encoderPinLeftTicks = 0;
volatile long encoderPinRightTicks = 0;

DualVNH5019MotorShield md;

// Initialise  sensors
SharpIR SharpIRR1(irR1, 20150);
SharpIR SharpIRR2(irR2, 1080);
SharpIR SharpIRR3(irR3, 1080);
SharpIR SharpIRR4(irR4, 1080);
SharpIR SharpIRR5(irR5, 1080);
SharpIR SharpIRR6(irR6, 1080);

float distanceCMR1;
float distanceCMR2;
float distanceCMR3;
float distanceCMR4;
float distanceCMR5;
float distanceCMR6;

// read 50 times and store into int array then it returns the median
int irArr1[50];
int irArr2[50];
int irArr3[50];
int irArr4[50];
int irArr5[50];
int irArr6[50];

// get the median and stores in the array 3 times
int irArr1Median[3];
int irArr2Median[3];
int irArr3Median[3];
int irArr4Median[3];
int irArr5Median[3];
int irArr6Median[3];

// For receiving commands from Rpi
int command;
int prev_command = 0; // not in use

void setup() {
  // put your setup code here, to run once:

  
  //Debug
 // analogReference(EXTERNAL);
  Serial.begin(115200);
  //Pin Initialization
  pinMode(encoderPinLeft, INPUT);
  pinMode(encoderPinRight, INPUT);
  digitalWrite(encoderPinLeft, LOW);
  digitalWrite(encoderPinRight, LOW);
  
  md.init();
  pinMode(irR1, INPUT);
  pinMode(irR2, INPUT);
  pinMode(irR3, INPUT);
  pinMode(irR4, INPUT);
  pinMode(irR5, INPUT);
  pinMode(irR6, INPUT);

//  for(int i = 0;i<5 ; i++){
//  goStraightEX();
//   resetEncoder();
//  delay(100);
//  }
//caliAngle();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (receiveCommand())
  {
    executeCommand();
  }
  delay(1);
}
