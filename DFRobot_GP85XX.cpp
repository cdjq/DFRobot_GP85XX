/*!
  * @file DFRobot_GP85XX.h
  * @brief 
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP85XX
  */
 
#include "DFRobot_GP85XX.h"

#define GP85XX_STORE_TIMING_HEAD            0x02  ///< Store function timing start head
#define GP85XX_STORE_TIMING_ADDR            0x10  ///< The first address for entering store timing
#define GP85XX_STORE_TIMING_CMD1            0x03  ///< The command 1 to enter store timing
#define GP85XX_STORE_TIMING_CMD2            0x00  ///< The command 2 to enter store timing
#define GP85XX_STORE_TIMING_DELAY           10    ///< Store procedure interval delay time: 10ms, more than 7ms
#define I2C_CYCLE_TOTAL                     5     ///< Total I2C communication cycle
#define I2C_CYCLE_BEFORE                    1     ///< The first half cycle 2 of the total I2C communication cycle
#define I2C_CYCLE_AFTER                     2     ///< The second half cycle 3 of the total I2C communication cycle
#define PWM_PASSAGG0                        0
#define PWM_PASSAGG1                        1

DFRobot_GP85XX::DFRobot_GP85XX()
{
}


/**************************************************************************
                       I2C转2路0-2.5/VCC 模拟电压模块(GP8503)
 **************************************************************************/
DFRobot_GP8503::DFRobot_GP8503(TwoWire *pWire,uint8_t addr)
{
  _pWire = pWire;
  _addr = addr;
}


void DFRobot_GP8503::begin(void)
{
  _pWire->begin();
}


void DFRobot_GP8503::setDACOutRange(eOutPutRange_t range,float vcc)
{
  if(range == eOutPutRange_t::eOutputRange2_5V)
  {
    _voltage = 2500;
  }else{
    _voltage = vcc*1000;
  }
}


void DFRobot_GP8503::setDACOutVoltage(uint16_t data, uint8_t channel,uint16_t value)
{
  if(data > _voltage){
    data = _voltage;
  }
  data = (uint16_t)round(((float)data / _voltage) * value);
  Serial.println(data);
  if(value == 4095 ){
    data = data << 4;
    sendData(data, channel);
  }else{
    sendData(data, 0);
  }
}


void DFRobot_GP8503::sendData(uint16_t data, uint8_t channel)
{
  if(channel == 0){
    _pWire->beginTransmission(_addr);
    _pWire->write(GP85XX_CONFIG_CURRENT_REG);
    _pWire->write(data & 0xff);
    _pWire->write((data >>8) & 0xff);
    _pWire->endTransmission();
  }else if(channel == 1){
	_pWire->beginTransmission(_addr);
    _pWire->write(GP85XX_CONFIG_CURRENT_REG<<1);
    _pWire->write(data & 0xff);
    _pWire->write((data >>8) & 0xff);
    _pWire->endTransmission();
  }else{
    _pWire->beginTransmission(_addr);
    _pWire->write(GP85XX_CONFIG_CURRENT_REG);
    _pWire->write(data & 0xff);
    _pWire->write((data >>8) & 0xff);
    _pWire->write(data & 0xff);
    _pWire->write((data >>8) & 0xff);
    _pWire->endTransmission();
  }
}


void DFRobot_GP8503::store(void)
{
  #if defined(ESP32)
    _pWire->~TwoWire();
  #elif !defined(ESP8266)
    _pWire->end();
  #endif
  
  pinMode(_scl, OUTPUT);
  pinMode(_sda, OUTPUT);
  digitalWrite(_scl, HIGH);
  digitalWrite(_sda, HIGH);
  startSignal();
  sendByte(GP85XX_STORE_TIMING_HEAD, 0, 3, false);
  stopSignal();
  startSignal();
  sendByte(GP85XX_STORE_TIMING_ADDR,0);
  sendByte(GP85XX_STORE_TIMING_CMD1,0);
  stopSignal();
  
  startSignal();
  sendByte(_addr<<1, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  sendByte(GP85XX_STORE_TIMING_CMD2, 1);
  stopSignal();

  delay(GP85XX_STORE_TIMING_DELAY);

  startSignal();
  sendByte(GP85XX_STORE_TIMING_HEAD, 0, 3, false);
  stopSignal();
  startSignal();
  sendByte(GP85XX_STORE_TIMING_ADDR);
  sendByte(GP85XX_STORE_TIMING_CMD2);
  stopSignal();
  _pWire->begin();
}


void DFRobot_GP8503::startSignal(void)
{
  digitalWrite(_scl,HIGH);
  digitalWrite(_sda,HIGH);
  delayMicroseconds(I2C_CYCLE_BEFORE);
  digitalWrite(_sda,LOW);
  delayMicroseconds(I2C_CYCLE_AFTER);
  digitalWrite(_scl,LOW);
  delayMicroseconds(I2C_CYCLE_TOTAL);
}


void DFRobot_GP8503::stopSignal(void)
{
  digitalWrite(_sda,LOW);
  delayMicroseconds(I2C_CYCLE_BEFORE);
  digitalWrite(_scl,HIGH);
  delayMicroseconds(I2C_CYCLE_TOTAL);
  digitalWrite(_sda,HIGH);
  delayMicroseconds(I2C_CYCLE_TOTAL);
}


uint8_t DFRobot_GP8503::sendByte(uint8_t data, uint8_t ack, uint8_t bits, bool flag)
{
  for(int i=bits-1; i>=0;i--){  
    if(data & (1<<i)){
      digitalWrite(_sda,HIGH);
    }else{
      digitalWrite(_sda,LOW);
    }
    delayMicroseconds(I2C_CYCLE_BEFORE); 
    digitalWrite(_scl,HIGH);
    delayMicroseconds(I2C_CYCLE_TOTAL);
    digitalWrite(_scl,LOW);
    delayMicroseconds(I2C_CYCLE_AFTER); 
  }
  if(flag) return recvAck(ack);
  else {
    digitalWrite(_sda,LOW);
    digitalWrite(_scl,HIGH);
    return 0;
  }
}


uint8_t DFRobot_GP8503::recvAck(uint8_t ack)
{
  uint8_t ack_=0;
  uint16_t errorTime = 0;
  pinMode(_sda,INPUT_PULLUP);
  digitalWrite(_sda,HIGH);
  delayMicroseconds(I2C_CYCLE_BEFORE);
  digitalWrite(_scl,HIGH);
  delayMicroseconds(I2C_CYCLE_AFTER);
  while(digitalRead(_sda) != ack){
      delayMicroseconds(1);
      errorTime++;
      if(errorTime > 250) break;
  }
  ack_=digitalRead(_sda);
  delayMicroseconds(I2C_CYCLE_BEFORE);
  digitalWrite(_scl,LOW);
  delayMicroseconds(I2C_CYCLE_AFTER);
  pinMode(_sda,OUTPUT);
  return ack_;
}


/**************************************************************************
                       I2C转0-2.5/VCC (15bit) 模拟电压模块(GP8512)
 **************************************************************************/

DFRobot_GP8512::DFRobot_GP8512()
{
}
 
void DFRobot_GP8512::begin(void)
{
  _pgp8503.begin();
}


void DFRobot_GP8512::setDACOutRange(eOutPutRange_t range,float vcc)
{
  if(range == eOutputRange2_5V){
    _pgp8503.setDACOutRange(_pgp8503.eOutputRange2_5V,vcc);
  }else{
    _pgp8503.setDACOutRange(_pgp8503.eOutputRangeVCC,vcc);
  }
  
}


void DFRobot_GP8512::setDACOutVoltage(uint16_t data)
{
  _pgp8503.setDACOutVoltage(data,0,32767);
}


void DFRobot_GP8512::store(void)
{
  _pgp8503.store();
}


void DFRobot_GP8512::sendData(uint16_t data)
{
  _pgp8503.sendData(data,0);
}

/**************************************************************************
                       PWM转0-5V/VCC 模拟电压模块(GP8101)
 **************************************************************************/
 
void DFRobot_GP8101::begin(uint8_t pin)
{
  _pin = pin;
  #if defined(ESP32)  
    ledcSetup(PWM_PASSAGG0, 5000, 13);  ////分辨率为12位，即占空比可选0~8191
	ledcAttachPin(_pin, PWM_PASSAGG0);
  #elif defined(ESP8266) 
    analogWriteRange(8191);
  #else 
    pinMode(_pin,OUTPUT);
  #endif
}

void DFRobot_GP8101::setDACOutRange(eOutPutRange_t range)
{
   if(range == eOutPutRange_t::eOutputRange5V)
  {
    _voltage = 5000;
  }else{
    _voltage = 10000;
  }
}


void DFRobot_GP8101::setDACOutVoltage(uint16_t data)
{
  if(data > _voltage){
    data = _voltage;
  }
  #if defined(ESP32) || defined(ESP8266)
    data = (uint16_t)round(((float)data/_voltage)* 8191);
  #else 
    data = (uint16_t)round(((float)data/_voltage)* 255);
  #endif
  sendData(data); 
}


void DFRobot_GP8101::sendData(uint16_t data)
{
  #if defined(ESP32)  
    ledcWrite(PWM_PASSAGG0, data);
  #else 
    analogWrite(_pin, data);
  #endif
}
 
/**************************************************************************
                       PWM转2路0-2.5V/VCC 模拟电压模块(GP8501)
 **************************************************************************/


void DFRobot_GP8501::begin(uint8_t pin)
{
  _pin0 = pin;
   #if defined(ESP32)  
    ledcSetup(PWM_PASSAGG0, 5000, 13);  ////分辨率为12位，即占空比可选0~8191
	ledcAttachPin(_pin0, PWM_PASSAGG0);
  #elif defined(ESP8266) 
    analogWriteRange(8191);
  #else 
    pinMode(_pin0,OUTPUT);
  #endif
}


void DFRobot_GP8501::begin(uint8_t pin0,uint8_t pin1)
{
  _pin0 = pin0;
  _pin1 = pin1;
  #if defined(ESP32)  
    ledcSetup(PWM_PASSAGG0, 5000, 13);  ////分辨率为13位，即占空比可选0~8191
	ledcSetup(PWM_PASSAGG1, 5000, 13);
	ledcAttachPin(_pin0, PWM_PASSAGG0);
	ledcAttachPin(_pin1, PWM_PASSAGG1);
  #elif defined(ESP8266) 
    analogWriteRange(8191);
  #else 
    pinMode(_pin0,OUTPUT);
    pinMode(_pin1,OUTPUT);
  #endif
}


void DFRobot_GP8501::setDACOutRange(eOutPutRange_t range, float vcc)
{
  if(range == eOutPutRange_t::eOutputRange2_5V)
  {
    _voltage = 2500;
  }else{
    _voltage = vcc*1000;
  }
}


void DFRobot_GP8501::setDACOutVoltage(uint16_t data , uint8_t channel)
{ 
  if(data > _voltage){
    data = _voltage;
  }
  #if defined(ESP32) || defined(ESP8266)
    data = (uint16_t)round(((float)data/_voltage)* 8191);
  #else 
    data = (uint16_t)round(((float)data/_voltage)* 255);
  #endif
  sendData(data, channel);
}


void DFRobot_GP8501::sendData(uint16_t data, uint8_t channel)
{
  #if defined(ESP32)  
    if(channel == 0){
      ledcWrite(PWM_PASSAGG0, data);
    }else if(channel == 1){
      ledcWrite(PWM_PASSAGG1, data);
    }else{
      ledcWrite(PWM_PASSAGG0, data);
	  ledcWrite(PWM_PASSAGG1, data);
    }
  #else 
    if(channel == 0){
      analogWrite(_pin0, data);
    }else if(channel == 1){
      analogWrite(_pin1, data);
    }else{
      analogWrite(_pin0, data);
	  analogWrite(_pin1, data);
    }
  #endif
}