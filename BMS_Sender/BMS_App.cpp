#include <chrono>
#include <thread>

#include "BMS_Sender.h"

int main()
{
    CBMSDataGenerator* pBMSDataGen = new CBMSDataGenerator;
    while (1)
    {
        pBMSDataGen->StreamDataToConsole(pBMSDataGen->GenerateJSON());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));;
    }
}