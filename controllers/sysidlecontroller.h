#ifndef SYSIDLECONTROLLER_H
#define SYSIDLECONTROLLER_H

#include <QObject>

class SysIdleController : public QObject
{
    Q_OBJECT
public:
    explicit SysIdleController(QObject *parent = 0);

signals:
    void sysIdleProcessed(unsigned long);

public slots:
    void sysIdleDuration();

private:
    unsigned long m_get_idle();

};

#endif // SYSIDLECONTROLLER_H
