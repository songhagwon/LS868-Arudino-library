#pragma once

/**
* File		LS868.h
* Version	v 1.2
* Date		2017. 06. 12
* Details	checkPacket() ����Լ��� ������ private�� ����
*
* Copyright 2016. (��)����Ƽ���ͳ��ų� all rights reserved.
**/

/**
* berief
*	LS868 Motor Shield �� ��ȣ�� ���� ���̺귯�� �ۼ�
*	SoftwareSerial RX 12 Pin
*				   TX 13 Pin
*	Motor Direction 11 Pin
**/

#ifndef LS868_h
#define LS868_h

#include <stdint.h>
#include <Arduino.h>

// �Ķ���� �����
#define RED		0x52
#define GREEN	0x47
#define BLUE	0x42
#define CW		0x01
#define CCW		0x02
#define ALL		0xFE
#define TORQUE	0x01
#define SPEED	0x02
// LSM ��� ����
#define MICRO	0xB0
#define MINI	0xC0
#define MIDDLE	0xD0
#define MEGA	0xE0
// �ø��� ����
#define HARD_SERIAL	0x01
#define SOFT_SERIAL	0x02


class LS868
{
public:
	// LS868 Parameter 1 : Product ID(Protocal ����), Parameter 2 : �ø��� Ÿ�� ����
	LS868(uint8_t product, uint8_t serial_mode);

	/**
	*
	* Data Get Function
	*
	**/

	uint16_t getModuleID(uint8_t m_id);
	int16_t getNowPosition(uint8_t m_id);
	int16_t getTargetPosition(uint8_t m_id);
	uint16_t getNowCurrent(uint8_t m_id);
	uint16_t getLimitCurrent(uint8_t m_id);
	uint16_t getNowTemperature(uint8_t m_id);
	uint16_t getLimitTemperature(uint8_t m_id);
	uint16_t getGainP(uint8_t m_id);
	uint16_t getGainI(uint8_t m_id);
	uint16_t getGainD(uint8_t m_id);
	uint16_t getControlMargin(uint8_t m_id);
	uint16_t getForwardControl(uint8_t m_id);
	uint16_t getVoltage(uint8_t m_id);
	int16_t getBoundaryMax(uint8_t m_id);
	int16_t getBoundaryMin(uint8_t m_id);
	uint8_t getLEDValue(uint8_t m_id, uint8_t m_color);
	uint16_t getModuleVersion(uint8_t m_id);		// ���� ProductID
	uint16_t getFirmwareVersion(uint8_t m_id);		// ���� firmware version
	uint32_t getBaudRate(uint8_t m_id);
	int16_t getZeroComp(uint8_t m_id);

	/**
	*
	* Data Set Function
	*
	**/

	void setFactoryReset(uint8_t m_id);
	void setModuleID(uint8_t m_id, uint16_t new_id);
	void setSyncPosition(uint8_t m_id, uint8_t m_mode, int16_t m_position);
	void setSyncLEDControl(uint8_t m_id, uint8_t m_r, uint8_t m_g, uint8_t m_b);
	void setLimitCurrent(uint8_t m_id, uint16_t m_current);
	void setLimitTemperature(uint8_t m_id, uint16_t m_temp);
	void setGainP(uint8_t m_id, uint16_t m_p);
	void setGainI(uint8_t m_id, uint16_t m_i);
	void setGainD(uint8_t m_id, uint16_t m_d);
	void setControlMargin(uint8_t m_id, uint16_t m_margin);
	void setForwardControl(uint8_t m_id, uint16_t m_forward);
	void setBoundaryMax(uint8_t m_id, int16_t m_boundarymax);
	void setBoundaryMin(uint8_t m_id, int16_t m_boundarymin);
	void setBaudRate(uint8_t m_id, uint32_t m_baudrate);
	void setZeroComp(uint8_t m_id, uint16_t m_zerocomp);

	/**
	*
	* Action Function
	*
	**/

	void torquePosition(uint8_t m_id, uint8_t m_torque, int16_t m_position);
	void speedPosition(uint8_t m_id, uint8_t m_speed, int16_t m_position);
	void LEDControl(uint8_t m_id, uint8_t m_r, uint8_t m_g, uint8_t m_b);
	void syncPosition(uint8_t m_id, uint8_t m_mode);
	void syncLED(uint8_t m_id);
	void wheelMode(uint8_t m_id, uint8_t m_speed, uint8_t m_direction);
	void activeStop(uint8_t m_id);
	void passiveStop(uint8_t m_id);

	/**
	*
	* ETC. Function
	*
	**/

	void begin(uint32_t baudrate);	// SoftwereSerial ��żӵ� ���� ����Լ�

private:
	uint8_t m_write[8];
	uint8_t m_read[8];
	uint8_t c_write[50];
	uint8_t product_id;
	bool serial_flag;
	int pin_direction;

	bool checkPacket(void);			// Packet Check�� ����Լ�(coding)
	void eepPROG(uint8_t m_id);		// setMotorID, setZeroComp���� �ʿ� ����
	void clearBuffer(void);			// m_write, m_read �ʱ�ȭ
	void mTxWrite(uint8_t m_id, uint8_t m_instruction);
	void mRxWrite(void);
};
#endif // !LS868
