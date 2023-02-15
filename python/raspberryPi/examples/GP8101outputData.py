# -*- coding:utf-8 -*-
'''!
  @file  GP8101output_data.py
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

DAC = DFRobot_GP8101()
DAC.begin()
print("init succeed")
# Set output range
DAC.set_DAC_outrange(OUTPUT_RANGE_5V, 100)

DAC.set_DAC_out_voltage(2500)




