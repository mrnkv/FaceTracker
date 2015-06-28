#include "setupview.h"
#include "ui_setupview.h"

#include <QTimer>
#include <QImage>
#include <QCloseEvent>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

SetupView::SetupView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupView)
{
    ui->setupUi(this);
    ui->lblCamStream->setEnabled(false);
    ui->lblFaceObjSize->setEnabled(false);
    ui->sldrMinSize->setEnabled(false);
    ui->sldrMaxSize->setEnabled(false);
    ui->lblTo->setEnabled(false);
    ui->lblPicture->setEnabled(false);
}

SetupView::~SetupView()
{
    delete ui;
}


void
SetupView::on_spnMaxWorkingPeriod_valueChanged(int arg1)
{
    emit changeMaxWorkingTime(arg1 * 60); // т.к. мы работаем с секундами
}

void
SetupView::on_checkBox_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Unchecked:
        ui->lblCamStream->setEnabled(false);
        ui->lblFaceObjSize->setEnabled(false);
        ui->sldrMinSize->setEnabled(false);
        ui->sldrMaxSize->setEnabled(false);
        ui->lblTo->setEnabled(false);
        ui->lblPicture->setEnabled(false);
        ui->lblPicture->setText(tr("Video output"));
        m_videoTimer.stop();
        emit changeCheckCamera(Qt::Unchecked);
        break;
    case Qt::Checked:
        ui->lblCamStream->setEnabled(true);
        ui->lblFaceObjSize->setEnabled(true);
        ui->sldrMinSize->setEnabled(true);
        ui->sldrMaxSize->setEnabled(true);
        ui->lblTo->setEnabled(true);
        ui->lblPicture->setEnabled(true);
        if(initCamera()){
            ui->lblPicture->setText(tr("We have a camera."));
            showCameraOutput();
            emit changeCheckCamera(Qt::Checked);
        }else{
            ui->lblPicture->setText(tr("We havn't camera"));
        }

        break;
    default:
        break;
    }
}

void
SetupView::on_sldrMinSize_valueChanged(int value)
{
    ui->sldrMinSize->setToolTip(QString("%1").arg(value));
    emit changeMinMaxFaceSize(ui->sldrMinSize->value(),
                              ui->sldrMaxSize->value());
}

void
SetupView::on_sldrMinSize_sliderMoved(int position)
{
    ui->sldrMinSize->setToolTip(QString("%1").arg(position));
}
void SetupView::on_sldrMaxSize_valueChanged(int value)
{
    ui->sldrMaxSize->setToolTip(QString("%1").arg(value));
    emit changeMinMaxFaceSize(ui->sldrMinSize->value(),
                              ui->sldrMaxSize->value());

}

void SetupView::on_sldrMaxSize_sliderMoved(int position)
{
    ui->sldrMaxSize->setToolTip(QString("%1").arg(position));
}

bool
SetupView::initCamera(){
    cv::VideoCapture cap(0); // open the default camera
    cap.open(0);
    if (cap.isOpened())
    {
        cap.release();
        return true;
    }
    else
        return false;
}

void
SetupView::showCameraOutput(){
    connect(&m_videoTimer, &QTimer::timeout, [this](){
        if(!this->isVisible()) return;
        cv::Mat image;
        cv::VideoCapture cap(0); // open the default camera
        if(!cap.isOpened()) {
            return;
        }
        cap >> image;
        cap.release();
        int cx = image.cols/2;
        int cy = image.rows/2;
        int w_min = image.cols*ui->sldrMinSize->value()/100;
        int w_max = image.cols*ui->sldrMaxSize->value()/100;
        qDebug() << "WMIN = " << w_min << " WMAX = " << w_max;
        cv::rectangle(image,
                      cv::Point(cx-w_min/2, cy-w_min/2),
                      cv::Point(cx+w_min/2, cy+w_min/2),
                      cv::Scalar(0, 255,255));
        cv::rectangle(image,
                      cv::Point(cx-w_max/2, cy-w_max/2),
                      cv::Point(cx+w_max/2, cy+w_max/2),
                      cv::Scalar(0, 0, 255));
        cv::cvtColor(image,image,CV_BGR2RGB);
        QImage img= QImage((const unsigned char*)(image.data),
            image.cols,image.rows,QImage::Format_RGB888);
        ui->lblPicture->setPixmap(QPixmap::fromImage(img));
    });
    m_videoTimer.start(3000); // 1 раз в 3 секундs показывать изображение во фрейме
}

