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
4. (GP8501,GP8101)将0%-100%占空比的PWM信号输入，线性转换成(GP8501)0-2.5V或0-VCC(GP8101)0-5V或0-10V的模拟电压输出

## 库安装

1. 下载库至树莓派，要使用这个库，首先要将库下载到Raspberry Pi，命令下载方法如下:<br>
```python
sudo git clone https://github.com/DFRobot/DFRobot_GP8403
```
2. 打开并运行例程，要执行一个例程demo_x.py，请在命令行中输入python demo_x.py。

## 方法

```python

  '''!
     @brief 初始化函数
  '''
  def begin(self)

  '''!
    @brief 设置DAC输出范围
    @param VCC 输入的电源电压
    @param mode DAC输出范围
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

  '''!
    @brief 设置输出DAC值
    @param data 需要输出的电压值
  '''
  def set_DAC_out_voltage(self, data)

  '''!
    @brief 设置DAC输出范围
    @param mode DAC输出范围
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

  '''!
    @brief 设置DAC输出范围
    @param mode DAC输出范围
    @param frequency PWM频率
  '''
  def set_DAC_outrange(self, mode, frequency)
 
```

## 兼容性

| 主板         | 通过 | 未通过 | 未测试 | 备注 |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python 版本

| Python  | 通过 | 未通过 | 未测试 | 备注 |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |


## 历史

- 2023/2/10 - 1.0.0 版本

## 创作者

- Written by  Baikunlin( kunlin.bai@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))

