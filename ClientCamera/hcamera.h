#ifndef HCAMERA_H
#define HCAMERA_H

#include <QObject>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>


class HCamera : public QObject
{
    Q_OBJECT
public:
    explicit HCamera(QObject *parent = 0);
    ~HCamera();

    void captureImage(QString filename);
    void openCamera(QString cameraname);
    void closeCamera();
    bool isOpenCamera();

public slots:
    void imageCaptured(int id, const QImage &image);

signals:
    void cameraCaptured();

private:
    QString imageFile;
    QCamera *camera;
    QCameraImageCapture *capturer;
};

#endif // HCAMERA_H
