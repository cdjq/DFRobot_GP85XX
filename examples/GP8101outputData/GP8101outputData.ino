/*!
  * @file GP8101outputData.ino
  * @brief 
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */

#include <DFRobot_GP85XX.h>

DFRobot_GP8101 GP8101;

void setup() {
  Serial.begin(115200);
  
  GP8101.begin();
  Serial.println("init succeed");
  GP8101.setDACOutRange(GP8101.eOutputRange5V);
  GP8101.setDACOutVoltage(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
