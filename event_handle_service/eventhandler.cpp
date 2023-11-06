//**********************************************************************
// Header includes
//**********************************************************************
#include <QPoint>
#include <math.h>
#include <QDebug>
#include "eventhandler.h"
#include "render_service/camera.h"

//**********************************************************************
// Function definitions
//**********************************************************************
EventHandleService::EventHandler::EventHandler(QObject *parent) : QObject(parent)
{

}

void EventHandleService::EventHandler::onStartMouseClickEvent(float mouseClickPosX, float mouseClickPosY)
{
    lastMouseClickPosX = mouseClickPosX;
    lastMouseClickPosY = mouseClickPosY;
    startMouseClickEvent = true;
}

void EventHandleService::EventHandler::onStopMouseClickEvent(float mouseClickPosX, float mouseClickPosY)
{
    lastMouseClickPosX = mouseClickPosX;
    lastMouseClickPosY = mouseClickPosY;
    startMouseClickEvent = false;
}

void EventHandleService::EventHandler::onMouseWheelEvent(int delta)
{
    int fov = camera->getFOV() - delta;
    fov = std::max(std::min(fov, 99), 0);
    camera->setFOV(fov);
    qDebug() << "FOV is: " << fov;
}

void EventHandleService::EventHandler::setCamera(RenderService::Camera *camera)
{
    this->camera = camera;
}

void EventHandleService::EventHandler::rotateByEulerAngle()
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    if ( !camera ) {
        return;
    }

    QVector3D cameraPos;
    const QVector3D viewCenter = camera->getViewCenter();
    const float radius = camera->getRadius();

    cameraPos.setX(viewCenter.x() + radius * cosf(pitchAngle) * sinf(yawAngle));
    cameraPos.setY(viewCenter.y() + radius * sinf(pitchAngle));
    cameraPos.setZ(viewCenter.z() + radius * cosf(pitchAngle) * cosf(yawAngle));

    camera->setCameraPosition(cameraPos);
}

void EventHandleService::EventHandler::onProcessMouseClickEvent(float mouseClickPosX, float mouseClickPosY, float sensitivity)
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    if ( startMouseClickEvent ) {
        yawAngle -= qDegreesToRadians((mouseClickPosX - lastMouseClickPosX) * sensitivity);
        pitchAngle += qDegreesToRadians((mouseClickPosY - lastMouseClickPosY) * sensitivity);
        if ( pitchAngle < -(float)M_PI / 2.0f + 0.1f ) {
            pitchAngle = -(float)M_PI / 2.0f + 0.1f;
        } else if ( pitchAngle > (float)M_PI / 2.0f - 0.1f) {
            pitchAngle = (float)M_PI / 2.0f - 0.1f;
        }
        rotateByEulerAngle();
        lastMouseClickPosX = mouseClickPosX;
        lastMouseClickPosY = mouseClickPosY;
    }
}
