#include "cgraphdata.h"

CGraphData::CGraphData(QObject *parent)
    : QObject{parent}
{

}

CGraphData::~CGraphData()
{

}

void CGraphData::setDate(QDate value)
{
    date = value;
}

void CGraphData::setTime(QTime value)
{
    time = value;
}
void CGraphData::setVersion(int value)
{
    version = value;
}

void CGraphData::setRversion(int value)
{
    rversion = value;
}

void CGraphData::setTempOut(int value)
{
    TempOut = (float)value/10;
}

void CGraphData::setCircleWaterIn(int value)
{
    CircleWaterIn = (float)value/10;
}

void CGraphData::setCircleWaterOut(int value)
{
    CircleWaterOut = (float)value/10;
}
void CGraphData::setUseWaterUp(int value)
{
    UseWaterUp = (float)value/10;
}

void CGraphData::setUseWaterDown(int value)
{
    UseWaterDown = (float)value/10;
}

void CGraphData::setTempVapor(int value)
{
    TempVapor = (float)value/10;
}

void CGraphData::setbt18(int value)
{
    bt18 = (float)value/10;
}

void CGraphData::setbt19(int value)
{
    bt19 = (float)value/10;
}

void CGraphData::setbt20(int value)
{
    bt20 = (float)value/10;
}

void CGraphData::setTempWaste(int value)
{
    TempWaste = (float)value/10;
}
void CGraphData::setTempIntake(int value)
{
    TempIntake = (float)value/10;
}

void CGraphData::setTempRoom(int value)
{
    TempRoom = (float)value/10;
}

void CGraphData::setElecConsump(int value)
{
    ElecConsump = (float)value/100;
}

void CGraphData::setAlarmNro(int value)
{
    AlarmNro = value;
}

void CGraphData::setCalc_Supply(int value)
{
    Calc_Supply = (float)value/10;
}

void CGraphData::setBt1Average(int value)
{
    Bt1Average = (float)value/10;
}

void CGraphData::setRelayBase(int value)
{
    RelayBase = value;
}

void CGraphData::setPriority(int value)
{
    Priority = value;
}

QDate CGraphData::getDate()
{
    return date;
}

QTime CGraphData::getTime()
{
    return time;
}

int CGraphData::getVersion()
{
    return version;
}

int CGraphData::getRversion()
{
    return rversion;
}

float CGraphData::getTempOut()
{
    return TempOut;
}

float CGraphData::getCircleWaterIn()
{
    return CircleWaterIn;
}

float CGraphData::getCircleWaterOut()
{
    return CircleWaterOut;
}

float CGraphData::getUseWaterUp()
{
    return UseWaterUp;
}

float CGraphData::getUseWaterDown()
{
    return UseWaterDown;
}

float CGraphData::getTempVapor()
{
    return TempVapor;
}

float CGraphData::getbt18()
{
    return bt18;
}

float CGraphData::getbt19()
{
    return bt19;
}

float CGraphData::getBt20()
{
    return bt20;
}

float CGraphData::getTempWaste()
{
    return TempWaste;
}

float CGraphData::getTempIntake()
{
    return TempIntake;
}

float CGraphData::getTempRoom()
{
    return TempRoom;
}

float CGraphData::getElecConsump()
{
    return ElecConsump;
}

float CGraphData::getAlarmNro()
{
    return AlarmNro;
}

float CGraphData::getCalc_Supply()
{
    return Calc_Supply;
}

float CGraphData::getBt1Average()
{
    return Bt1Average;
}

int CGraphData::getRelayBase()
{
    return RelayBase;
}

int CGraphData::getPriority()
{
    return Priority;
}
