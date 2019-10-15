void caliRight()
{

  int countc = 0;
  bool tried_left = false;
  bool tried_right = false;

  int cRsamples = 7;
  irSamples(cRsamples);
  float ir_diff = median(irArr5,7) - median(irArr6,7);

  while (abs(ir_diff) > 0.2 && countc < 100 && not(tried_left && tried_right))
  {

    //delay(10);

    if (ir_diff < 0.2)
    {
      //left
      rotateLeft(0);
      tried_left = true;
    }
    else if (ir_diff > 0.2)
    {
      //right
      rotateRight(0);

      tried_right = true;
    }
    countc++;
    irSamples(cRsamples);
    ir_diff = median(irArr5,7) - median(irArr6,7);
  }
}

void caliDistance()
{
  //irSamples();

  int cDsamples = 7;
  irSamples(cDsamples);
  
  int dist = 4;

  while (median(irArr2,cDsamples) > dist && median(irArr3,cDsamples) > dist && median(irArr4,cDsamples) > dist)
  {
    goStraightFP(0);
    irSamples(cDsamples);
  }

  while (median(irArr2,cDsamples) < dist || median(irArr3,cDsamples) < dist || median(irArr4,cDsamples) < dist)
  {
    goBackFP(0);
    irSamples(cDsamples);
  }
}

void caliAngle()
{
  caliFront();
  caliRight();
  rotateRight(1);
  caliFront();
  rotateLeft(1);
  caliFront();
  caliRight();
 
  Serial.println("cali:done");
}

void caliFront()
{

  caliDistance();

  //make robot parallel

//  int offsetIR2 = 0;
//  int offsetIR4 = 0;

//KIV
//  switch (estShort(readIR2()))
//  {
//
//  case 2:
//  {
//    offsetIR2 = 10;
//    break;
//  }
//
//  case 3:
//  {
//    offsetIR2 = 20;
//    break;
//  }
//
//  default:
//  {
//    offsetIR2 = 0;
//    break;
//  }
//  }
//
//  switch (estShort(readIR4()))
//  {
//
//  case 2:
//    offsetIR4 = 10;
//    break;
//
//  case 3:
//    offsetIR4 = 20;
//    break;
//
//  default:
//    offsetIR4 = 0;
//    break;
//  }
//  int ir_diff = 0;
//  ir_diff = ((readIR2() - offsetIR2) - (readIR4() - offsetIR4));

  int cFsamples = 7;
  irSamples(cFsamples);
  float ir_diff = median(irArr2,cFsamples) - median(irArr4,cFsamples);



  int countc = 0;
  bool tried_left = false;
  bool tried_right = false;

  //using Fl and FR from front sensors
  while ((abs(ir_diff) > 0.3) && countc < 100 && not(tried_left && tried_right))
  {

    if (ir_diff < 0)
    {
      //left
      rotateLeft(0);
      tried_left = true;
      //  Serial.println("rotating left");
    }
    else if (ir_diff > 0)
    {
      //right
      rotateRight(0);
      tried_right = true;
      //  Serial.println("rotating right");
    }
    countc++;
    irSamples(cFsamples);
    ir_diff = median(irArr2,cFsamples) - median(irArr4,cFsamples);
  }
}
