#ifndef CAMERA_H
#define CAMERA_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>

namespace RenderService {

//**********************************************************************
// Class declaration
//**********************************************************************
class Camera : public QObject
{
    Q_OBJECT
public:
//**********************************************************************
// Constructors & destructors
//**********************************************************************
    explicit Camera(QObject *parent = nullptr);
    Camera(const QVector3D& cameraPos, const QVector3D& viewCenter, float radius);
    ~Camera() = default;

public:
//**********************************************************************
// Public methods
//**********************************************************************
    QVector3D getViewCenter() const { return viewCenter; }
    void setViewCenter(const QVector3D& viewCenter) { this->viewCenter = viewCenter; }

    void setRadius(float radius) { this->radius = radius; }
    float getRadius() const { return radius; }

    void setCameraPosition(const QVector3D& cameraPos) { this->cameraPos = cameraPos; }
    QVector3D getCameraPosition() const { return cameraPos; }

    void setFOV(int fov) { this->fov = fov; }
    int getFOV() const { return fov; }

    // Convert target object from world space to camera space
    QMatrix4x4 getViewMatrix() const;

    // Convert target object from camera space to clip space
    QMatrix4x4 getClipMatrix(float ratio) const;

    // Sync the camera properties each time when a user event is consumed
    void syncCameraOrientation();

private:
    QVector3D cameraPos; // Position of camera
    QVector3D viewCenter; // Position of target object center
    QVector3D upDirection; // Y axis of camera coordinate space
    QVector3D rightDirection; // X axis of camera coordinate space
    QVector3D viewDirection; // Z axis of camera coordinate space
    float radius; // Distance between camera and target object center
    int fov = 45; // Field of view, related to zoom effect
};

}
#endif // CAMERA_H
