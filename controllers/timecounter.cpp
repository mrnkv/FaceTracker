#include "timecounter.h"

#include <QTimer>
#include <QDebug>
#include <QDateTime>

TimeCounter::TimeCounter(QObject *parent) :
    QObject(parent),
    m_timeStamp(0),
    m_maxWorkingTime(MAX_WORKING_TIME),// 1/3 min
    m_currentTime(0),
    m_currentFreeTime(0)

{
    m_machineState = gray;
    m_timeStamp = QDateTime::currentDateTime().toTime_t();
    m_countTimer = new QTimer(this);
    connect(m_countTimer, SIGNAL(timeout()),
            this, SLOT(m_count()));
}
void
TimeCounter::setMaxWorkingTime(unsigned int t){
    m_maxWorkingTime = t;
}

void
TimeCounter::userStateBusy(bool state){
    qDebug() << QTime().currentTime().toString() << "state = " << state;

    m_userState = state ? busy:free;
}

void
TimeCounter::m_createConnectionsTrans(){
    connect(m_countTimer, SIGNAL(timeout()),
            this, SLOT(m_count()));
}

void
TimeCounter::startTimers(){
    emit stateChanged(Color::gray);
    m_countTimer->start(1000);
}

void
TimeCounter::m_count(){
    qDebug() << "Count " << m_currentTime << m_currentFreeTime;
    switch (m_machineState) {
    case red:
        qDebug() << QTime().currentTime().toString() << "red";
        switch (m_userState) {
        case free:
            m_currentFreeTime++;
            if (m_currentFreeTime >= AWAY_TIME){// минута прошла
                m_currentFreeTime = 0;
                m_timeStamp = QDateTime::currentDateTime().toTime_t();
                //переслать данные об активном периоде
                qDebug() << "Sending active period data "<< m_timeStamp << m_currentTime << m_maxWorkingTime;
                m_currentTime = 0;
                //перейти в состояние серый
                m_machineState = gray;
                emit stateChanged(Color::gray);
            }
            break;
        case busy:
            m_currentTime = m_currentFreeTime > 0 ? m_currentTime + m_currentFreeTime : m_currentTime + 1;
            m_currentFreeTime = 0;
            if(m_currentTime < m_maxWorkingTime){
                m_machineState = green;
                emit stateChanged(Color::green);
            }
            break;
        default:
            break;
        }
        break;
    case gray:
        qDebug() << QTime().currentTime().toString() << "gray";
        switch (m_userState) {
        case free:
            //ничего не надо делать
            break;
        case busy:
            m_currentTime = 1;
            //получить еаймстамп для нового периода
            m_timeStamp = QDateTime::currentDateTime().toTime_t();
            //перейти в зеленое состояние
            m_machineState = green;
            emit stateChanged(Color::green);
            break;
        default:
            break;
        }
        break;
    case green:
        qDebug() << QTime().currentTime().toString() << "green";
        switch (m_userState) {
        case free:
            m_currentFreeTime++;
            if (m_currentFreeTime >= AWAY_TIME){// минута прошла
                m_currentFreeTime = 0;
                //переслать данные об активном периоде
                qDebug() << "Sending active period data " << m_timeStamp << m_currentTime << m_maxWorkingTime;
                //
                //перейти в состояние серый
                m_machineState = gray;
                emit stateChanged(Color::gray);
            }
        break;
        case busy:
            m_currentTime = m_currentFreeTime > 0 ? m_currentTime + m_currentFreeTime : m_currentTime + 1;
            m_currentFreeTime = 0;
            if(m_currentTime > m_maxWorkingTime){
                //перейти в состояние красный
                m_machineState = red;
                emit stateChanged(Color::red);
            }
        break;
        default:
        break;
        }
    default:
    break;
    }
    emit setCurrentWorkingTime(m_maxWorkingTime - m_currentTime );
}
