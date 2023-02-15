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
status = DAC.begin()
if (status != 0):
    while True: time.sleep(1)

print("init succeed")
# Set output range
DAC.set_DAC_outrange(OUTPUT_RANGE_2_5V)

DAC.set_DAC_out_voltage(1500)

DAC.store()


