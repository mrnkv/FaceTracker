#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <QObject>
#include "views/trayicon.h"


class TimeCounter : public QObject
{
    Q_OBJECT
enum UserState {busy, free};
enum MachineState {red, green, gray};
static const int MAX_WORKING_TIME = 60;
static const int AWAY_TIME  = 60;
public:
    explicit TimeCounter(QObject *parent = 0);

    void startTimers();

signals:
    void stateChanged(Color color);
    void setCurrentWorkingTime(int time);

public slots:
    void userStateBusy(bool state);
    void setMaxWorkingTime(unsigned int t);
private slots:
    void m_count();

private:
    void m_createConnectionsTrans();
    QTimer *m_countTimer;
    unsigned long int m_timeStamp;
    unsigned int m_maxWorkingTime;
    unsigned int m_currentTime;
    unsigned int m_currentFreeTime;
    UserState m_userState;
    MachineState m_machineState;

};

#endif // TIMECOUNTER_H
