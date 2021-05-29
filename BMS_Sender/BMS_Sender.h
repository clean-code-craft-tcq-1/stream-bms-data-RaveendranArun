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

#define TEMP_JSON_INDEX     1
#define SOC_JSON_INDEX      3

typedef struct BmsData
{
    float temperature;
    float stateOfCharge;
}BmsData;

class CBMSParam
{
private:
    BmsData m_data;
public:
    CBMSParam()
    {
        m_data.temperature = 0.0;
        m_data.stateOfCharge = 0.0;
    }

    void SetTemperature(float);
    float GetTemperature(void);
    void SetStateOfCharge(float);
    float GetStateOfCharge(void);
};

inline void CBMSParam::SetTemperature(float temperature)
{
    m_data.temperature = temperature;
}

inline float CBMSParam::GetTemperature(void)
{
    return m_data.temperature;
}

inline void CBMSParam::SetStateOfCharge(float soc)
{
    m_data.stateOfCharge = soc;
}

inline float CBMSParam::GetStateOfCharge(void)
{
    return m_data.stateOfCharge;
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
    BmsData TestData(stringstream testData);
    bool ValidateDataRange(float value, int minVal, int maxVal);
};

#endif