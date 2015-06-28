#ifndef SETUPVIEW_H
#define SETUPVIEW_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QTimer>

namespace Ui {
class SetupView;
}

class SetupView : public QWidget
{
    Q_OBJECT
public:
    explicit SetupView(QWidget *parent = 0);
    ~SetupView();
signals:
    void changeMaxWorkingTime(unsigned int t);
    void changeMinMaxFaceSize(unsigned int min, unsigned int max);
    void changeCheckCamera(Qt::CheckState ch);
private slots:
    void on_spnMaxWorkingPeriod_valueChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_sldrMinSize_valueChanged(int value);
    void on_sldrMinSize_sliderMoved(int position);
    void on_sldrMaxSize_valueChanged(int value);
    void on_sldrMaxSize_sliderMoved(int position);

private:
    Ui::SetupView *ui;
    bool initCamera();
    void showCameraOutput();
    QTimer m_videoTimer;
};

#endif // SETUPVIEW_H
