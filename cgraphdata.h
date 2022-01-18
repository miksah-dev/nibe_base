#ifndef CGRAPHDATA_H
#define CGRAPHDATA_H

#include <QObject>
#include <QDate>
#include <QTime>


class CGraphData : public QObject
{
    Q_OBJECT
public:
    explicit CGraphData(QObject *parent = nullptr);;

    ~CGraphData();

    void setDate(QDate value);
    void setTime(QTime value);
    void setVersion(int value);
    void setRversion(int value);
    void setTempOut(int value);
    void setCircleWaterIn(int value);
    void setCircleWaterOut(int value);
    void setUseWaterUp(int value);
    void setUseWaterDown(int value);
    void setTempVapor(int value);
    void setbt18(int value);
    void setbt19(int value);
    void setbt20(int value);
    void setTempWaste(int value);
    void setTempIntake(int value);
    void setTempRoom(int value);
    void setElecConsump(int value);
    void setAlarmNro(int value);
    void setCalc_Supply(int value);
    void setBt1Average(int value);
    void setRelayBase(int value);
    void setPriority(int value);

    QDate getDate();
    QTime getTime();
    int getVersion();
    int getRversion();
    float getTempOut();
    float getCircleWaterIn();
    float getCircleWaterOut();
    float getUseWaterUp();
    float getUseWaterDown();
    float getTempVapor();
    float getbt18();
    float getbt19();
    float getBt20();
    float getTempWaste();
    float getTempIntake();
    float getTempRoom();
    float getElecConsump();
    float getAlarmNro();
    float getCalc_Supply();
    float getBt1Average();
    int getRelayBase();
    int getPriority();

signals:

// date, time, version, r_version, temp_out, water_in, water_out, water_down, water_up, temp_vapor, bt18, bt19, bt20, temp_waste, temp_in, temp_room, tot_elec, alarmsnro, calc_supply, bt1_avg, relay_base, prio

private:
    QDate date;
    QTime time;
    int version;
    int rversion;
    float TempOut;
    float CircleWaterIn;
    float CircleWaterOut;
    float UseWaterUp;
    float UseWaterDown;
    float TempVapor;
    float bt18;
    float bt19;
    float bt20;
    float TempWaste;
    float TempIntake;
    float TempRoom;
    float ElecConsump;
    float AlarmNro;
    float Calc_Supply;
    float Bt1Average;
    int RelayBase;
    int Priority;

};

#endif // CGRAPHDATA_H
