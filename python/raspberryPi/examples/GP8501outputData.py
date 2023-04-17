# -*- coding:utf-8 -*-
'''!
  @file  GP8501output_data.py
  @brief 设置输出通道、电压值和输出范围，将PWM信号转换为2路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [Baikunlin](kunlin.bai@dfrobot.com)
  @version  V1.0
  @date  2023-02-10
  @url  https://github.com/DFRobot/DFRobot_GP85XX
'''

from __future__ import print_function
import sys
import os
import time

sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
from DFRobot_GP85XX import *

DAC = DFRobot_GP8501()
'''!
  @brief 初始化函数
'''
DAC.begin()
print("init succeed")
'''!
  @brief 设置DAC输出范围
  @param mode DAC输出范围
  @n     OUTPUT_RANGE_2_5V(0-2.5V)
  @n     OUTPUT_RANGE_VCC(0-VCC)
  @param frequency PWM频率
  @param channel 输出通道 0:通道0;1:通道1;2:全部通道
  @param vcc VCC输入的电源电压
'''
DAC.set_DAC_outrange(OUTPUT_RANGE_2_5V, 100, 2)
'''!
  @brief 设置不同通道输出DAC值
  @param data 需要输出的电压值,范围（0-2500）或（0-VCC*1000）,VCC范围（2.7V-5.5V）
  @param channel 输出通道 0:通道0;1:通道1;2:全部通道
'''
DAC.set_DAC_out_voltage(2500, 2)




