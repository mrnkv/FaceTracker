#include "statistictimes.h"
#include "ui_statistictimes.h"

#include <QCloseEvent>

StatisticTimes::StatisticTimes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticTimes)
{
    ui->setupUi(this);
}

void
StatisticTimes::chageIndication(QString value, Color color){
    QString styleSheet = color == Color::green ? "color:green" : "color:red";
    ui->lcdCurrentTime->setStyleSheet(styleSheet);
    ui->lcdCurrentTime->display(value);
}


StatisticTimes::~StatisticTimes()
{
    delete ui;
}

void StatisticTimes::on_btnSettings_clicked()
{
    emit showSettings();
}

void
StatisticTimes::closeEvent(QCloseEvent *ev){
    hide();
    ev->ignore();
}
