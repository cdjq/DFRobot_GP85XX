/*!
  * @file GP8501outputData.ino
  * @brief 设置输出通道、电压值和输出范围，将PWM信号转换为2路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */

#include <DFRobot_GP85XX.h>

DFRobot_GP8501 GP8501;

//双通道输出IO口
int pin0 = 9;
int pin1 = 10;
//单通道输出IO口
// int pin = 9;

void setup() {
  Serial.begin(115200);
  /**
   * @brief 初始化函数
   * @param pin PWM输出引脚	 
   */
  //GP8501.begin(pin);
  /**
   * @brief 初始化函数
   * @param pin0 PWM输出引脚0
   * @param pin1 PWM输出引脚1
   */
  GP8501.begin(pin0,pin1);
  Serial.println("init succeed");
  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-2.5V)
   * @n     eOutputRangeVCC(0-VCC) 
   * @param vcc VCC输入的电源电压,VCC范围(2.7V-5.5V)
   */	
  GP8501.setDACOutRange(GP8501.eOutputRange2_5V);
  /**
   * @brief 设置不同通道输出DAC值
   * @param data 需要输出的电压值
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   */
  GP8501.setDACOutVoltage(2000,2);
  //通道0
  // GP8501.setDACOutVoltage(2000, 0);
  //通道1
  // GP8501.setDACOutVoltage(2000, 1);
  /**
   * @brief 设置PWM占空比
   * @param data 需要设置的占空比
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   */
	//GP8501.sendData(uint16_t data, uint8_t channel);
}

void loop() {

}
