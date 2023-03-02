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
4. (GP8501,GP8101)将0%-100%占空比的PWM信号输入，线性转换成(GP8501)0-2.5V或0-VCC(GP8101)0-5V或0-10V的模拟电压输出

## Installation

There two methods: 
1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_GP8302 library from the Arduino Software Library Manager and download it.

## Methods

```python
 
#################I2C转2路0-2.5/VCC 模拟电压模块(GP8503)#################
  '''!
     @brief 初始化函数
  '''
  def begin(self)

  '''!
    @brief 设置DAC输出范围
    @param VCC 输入的电源电压
    @param mode DAC输出范围
    @n     OUTPUT_RANGE_2_5V(0-2.5V)
    @n     OUTPUT_RANGE_VCC(0-VCC)
  '''
  def set_DAC_outrange(self, mode, vcc)

  '''!
    @brief 设置不同通道输出DAC值
    @param data 需要输出的电压值
    @param channel 输出通道 0:通道0;1:通道1;2:全部道
    @param value DAC分辨率 4096 : 12bit ; 32767 : 15bit
  '''
  def set_DAC_out_voltage(self, data, channel, value=4095)

  '''!
    @brief   将设置的电压保存在芯片内部
  '''
  def store(self)

#################I2C转0-2.5/VCC (15bit) 模拟电压模块(GP8512)#################

  '''!
    @brief 初始化函数
  '''
  def begin(self)

  '''!
    @brief 设置DAC输出范围
    @param VCC 输入的电源电压
    @param mode DAC输出范围
    @n     OUTPUT_RANGE_2_5V(0-2.5V)
    @n     OUTPUT_RANGE_VCC(0-VCC)
  '''
  def set_DAC_outrange(self, mode, vcc=5)


  '''!
    @brief 设置输出DAC值
    @param data 需要输出的电压值
  '''
  def set_DAC_out_voltage(self, data)

  '''!
    @brief   将设置的电压保存在芯片内部
  '''
  def store(self)

#################PWM转2路0-2.5V/VCC 模拟电压模块(GP8501)#################
  '''!
    @brief 初始化函数
  '''
  def begin(self)

  '''!
    @brief 设置DAC输出范围
    @param mode DAC输出范围
    @n     OUTPUT_RANGE_2_5V(0-2.5V)
    @n     OUTPUT_RANGE_VCC(0-VCC)
    @param frequency PWM频率
    @param channel 输出通道 0:通道0;1:通道1;2:全部通道
    @param vcc VCC输入的电源电压
  '''
  def set_DAC_outrange(self, mode, frequency, vcc)

  '''!
    @brief 设置不同通道输出DAC值
    @param data 需要输出的电压值
    @param channel 输出通道 0:通道0;1:通道1;2:全部通道
  '''
  def set_DAC_out_voltage(self, data, channel)

#################PWM转2路0-2.5V/VCC 模拟电压模块(GP8101)#################

  '''!
    @brief 初始化函数
  '''
  def begin(self)

  '''!
    @brief 设置DAC输出范围
    @param mode DAC输出范围
    @n     OUTPUT_RANGE_5V(0-5V)
    @n     OUTPUT_RANGE_10V(0-10V)
    @param frequency PWM频率
  '''
  def set_DAC_outrange(self, mode, frequency)

  '''!
    @brief 设置不同通道输出DAC值
    @param data 需要输出的电压值
  '''
  def set_DAC_out_voltage(self, data)

```

## Compatibility

| MCU         | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |

## History

- 2023/02/10 - Version 1.0.0 released.

## Credits

- Written by   Baikunlin( kunlin.bai@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))