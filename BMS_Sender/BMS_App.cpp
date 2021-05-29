#include <chrono>
#include <thread>

#include "BMS_Sender.h"

int main()
{
    CBMSDataGenerator* pBMSDataGen = new CBMSDataGenerator;
    for (int i = 0; i < 10; ++i)
    {
        pBMSDataGen->StreamDataToConsole(pBMSDataGen->GenerateJSON());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));;
    }
}