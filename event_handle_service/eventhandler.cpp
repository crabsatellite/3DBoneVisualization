//**********************************************************************
// Header includes
//**********************************************************************
#include <QPoint>
#include <math.h>
#include "eventhandler.h"
#include "render_service/camera.h"

//**********************************************************************
// Function definitions
//**********************************************************************
EventHandleService::EventHandler::EventHandler(QObject *parent) : QObject(parent)
{

}

void EventHandleService::EventHandler::onStartMouseClickEvent(QMouseEvent *event)
{
    QPoint curMouseClickPos = event->pos();
    lastMouseClickPosX = curMouseClickPos.x();
    lastMouseClickPosY = curMouseClickPos.y();
    startMouseClickEvent = true;
}

void EventHandleService::EventHandler::onStopMouseClickEvent(QMouseEvent *event)
{
    QPoint curMouseClickPos = event->pos();
    lastMouseClickPosX = curMouseClickPos.x();
    lastMouseClickPosY = curMouseClickPos.y();
    startMouseClickEvent = false;
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

void EventHandleService::EventHandler::onProcessMouseClickEvent(QMouseEvent *event)
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    if ( startMouseClickEvent ) {
        QPoint curMouseClickPos = event->pos();
        yawAngle -= qDegreesToRadians((curMouseClickPos.x() - lastMouseClickPosX) * 0.015);
        pitchAngle += qDegreesToRadians((curMouseClickPos.y() - lastMouseClickPosY) * 0.015);
        if ( pitchAngle < -(float)M_PI / 2.0f + 0.1f ) {
            pitchAngle = -(float)M_PI / 2.0f + 0.1f;
        } else if ( pitchAngle > (float)M_PI / 2.0f - 0.1f) {
            pitchAngle = (float)M_PI / 2.0f - 0.1f;
        }
        rotateByEulerAngle();
        lastMouseClickPosX = curMouseClickPos.x();
        lastMouseClickPosX = curMouseClickPos.y();
    }
}
