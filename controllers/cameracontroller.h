#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
namespace cv {
class Mat;
}

class QPixmap;

class CameraController : public QObject
{
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = 0);
signals:
    void imageProcessed(bool facePresent);
public slots:
    void procCamInput();
    void setMinMaxFaceSizes(unsigned int min, unsigned int max);
    void setCheckCamera(Qt::CheckState ch);
private:
    bool m_cameraInit();
    bool m_hasFaceOnPicture(cv::Mat *picture);
    unsigned int m_minFaceSize, m_maxFaceSize; //в процентах
    Qt::CheckState m_checkCamera;
};

#endif // CAMERACONTROLLER_H
