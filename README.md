# DFRobot_GP85XX

* [中文版](./README_CN.md)

这是四个DAC模块。用户可以通过I2C和PWM占空比两种输入方式控制此模块输出电压，它具有以下特点：
1. 能够控制输出0-2.5V或0-VCC电压，0-5V或0-10V电压。
2. 采用I2C和PWM占空比两种输入方式控制输出电压大小，I2C默认地址为0x58。 
3. (GP8503,GP8512)模块掉电后，输出电压配置将丢失，如果想下次上电采用此次配置，需保存配置。

## Product Link([www.dfrobot.com](www.dfrobot.com))

    SKU:

## Table of Contents

  - [Summary](#summary)
  - [Installation](#installation)
  - [Methods](#methods)
  - [Compatibility](#compatibility)
  - [History](#history)
  - [Credits](#credits)

## Summary

提供一个Arduino库给四个DAC模块(GP8503,GP8512,GP8501,GP8101)，设置和保存模块输出的电压配置，此库具有以下功能：
1. (GP8503,GP8512,GP8501)设置0-2.5V的电压或0-VCC电压,(GP8101)设置0-5V的电压或0-10V电压
2. (GP8503,GP8512)通过IIC设置DAC范围输出对应的电压,DAC分辨率15bit(0 ~ 0x7FFF)，12bit(0 ~ 0xFFF)；
3. (GP8503,GP8512)保存电压配置，掉电后，该配置不丢失。
4. (GP8501,GP8101)将0%-100%占空比的PWM信号输入，线性转换成(GP8501)0-2.5V或0-VCC，(GP8101)0-5V或0-10V的模拟电压输出

## Installation

There two methods: 
1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_GP8302 library from the Arduino Software Library Manager and download it.

## Methods

```C++
  /**
   * @fn begin
   * @brief 初始化函数。
   */
  bool begin(void);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @param vcc VCC输入的电源电压
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range,float vcc = 5);

  /**
   * @fn setDACOutVoltage
   * @brief 设置不同通道输出DAC值
   * @param data 需要输出的电压值
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   * @param value DAC分辨率 4096 : 12bit ; 32767 : 15bit
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data, uint8_t channel,uint16_t value = 4095);
	
  /**
   * @brief 将设置的电压保存在芯片内部
   */
  void store(void);

  /**
   * @fn setDACOutVoltage
   * @brief 设置输出DAC值
   * @param data 需要输出的电压值
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   * @param vcc VCC输入的电源电压
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range,  uint8_t channel,float vcc = 5);

  /**
   * @fn setDACOutVoltage
   * @brief 设置不同通道输出DAC值
   * @param data 需要输出的电压值
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data, uint8_t channel);

```

## Compatibility

MCU                |  Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |       √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
ESP8266            |      √       |              |             | 
micro:bit          |      √       |              |             | 
FireBeetle M0      |      √       |              |             | 

## History

- 2023/02/10 - Version 1.0.0 released.

## Credits

- Written by   Baikunlin( kunlin.bai@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))