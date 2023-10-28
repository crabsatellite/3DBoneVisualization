//**********************************************************************
// Header includes
//**********************************************************************
#include "camera.h"
#include <QtMath>
#include <math.h>

//**********************************************************************
// Constants
//**********************************************************************

// TODO: need to make them configurable
namespace {

const float NEAR_PLANE = 0.1;
const float FAR_PLANE = 100;
const int FOV = 45;

}

//**********************************************************************
// Function definitions
//**********************************************************************
RenderService::Camera::Camera(QObject *parent) : QObject(parent),
    cameraPos(QVector3D(0.0f, 0.0f, 0.0f)),
    viewCenter(QVector3D(0.0f, 0.0f, 0.0f)),
    upDirection(QVector3D(0.0f, 1.0f, 0.0f)),
    viewDirection(QVector3D(0.0f, 0.0f, -1.0f)),
    rightDirection(QVector3D(1.0f, 0.0f, 0.0f))
{
    syncCameraOrientation();
}

RenderService::Camera::Camera(const QVector3D &cameraPos, const QVector3D &viewCenter, float radius):
    cameraPos(cameraPos),
    viewCenter(viewCenter),
    radius(radius)
{
    syncCameraOrientation();
}

QMatrix4x4 RenderService::Camera::getClipMatrix(float ratio) const
{
    QMatrix4x4 clipMatrix;
    clipMatrix.perspective(FOV, ratio, NEAR_PLANE, FAR_PLANE);
    return clipMatrix;
}

QMatrix4x4 RenderService::Camera::getViewMatrix() const
{
    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(cameraPos, viewCenter, upDirection);
    return viewMatrix;
}

void RenderService::Camera::syncCameraOrientation()
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    viewDirection = viewCenter - cameraPos;
    viewDirection.normalize();
    rightDirection = QVector3D::crossProduct(viewDirection, QVector3D(0.0f, 1.0f, 0.0f));
    rightDirection.normalize();
    upDirection = QVector3D::crossProduct(rightDirection, viewDirection);
    upDirection.normalize();
}

