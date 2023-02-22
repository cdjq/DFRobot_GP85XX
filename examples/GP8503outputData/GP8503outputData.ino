/*!
  * @file GP8503outputData.ino
  * @brief 
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */

#include <DFRobot_GP85XX.h>

DFRobot_GP8503 GP8503;

void setup() {
  Serial.begin(115200);
  
  GP8503.begin();
  Serial.println("init succeed");

  GP8503.setDACOutRange(GP8503.eOutputRange2_5V);
  GP8503.setDACOutVoltage(2000,2);
  delay(1000);
  GP8503.store();
}

void loop() {
  // put your main code here, to run repeatedly:

}
