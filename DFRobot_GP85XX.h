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


#ifndef _DFROBOT_GP85XX_H_
#define _DFROBOT_GP85XX_H_

#include "Arduino.h"
#include "Wire.h"

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif


#define DFGP85XX_I2C_ADDR                    uint8_t(0x58)   //!< i2c address
#define GP85XX_CONFIG_CURRENT_REG            uint8_t(0x02)

class DFRobot_GP85XX
{
  public:
    
    /**
     * @fn DFRobot_GP85XX
     * @brief Constructor 
     * @return None
     */
    DFRobot_GP85XX();
  
  private:
  
};

/**************************************************************************
                       I2C转2路0-2.5/VCC 模拟电压模块(GP8503)
 **************************************************************************/
class DFRobot_GP8503: public DFRobot_GP85XX
{
  public:
  
    /**
     * @enum eOutPutRange_t
     * @brief Analog voltage output range select
     */
    typedef enum{
      eOutputRange2_5V = 0,
      eOutputRangeVCC = 1,
    }eOutPutRange_t;
  
    /**
     * @brief DFRobot_GP85XX constructor
     * @param pWire I2C object
     * @param addr I2C address
     */
    DFRobot_GP8503(TwoWire *pWire = &Wire,uint8_t addr = DFGP85XX_I2C_ADDR);

    /**
     * @fn begin
     * @brief 初始化函数
     */
    void begin(void);

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
	
	/**
     * @fn sendData
     * @brief 设置IIC输入值
     * @param data 需要设置的输入值(0-fff)
     * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
     * @return NONE
     */
	void sendData(uint16_t data, uint8_t channel);

    protected:
  
    void startSignal(void);
	
    void stopSignal(void);
	
    uint8_t recvAck(uint8_t ack);
	
    uint8_t sendByte(uint8_t data, uint8_t ack = 0, uint8_t bits = 8, bool flag = true);
  
  private:
  
    TwoWire *_pWire;
    int _scl= SCL;
    int _sda = SDA;
    uint8_t _addr;
    uint16_t _voltage = 0;
    
};

/**************************************************************************
                       I2C转0-2.5/VCC (15bit) 模拟电压模块(GP8512)
 **************************************************************************/
class DFRobot_GP8512: public DFRobot_GP85XX
{
  public:
  
    typedef enum{
      eOutputRange2_5V = 0,
      eOutputRangeVCC = 1,
    }eOutPutRange_t;
  
    DFRobot_GP8512();
	
	/**
     * @fn begin
     * @brief 初始化函数
     */
    void begin(void);

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
	
	/**
     * @fn sendData
     * @brief 设置IIC输入值
     * @param data 需要设置的输入值(0-7fff)
     * @return NONE
     */
	void sendData(uint16_t data);
  
  private:
    
    DFRobot_GP8503 _pgp8503;
  
};

/**************************************************************************
                       PWM转0-5V/VCC 模拟电压模块(GP8101)
 **************************************************************************/
class DFRobot_GP8101: public DFRobot_GP8512
{
  public:
    typedef enum{
      eOutputRange5V = 0,
      eOutputRange10V= 1,
    }eOutPutRange_t;
    
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
     * @n     eOutputRange5V(0-5V)
     * @n     eOutputRange10V(0-10V)
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
     * @param data 需要设置的占空比(0-255),ESP32和ESP8266为：(0-8191)
     * @return NONE
     */
	void sendData(uint16_t data);
  
    private:
  
    uint16_t _voltage = 0;
	uint16_t _frequency = 2000;
	uint8_t _pin;
  
};

/**************************************************************************
                       PWM转2路0-2.5V/VCC 模拟电压模块(GP8501)
 **************************************************************************/
class DFRobot_GP8501: public DFRobot_GP85XX
{
  public:
  
    typedef enum{
      eOutputRange2_5V = 0,
      eOutputRangeVCC = 1,
    }eOutPutRange_t;
    
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
  
  private:
  
    uint16_t _voltage = 0;
    uint16_t _frequency = 2000;
	uint8_t _pin0;
	uint8_t _pin1;
  
};

#endif