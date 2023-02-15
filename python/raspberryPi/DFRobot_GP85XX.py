# -*- coding: utf-8 -*
'''!
  @file  DFRobot_GP85XX.py
  @brief
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [Baikunlin](kunlin.bai@dfrobot.com)
  @version  V1.0
  @date  2023-02-10
  @url  https://github.com/DFRobot/DFRobot_GP85XX
'''

from __future__ import print_function
import smbus
import time
import datetime
import RPi.GPIO as GPIO

## i2c address
DF2301Q_I2C_ADDR = 0x58
##Select DAC output voltage of 0-2.5V
OUTPUT_RANGE_5V = 0
##Select DAC output voltage of 0-VCC
OUTPUT_RANGE_10V = 17
##Select DAC output voltage of 0-2.5V
OUTPUT_RANGE_2_5V = 0
##Select DAC output voltage of 0-VCC
OUTPUT_RANGE_VCC = 17


class DFRobot_GP85XX(object):
  def __init__(self):
    '''!
      @brief Module init
    '''
    pass


class DFRobot_GP8503(DFRobot_GP85XX):
  ## Configure sensor register
  GP8503_CONFIG_CURRENT_REG = 0x02
  ## Store function timing start head
  GP8503_STORE_TIMING_HEAD = 0x02
  ## The first address for entering store timing
  GP8503_STORE_TIMING_ADDR = 0x10
  ## The command 1 to enter store timing
  GP8503_STORE_TIMING_CMD1 = 0x03
  ## The command 2 to enter store timing
  GP8503_STORE_TIMING_CMD2 = 0x00
  ## Total I2C communication cycle 5us
  I2C_CYCLE_TOTAL = 0.000005
  ## The first half cycle of the total I2C communication cycle 2us
  I2C_CYCLE_BEFORE = 0.000002
  ## The second half cycle of the total I2C communication cycle 3us
  I2C_CYCLE_AFTER = 0.000003

  GP8503_STORE_TIMING_DELAY = 0.000010

  def __init__(self, addr=DF2301Q_I2C_ADDR):
    self._addr = addr
    self.outPutSetRange = 0x01
    self.voltage = 5000
    self._scl = 3
    self._sda = 2
    self.dataTransmission = 0
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    self.i2c = smbus.SMBus(1)

  def begin(self):
    '''!
      @param Initialize the sensor
    '''
    if self.i2c.read_byte(self._addr) != 0:
      return 0
    return 1

  def set_DAC_outrange(self, mode, vcc=5):
    '''!
      @brief 设置DAC输出范围
      @param VCC 输入的电源电压
      @param mode DAC输出范围
    '''
    if mode == OUTPUT_RANGE_2_5V:
      self.voltage = 2500
    elif mode == OUTPUT_RANGE_VCC:
      self.voltage = vcc * 1000

  def set_DAC_out_voltage(self, data, channel, value=4095):
    '''!
      @brief 设置不同通道输出DAC值
      @param data 需要输出的电压值
      @param channel 输出通道 0:通道0;1:通道1;2:全部通道
      @param value DAC分辨率 4096 : 12bit ; 32767 : 15bit
    '''

    data = int((float(data) / self.voltage) * value)
    if value == 4095:
      data = int(data) << 4
      self._send_data(data, channel)
    else:
      self._send_data(data, 0)

  def store(self):
    '''!
      @brief   将设置的电压保存在芯片内部
    '''
    GPIO.setup(self._scl, GPIO.OUT)
    GPIO.setup(self._sda, GPIO.OUT)
    self._start_signal()
    self._send_byte(self.GP8503_STORE_TIMING_HEAD, 0, 3, False)
    self._stop_signal()
    self._start_signal()
    self._send_byte(self.GP8503_STORE_TIMING_ADDR)
    self._send_byte(self.GP8503_STORE_TIMING_CMD1)
    self._stop_signal()

    self._start_signal()
    self._send_byte(self._addr << 1, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2, 1)
    self._stop_signal()

    time.sleep(self.GP8503_STORE_TIMING_DELAY)

    self._start_signal()
    self._send_byte(self.GP8503_STORE_TIMING_HEAD, 0, 3, False)
    self._stop_signal()
    self._start_signal()
    self._send_byte(self.GP8503_STORE_TIMING_ADDR)
    self._send_byte(self.GP8503_STORE_TIMING_CMD2)
    self._stop_signal()

  def _send_data(self, data, channel):
    if channel == 0:
      self.i2c.write_word_data(self._addr, self.GP8503_CONFIG_CURRENT_REG, data)
    elif channel == 1:
      self.i2c.write_word_data(self._addr, self.GP8503_CONFIG_CURRENT_REG << 1, data)
    else:
      self.i2c.write_word_data(self._addr, self.GP8503_CONFIG_CURRENT_REG, data)
      self.i2c.write_word_data(self._addr, self.GP8503_CONFIG_CURRENT_REG << 1, data)

  def _start_signal(self):
    GPIO.output(self._scl, GPIO.HIGH)
    GPIO.output(self._sda, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._sda, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_AFTER)
    GPIO.output(self._scl, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_TOTAL)

  def _stop_signal(self):
    GPIO.output(self._sda, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_TOTAL)
    GPIO.output(self._sda, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_TOTAL)

  def _recv_ack(self, ack=0):
    ack_ = 0
    error_time = 0
    GPIO.setup(self._sda, GPIO.IN)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_AFTER)
    while GPIO.input(self._sda) != ack:
      time.sleep(0.000001)
      error_time += 1
      if error_time > 250:
        break
    ack_ = GPIO.input(self._sda)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_AFTER)
    GPIO.setup(self._sda, GPIO.OUT)
    return ack_

  def _send_byte(self, data, ack=0, bits=8, flag=True):
    i = bits
    data = data & 0xFF
    while i > 0:
      i -= 1
      if data & (1 << i):
        GPIO.output(self._sda, GPIO.HIGH)
      else:
        GPIO.output(self._sda, GPIO.LOW)
      time.sleep(self.I2C_CYCLE_BEFORE)
      GPIO.output(self._scl, GPIO.HIGH)
      time.sleep(self.I2C_CYCLE_TOTAL)
      GPIO.output(self._scl, GPIO.LOW)
      time.sleep(self.I2C_CYCLE_AFTER)
    if flag:
      return self._recv_ack(ack)
    else:
      GPIO.output(self._sda, GPIO.LOW)
      GPIO.output(self._scl, GPIO.HIGH)
    return ack


class DFRobot_GP8512(DFRobot_GP85XX):

  def __init__(self):

    self.gp8503 = DFRobot_GP8503(DF2301Q_I2C_ADDR)

  def begin(self):
    '''!
     @brief 初始化函数
    '''
    return self.gp8503.begin()

  def set_DAC_outrange(self, mode, vcc=5):
    '''!
      @brief 设置DAC输出范围
      @param VCC 输入的电源电压
      @param mode DAC输出范围
    '''
    if mode == OUTPUT_RANGE_2_5V:
      self.gp8503.set_DAC_outrange(mode)
    elif mode == OUTPUT_RANGE_VCC:
      self.gp8503.set_DAC_outrange(mode, vcc)

  def set_DAC_out_voltage(self, data):
    '''!
      @brief 设置输出DAC值
      @param data 需要输出的电压值
    '''
    self.gp8503.set_DAC_out_voltage(data, 0, 32767)

  def store(self):
    '''!
      @brief   将设置的电压保存在芯片内部
    '''
    self.gp8503.store()


class DFRobot_GP8501(DFRobot_GP85XX):

  def __init__(self):
    self.voltage = 5000
    self.R0 = 18
    self.R1 = 12

  def begin(self):
    '''!
      @brief 初始化函数
    '''
    GPIO.setwarnings(False)  # 屏蔽警告
    GPIO.setmode(GPIO.BCM)  # 设置引脚模式BCM
    GPIO.setup(self.R0, GPIO.OUT)  # 设置引脚R0方向输出
    GPIO.setup(self.R1, GPIO.OUT)  # 设置引脚R1方向输出

  def set_DAC_outrange(self, mode, frequency, channel, vcc=5):
    '''!
      @brief 设置DAC输出范围
      @param mode DAC输出范围
      @param frequency PWM频率
      @param channel 输出通道 0:通道0;1:通道1;2:全部通道
      @param vcc VCC输入的电源电压
    '''
    if mode == OUTPUT_RANGE_2_5V:
      self.voltage = 2500
    elif mode == OUTPUT_RANGE_VCC:
      self.voltage = vcc * 1000
    if channel == 0:
      self.PR0 = GPIO.PWM(self.R0, frequency)
      self.PR0.start(0)
    elif channel == 1:
      self.PR1 = GPIO.PWM(self.R1, frequency)
      self.PR1.start(0)
    else:
      self.PR0 = GPIO.PWM(self.R0, frequency)
      self.PR0.start(0)
      self.PR1 = GPIO.PWM(self.R1, frequency)
      self.PR1.start(0)

  def set_DAC_out_voltage(self, data, channel):
    '''!
      @brief 设置不同通道输出DAC值
      @param data 需要输出的电压值
      @param channel 输出通道 0:通道0;1:通道1;2:全部通道
    '''
    data = int(data / self.voltage) * 100

    if data > 100:
      data = 100
    if data < 0:
      data = 0
    if channel == 0:
      self.PR0.ChangeDutyCycle(data)
    elif channel == 1:
      self.PR1.ChangeDutyCycle(data)
    else:
      self.PR0.ChangeDutyCycle(data)
      self.PR1.ChangeDutyCycle(data)


class DFRobot_GP8101(DFRobot_GP85XX):

  def __init__(self):
    self.voltage = 5000
    self.R = 18

  def begin(self):
    '''!
      @brief 初始化函数
    '''
    GPIO.setwarnings(False)  # 屏蔽警告
    GPIO.setmode(GPIO.BCM)  # 设置引脚模式BCM
    GPIO.setup(self.R, GPIO.OUT)  # 设置引脚18方向输出

  def set_DAC_outrange(self, mode, frequency):
    '''!
      @brief 设置DAC输出范围
      @param mode DAC输出范围
      @param frequency PWM频率
    '''
    if mode == OUTPUT_RANGE_5V:
      self.voltage = 5000
    elif mode == OUTPUT_RANGE_10V:
      self.voltage = 10000
    self.PR = GPIO.PWM(self.R, frequency)
    self.PR.start(0)

  def set_DAC_out_voltage(self, data):
    '''!
      @brief 设置输出DAC值
      @param data 需要输出的电压值
    '''
    data = data / self.voltage * 100
    if data > 100:
      data = 100
    if data < 0:
      data = 0
    self.PR.ChangeDutyCycle(data)
