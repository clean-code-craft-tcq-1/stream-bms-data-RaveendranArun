#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "dataBmsRx.h"

/* global variable declaration */
batteryReading_st bmsTempSocData;
dataBms_St inputSt;

/*
 **********************************************************************************************************************
 * Service name         : performBmsRead
 * Syntax               : retBmsStatus_en performBmsRead(char *)
 * param[in]            : txBmsReadPtr
 * return               : None
 * Description          : Program to perform BMS read
 **********************************************************************************************************************
 */
retBmsStatus_en performBmsRead(char *txBmsReadPtr)
{
	retBmsStatus_en retStatus = ERROR_STATUS;
	/* check if pointer is valid */
	if(txBmsReadPtr!=NULL)
	{
		scanf("%s",txBmsReadPtr);
		retStatus = OK_STATUS;
	}
	return retStatus;
}

/*
 **********************************************************************************************************************
 * Service name         : prepareConvAtoF
 * Syntax               : retBmsStatus_en prepareConvAtoF(char *)
 * param[in]            : txBmsReadPtr
 * return               : None
 * Description          : Program to prepare data for asci to float conversion
 **********************************************************************************************************************
 */
retBmsStatus_en prepareConvAtoF(char *txBmsReadPtr)
{
	retBmsStatus_en retStatus = ERROR_STATUS;
	int lengthOfString = 0x00;
	int loopCntr = 0;
	int cntrval = 0;
	lengthOfString = strlen(txBmsReadPtr);
	/* add new line and null to the end if string */
    txBmsReadPtr[lengthOfString] = '\n';
    txBmsReadPtr[lengthOfString + 1] = '\0';
	bmsTempSocData.stringSize = lengthOfString;
    for(loopCntr = 0;txBmsReadPtr[loopCntr]!='\0';loopCntr++)
    {
    if((((txBmsReadPtr[loopCntr]>='0')&&(txBmsReadPtr[loopCntr]<='9'))||(txBmsReadPtr[loopCntr] == '.')))
    {
       inputSt.y = convertAsciiToFloat(&txBmsReadPtr[loopCntr]);
       loopCntr += inputSt.cntr;
       inputSt.cntr=0;
	   updateBmsDataValues(cntrval);
	   cntrval++;
    }
	retStatus = OK_STATUS;
    }
	return retStatus;
}

/*
 **********************************************************************************************************************
 * Service name         : convertAsciiToFloat
 * Syntax               : float convertAsciiToFloat(char *)
 * param[in]            : addrChPtr
 * return               : None
 * Description          : Program to convert ascii to float
 **********************************************************************************************************************
 */
float convertAsciiToFloat(char *txBmsinfoRead)
{
  int loopCntr = 0;
  int num = 0, num2 = 0, point_ch = 0, x = 0, decPointNum = 1; 
  float f2 = 0.00, f3 = 0.00;

  point_ch = checkNumPoint(&txBmsinfoRead[loopCntr]);
	
  for (; ((txBmsinfoRead[loopCntr] !=' ')&&(txBmsinfoRead[loopCntr] !='\n')); loopCntr++) 
  {
    if (loopCntr < point_ch)
    {
        num = num * 10 + (txBmsinfoRead[loopCntr] - 48);
    }
    else if (loopCntr == point_ch) 
    /* do nothing */;
    else
    {
      num2 = num2 * 10 + (txBmsinfoRead[loopCntr] - 48);
      ++x;
    }
    inputSt.cntr = loopCntr;
  }
  
  /* it takes 10 if it has 1 digit ,100 if it has 2 digits in mantissa*/
    decPointNum = setDeciPoint(x);
  f2 = num2 / (float) decPointNum;
  printf("f2=%f\n",f2);
  f3 = num + f2;
  return f3;	
}

/*
 **********************************************************************************************************************
 * Service name         : checkNumPoint
 * Syntax               : int checkNumPoint(char *)
 * param[in]            : addrChPtr
 * return               : None
 * Description          : Program to check at what place the decimal point occurs from the provided input data
 **********************************************************************************************************************
 */
int checkNumPoint(char *addrChPtr)
{
	int loopCntr = 0;
	int pnt_ch = 0;
	for (; addrChPtr[loopCntr]; loopCntr++)
    if (addrChPtr[loopCntr] == '.') 
	{
      pnt_ch = loopCntr;
      break;
    }
	return pnt_ch;
}

/*
 **********************************************************************************************************************
 * Service name         : setDeciPoint
 * Syntax               : int setDeciPoint(int)
 * param[in]            : pointNum
 * return               : None
 * Description          : Program to set the decimal point based on number of digits
 **********************************************************************************************************************
 */
int setDeciPoint(int pointNum)
{
  int loopCntr = 0;
  int decPntNum = 1; 
  /* it takes 10 if it has 1 digit ,100 if it has 2 digits in mantissa*/
  for (loopCntr = 1; loopCntr <= pointNum; loopCntr++) 
    decPntNum = decPntNum * 10;
  return decPntNum;
}

/*
 **********************************************************************************************************************
 * Service name         : updateBmsDataValues
 * Syntax               : void updateBmsDataValues(int)
 * param[in]            : arrIndx
 * return               : None
 * Description          : Program to check and fetch either BMS Soc or temperature data
 **********************************************************************************************************************
 */
void updateBmsDataValues(int arrIndx)
{
	/* conditional check to update and print either BMS temparature data or Soc data */
	if((arrIndx&1)!=1)
	{
		bmsTempSocData.batteryTempearature[bmsTempSocData.numOfData] = inputSt.y;
		printf("%f/t",bmsTempSocData.batteryTempearature[bmsTempSocData.numOfData]);
	}
	else
	{
		bmsTempSocData.batterySoc[bmsTempSocData.numOfData] = inputSt.y;
		printf("%f/n",bmsTempSocData.batterySoc[bmsTempSocData.numOfData]);
		bmsTempSocData.numOfData+=1;
	}
}

/*
 **********************************************************************************************************************
 * Service name         : RxBmsData
 * Syntax               : retBmsStatus_en RxBmsData(void)
 * param[in]            : None
 * return               : None
 * Description          : Program to Read from console or sender to update the txBmsDataRead bufffer
 **********************************************************************************************************************
 */
retBmsStatus_en RxBmsData()
{
	retBmsStatus_en retStatus = ERROR_STATUS;
	char txBmsDataRead[100];
	/* perform Read from console or sender to update the txBmsDataRead bufffer */
	retStatus = performBmsRead(txBmsDataRead);
	/* convert BMS data of Sender from ascii to float for comparison if success status is OK */
	if(retStatus != ERROR_STATUS)
	{
		retStatus = prepareConvAtoF(txBmsDataRead);
	}
	
	return retStatus;
}

/*
 **********************************************************************************************************************
 * Service name         : checkValIsMax
 * Syntax               : void checkValIsMax(float *, float)
 * param[in]            : maxValue
 * return               : maxRange
 * Description          : Program to check and print if the BMS maximum value or range is breached
 **********************************************************************************************************************
 */
void checkValIsMax(float *maxValue, float maxRange)
{
	for(  int loopCntr = 0;loopCntr<(bmsTempSocData.numOfData);loopCntr++)
	{
		if(maxValue[loopCntr] >= maxRange)
		{
			printf("Max range of %f is breached by %f\n",maxRange,maxValue[loopCntr]);
		}
	}
}

/*
 **********************************************************************************************************************
 * Service name         : checkValIsMin
 * Syntax               : void checkValIsMin(float *, float)
 * param[in]            : minValue
 * return               : minRange
 * Description          : Program to check and print if the BMS minimum value or range is breached
 **********************************************************************************************************************
 */
void checkValIsMin(float *minValue, float minRange)
{
	for(  int loopCntr = 0;loopCntr<(bmsTempSocData.numOfData);loopCntr++)
	{
		if(minValue[loopCntr]<=minRange)
		{
			printf("Min range of %f breached by %f\n",minRange,minValue[loopCntr]);
		}
	}
}

/*
 **********************************************************************************************************************
 * Service name         : testMain
 * Syntax               : retBmsStatus_en testMain(void)
 * param[in]            : none
 * return               : none
 * Description          : Program to check and print if recieved BMS data is max or min range
 **********************************************************************************************************************
 */
retBmsStatus_en testMain()
{
	retBmsStatus_en retStatus = ERROR_STATUS;
	retStatus = RxBmsData();
	checkValIsMax(&bmsTempSocData.batteryTempearature[0], TEMPERATURE_MAX);
	checkValIsMax(&bmsTempSocData.batterySoc[0], SOC_MAX);
	checkValIsMin(&bmsTempSocData.batteryTempearature[0], TEMPERATURE_MIN);
	checkValIsMin(&bmsTempSocData.batterySoc[0], SOC_MIN);
	return retStatus;
}
