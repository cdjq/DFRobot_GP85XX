/*!
  * @file GP8101outputData.ino
  * @brief 设置输出电压值和范围，将PWM信号转换为1路0--5V或0-10V的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */

#include <DFRobot_GP85XX.h>

DFRobot_GP8101 GP8101;

//输出IO口
int pin = 9;

void setup() {
  Serial.begin(115200);
  
  /**
   * @param pin PWM出输出接口
   * @brief 初始化函数
   */
  GP8101.begin(pin);
  Serial.println("init succeed");
  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange5V(0-5V)
   * @n     eOutputRange10V(0-10V)
   */	
  GP8101.setDACOutRange(GP8101.eOutputRange5V);
  /**
   * @brief 设置输出DAC值
   * @param data 需要输出的电压值
   */
  GP8101.setDACOutVoltage(4000);
  /**
   * @brief 设置PWM占空比
   * @param data 需要设置的占空比(0-255),ESP32和ESP8266为：(0-8191)
   */
	//GP8101.sendData(uint16_t data);
}

void loop() {

}
