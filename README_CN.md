# DFRobot_GP85XX
* [English Version](./README.md)

这是四个DAC模块。用户可以通过I2C和PWM占空比两种输入方式控制此模块输出电压，它具有以下特点：
1. 能够控制输出0-2.5V或0-VCC电压，0-5V或0-10V电压。
2. 采用I2C和PWM占空比两种输入方式控制输出电压大小，I2C默认地址为0x58。 
3. (GP8503,GP8512)模块掉电后，输出电压配置将丢失，如果想下次上电采用此次配置，需保存配置。

## 产品链接([www.dfrobot.com](www.dfrobot.com))

    SKU:

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

提供一个Arduino库给四个DAC模块(GP8503,GP8512,GP8501,GP8101)，设置和保存模块输出的电压配置，此库具有以下功能：
1. (GP8503,GP8512,GP8501)设置0-2.5V的电压或0-VCC电压,(GP8101)设置0-5V的电压或0-10V电压
2. (GP8503,GP8512)通过IIC设置DAC范围输出对应的电压,DAC分辨率15bit(0 ~ 0x7FFF)，12bit(0 ~ 0xFFF)；
3. (GP8503,GP8512)保存电压配置，掉电后，该配置不丢失。
4. (GP8501,GP8101)将0%-100%占空比的PWM信号输入，线性转换成(GP8501)0-2.5V或0-VCC，(GP8101)0-5V或0-10V的模拟电压输出

## 库安装

这里有2种安装方法：
1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_GP8403 库

## 方法

```C++

/**************************************************************************
                       I2C转2路0-2.5/VCC 模拟电压模块(GP8503)
 **************************************************************************/

  /**
   * @fn begin
   * @brief 初始化函数。
   */
  bool begin(void);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-2.5V)
   * @n     eOutputRangeVCC(0-VCC)
   * @param vcc VCC输入的电源电压,VCC范围(2.7V-5.5V)
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

/**************************************************************************
                       I2C转0-2.5/VCC (15bit) 模拟电压模块(GP8512)
 **************************************************************************/

  /**
   * @fn begin
   * @brief 初始化函数。
   */
  bool begin(void);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-2.5V)
   * @n     eOutputRangeVCC(0-VCC)
   * @param vcc VCC输入的电源电压,VCC范围(2.7V-5.5V)
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range,float vcc = 5);

  /**
   * @fn setDACOutVoltage
   * @brief 设置输出DAC值
   * @param data 需要输出的电压值
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data);

  /**
   * @brief 将设置的电压保存在芯片内部
   */
  void store(void);

/**************************************************************************
                       I2C转0-2.5/VCC (15bit) 模拟电压模块(GP8101)
 **************************************************************************/

  /**
   * @fn begin
   * @param pin PWM出输出接口
   * @brief 初始化函数
   */
  void begin(uint8_t pin);

  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-5V)
   * @n     eOutputRangeVCC(0-10V)
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range);

  /**
   * @fn setDACOutVoltage
   * @brief 设置输出DAC值
   * @param data 需要输出的电压值
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data);
	
	/**
   * @fn sendData
   * @brief 设置PWM占空比
   * @param data 需要设置的占空比
   * @return NONE
   */
	void sendData(uint16_t data);

/**************************************************************************
                       PWM转2路0-2.5V/VCC 模拟电压模块(GP8501)
 **************************************************************************/

  /**
   * @fn begin
   * @brief 初始化函数
   * @param pin0 PWM输出引脚0
   * @param pin1 PWM输出引脚1
   */
  void begin(uint8_t pin0,uint8_t pin1);
	
	/**
   * @fn begin
   * @brief 初始化函数
   * @param pin PWM输出引脚   
   */
	void begin(uint8_t pin);
  
  /**
   * @fn setDACOutRange
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange2_5V(0-2.5V)
   * @n     eOutputRangeVCC(0-VCC)
   * @param vcc VCC输入的电源电压,VCC范围(2.7V-5.5V)
   * @return NONE
   */	
  void setDACOutRange(eOutPutRange_t range, float vcc = 5);
  
  /**
   * @fn setDACOutVoltage
   * @brief 设置不同通道输出DAC值
   * @param data 需要输出的电压值
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   * @return NONE
   */
  void setDACOutVoltage(uint16_t data, uint8_t channel);
	
	/**
   * @fn sendData
   * @brief 设置PWM占空比
   * @param data 需要设置的占空比
   * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
   * @return NONE
   */
	void sendData(uint16_t data, uint8_t channel);

```

## 兼容性

主板               | 通过          | 未通过      | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |       √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
ESP8266            |      √       |              |             | 
micro:bit          |      √       |              |             | 
FireBeetle M0      |      √       |              |             | 


## 历史

- 2023/2/10 - 1.0.0 版本

## 创作者

- Written by  Baikunlin( kunlin.bai@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))

