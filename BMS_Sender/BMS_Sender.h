#ifndef _BMS_SENDER_H
#define _BMS_SENDER_H

#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

// Temperature
#define MIN_TEMPERATURE     0
#define MAX_TEMPERATURE     100

// State of Charge
#define MIN_SOC             40
#define MAX_SOC             80

class CBMSParam
{
private:
    float m_temperature;
    float m_stateOfCharge;
public:
    CBMSParam(): m_temperature(0.0), m_stateOfCharge(0.0){} 
    void SetTemperature(float);
    float GetTemperature(void);
    void SetStateOfCharge(float);
    float GetStateOfCharge(void);
};

inline void CBMSParam::SetTemperature(float temperature)
{
    m_temperature = temperature;
}

inline float CBMSParam::GetTemperature(void)
{
    return m_temperature;
}

inline void CBMSParam::SetStateOfCharge(float soc)
{
    m_stateOfCharge = soc;
}

inline float CBMSParam::GetStateOfCharge(void)
{
    return m_stateOfCharge;
}

class CBMSDataGenerator
{
private:

    CBMSParam m_param;

public:

    CBMSDataGenerator();
    float GenerateTemperature();
    float GenerateStateOfCharge();
    int RandomNumberGenerator(int , int);
    void StreamDataToConsole(std::stringstream data);
    std::stringstream GenerateJSON(void);
    bool ValidateData(float value, int minVal, int maxVal);
};

#endif