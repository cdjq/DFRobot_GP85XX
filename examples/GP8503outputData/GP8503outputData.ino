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
  
  //初始化
  GP8503.begin();
  Serial.println("init succeed");

  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-2.5V)
   * @n     eOutputRangeVCC(0-VCC)
   * @param vcc VCC输入的电源电压,VCC范围(2.7V-5.5V)
   */	
  GP8503.setDACOutRange(GP8503.eOutputRange2_5V);
  /**
   * @brief 设置不同通道输出DAC值
   * @param data 需要输出的电压值
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   */   
  GP8503.setDACOutVoltage(2000,2);
  /**
   * @brief 设置IIC输入值
   * @param data 需要设置的输入值(0-fff)
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   */
  //GP8503.sendData(fff,2);
  delay(1000);
  //将设置的电压保存在芯片内部
  GP8503.store();
}

void loop() {

}
