#ifndef DATABMSRX_H_
#define DATABMSRX_H_

/* Macro Declaration */
#define ARRINDEXSIZE 1000
#define TEMPERATURE_MAX (float)45.0
#define TEMPERATURE_MIN (float)0.0

#define SOC_MAX (float)80.0
#define SOC_MIN (float)20.0

/* Enum declarations */
typedef enum
{
  OK_STATUS,
  ERROR_STATUS
}retBmsStatus_en;

typedef struct
{
    float y;
    int cntr;
}dataBms_St;
/* Structure declarations */
typedef struct
{
  float batteryTempearature[ARRINDEXSIZE];
  float batterySoc[ARRINDEXSIZE];
  int numOfData;
  int stringSize;
}batteryReading_st;

/* Function declaration */

void updateBmsDataValues(int arrIndx);
int checkNumPoint(char *addrChPtr);
int setDeciPoint(int pointNum);
retBmsStatus_en prepareConvAtoF(char *txBmsReadPtr);
float convertAsciiToFloat(char *txBmsinfoRead);
retBmsStatus_en performBmsRead(char *txBmsReadPtr);
void checkValIsMax(float *maxValue, float maxRange);
void checkValIsMin(float *minValue, float minRange);
retBmsStatus_en RxBmsData(void);
retBmsStatus_en testMain(void);

#endif  /* DATABMSTX_H_ */
