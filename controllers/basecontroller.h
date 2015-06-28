#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "views/trayicon.h"

#include <QObject>

class SetupView;
class StatisticTimes;
class QTimer;
class TrayIcon;
class SysIdleController;
class CameraController;
class TimeCounter;

class BaseController final : public QObject
{
    Q_OBJECT
public:
    explicit BaseController();
    ~BaseController();
    void start();
    void createConnections();
    void startTimers();

signals:
    void quit();
    void sysIdleRequest();
    void changeCurrentTime(QString value, Color color);
    void busySignal(bool busy);
    void changeSysTrayIcon(Color color);
    void setSystemIconToolTip(QString toolTip);

public slots:
    void aboutQuit();
    void sysIdleAnswer(unsigned long duration);
    void cameraFaceAnswer(bool facePresent);
    void trayIconTriggered(Action action);
    void changeCurrentIcon(Color color); //запрос на смену иконки
    void setCurrentWorkingTime(int t);

private:
    //views
    StatisticTimes* m_statisticTimes;
    SetupView* m_setupView;
    TrayIcon *m_trayIcon;

    //Controllers
    SysIdleController *m_sysIdleController;
    CameraController *m_cameraController;
    TimeCounter *m_timeCounter;

    //Timers
    QTimer *m_sysIdleTimer;
    QTimer *m_cameraTimer;

    //Values
    unsigned int m_maxWorkingTime; //sec
    unsigned int m_activeTime; //sec
    bool m_online; //connected to internet server
    bool m_camBusy, m_sysidleBusy;
    unsigned long int m_beginTimeStamp;
};

#endif // BASECONTROLLER_H
