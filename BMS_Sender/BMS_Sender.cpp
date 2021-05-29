/* ***********************************************************************************************************
* File Name   :	BMS_Sender.cpp
* Author      : Arun Rqaveendran
* Description : BMS_Sender.cpp is used to send the BMS datas like temperature and State of Charging
* Functions	  :
* *********************************************************************************************************** */
#include "BMS_Sender.h"
#include <ctime>

CBMSDataGenerator:: CBMSDataGenerator()
{
    srand((unsigned int)time(NULL));
}

bool CBMSDataGenerator::ValidateDataRange(float value, int minVal, int maxVal)
{
    return((value >= minVal) && (value <= maxVal));
}

int CBMSDataGenerator::RandomNumberGenerator(int min, int max)
{
    return (rand() % ((max - min) + 1)) + min;
}

float CBMSDataGenerator::GenerateStateOfCharge()
{
    return RandomNumberGenerator(MIN_SOC, MAX_SOC);
}

float CBMSDataGenerator::GenerateTemperature()
{
    return RandomNumberGenerator(MIN_TEMPERATURE, MAX_TEMPERATURE);
}

std::stringstream CBMSDataGenerator::GenerateJSON()
{
    stringstream data;

    m_param.SetTemperature(GenerateTemperature());
    m_param.SetStateOfCharge(GenerateStateOfCharge());
    data << "{\"Temperature\": "<< m_param.GetTemperature() << " ,\"SOC\": " << m_param.GetStateOfCharge() <<" }";
    return data;
}

void CBMSDataGenerator::StreamDataToConsole(std::stringstream data)
{
    std::cout << data.str() << endl;
}

BmsData CBMSDataGenerator::TestData(stringstream testData)
{
    BmsData data;
    std::string subString[5];

    for(int iter=0; iter < 5; iter++)
    {
	testData >> subString[iter];
    }
    data.temperature = std::stof(subString[TEMP_JSON_INDEX]);
    data.stateOfCharge = std::stof(subString[SOC_JSON_INDEX]);
    return data; 
}
