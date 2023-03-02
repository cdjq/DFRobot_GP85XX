# -*- coding:utf-8 -*-
'''!
  @file  GP8512output_data.py
  @brief
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

DAC = DFRobot_GP8512()
'''!
  @brief 初始化函数
'''
status = DAC.begin()
print("init succeed")
'''!
  @brief 设置DAC输出范围
  @param mode DAC输出范围
  @n     OUTPUT_RANGE_2_5V(0-2.5V)
  @n     OUTPUT_RANGE_VCC(0-VCC)
  @param vcc VCC输入的电源电压
'''
DAC.set_DAC_outrange(OUTPUT_RANGE_2_5V)
'''!
  @brief 设置输出DAC值
  @param data 需要输出的电压值,范围（0-2500）或（0-VCC*1000）
'''
DAC.set_DAC_out_voltage(1500)
'''!
  @brief   将设置的电压保存在芯片内部
'''
DAC.store()



