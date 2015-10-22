#ifndef FILTER_ONE_H
#define FILTER_ONE_H
#include<QWidget>

class Filter_One
{
public:
    Filter_One();
    float LOFF [6],HIFF [6];
    unsigned char L_nStatus,H_nStatus;

    void  LowFilter(int8_t *pTempData);
    void  HigtFilter(int8_t *pTempData);
    void  Notch_50Hz(int8_t *dData);

};

#endif // FILTER_ONE_H
