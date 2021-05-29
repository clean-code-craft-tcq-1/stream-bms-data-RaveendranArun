#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "../BMS_Sender/BMS_Sender.h"
#include "catch.hpp"

TEST_CASE("Data generation test") {

	CBMSDataGenerator* pBmsObj = new CBMSDataGenerator;
    BmsData data;
	for (int iter = 0; iter < 50; iter++) 
	{
		data = pBmsObj->TestData(pBmsObj->GenerateJSON());
		REQUIRE(pBmsObj->ValidateDataRange(data.stateOfCharge, MIN_SOC, MAX_SOC));
		REQUIRE(pBmsObj->ValidateDataRange(data.temperature, MIN_TEMPERATURE, MAX_TEMPERATURE));
	}
}