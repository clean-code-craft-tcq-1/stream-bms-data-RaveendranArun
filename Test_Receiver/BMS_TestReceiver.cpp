#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Test_Sender/catch.hpp"
#include "BMS_Receiver/dataBmsRx.h"

TEST_CASE(" Test case to check if data is read from sender to Reciever is success ") 
{
 REQUIRE(RxBmsData() == OK_STATUS);
}
