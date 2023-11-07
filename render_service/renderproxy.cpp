//**********************************************************************
// Header includes
//**********************************************************************
#include "renderproxy.h"
#include "camera.h"
#include "event_handle_service/eventhandler.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QtMath>

// TODO: need to avoid hardcode here
namespace {

const float RADIUS = 2.0f;
const QVector3D VIEW_CENTER = QVector3D(0.0f, 0.0f, 0.0f);
const QVector3D CAMERA_POSITION = QVector3D(0.0f, 0.0f, 2.0f);
const float SLIDER_ROTATION_SENSITIVITY = 1.1;
const float SLIDER_PAN_SENSITIVITY = 0.01;
const float MOUSE_ROTATION_SENSITIVITY = 0.1;

float vertices[] = {

    // front face
    -0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,

    // back face
    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,

    // left face
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,

    // right face
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,

    // top face
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    // bottom face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
};
}

//**********************************************************************
// Function definitions
//**********************************************************************
RenderService::RenderProxy::RenderProxy(QWidget *parent) : QOpenGLWidget(parent)
{
    camera.reset(new RenderService::Camera(CAMERA_POSITION, VIEW_CENTER, RADIUS));
    eventHandler.reset(new EventHandleService::EventHandler());
    eventHandler->setCamera(camera.data());
}

RenderService::RenderProxy::~RenderProxy()
{
    makeCurrent();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    doneCurrent();
}

void RenderService::RenderProxy::initializeGL()
{
    initializeOpenGLFunctions();
    bindVertexData();
    compileShaders();
    glEnable(GL_DEPTH_TEST);
}

void RenderService::RenderProxy::resizeGL(int w, int h)
{
}

void RenderService::RenderProxy::paintGL()
{
    QMatrix4x4 modelMatrix;
    QMatrix4x4 viewMatrix = camera->getViewMatrix();
    QMatrix4x4 clipMatrix = camera->getClipMatrix((float)width() / height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProrgam.bind();
    glBindVertexArray(VAO);

    shaderProrgam.setUniformValue("modelMatrix", modelMatrix);
    shaderProrgam.setUniformValue("viewMatrix", viewMatrix);
    shaderProrgam.setUniformValue("clipMatrix", clipMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void RenderService::RenderProxy::mousePressEvent(QMouseEvent *event)
{
    QPoint curMouseClickPos = event->pos();
    eventHandler->onStartRotationEvent(curMouseClickPos.x(), curMouseClickPos.y());
}

void RenderService::RenderProxy::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint curMouseClickPos = event->pos();
    eventHandler->onStopRotationEvent(curMouseClickPos.x(), curMouseClickPos.y());
}

void RenderService::RenderProxy::mouseMoveEvent(QMouseEvent *event)
{
    if ( eventHandler->isStartRotationEvent() ) {
        QPoint curMouseClickPos = event->pos();
        eventHandler->onProcessRotationEvent(curMouseClickPos.x(), curMouseClickPos.y(), MOUSE_ROTATION_SENSITIVITY);
        camera->syncCameraOrientation();
        update();
    }
}

void RenderService::RenderProxy::wheelEvent(QWheelEvent *event)
{
    eventHandler->onProcessZoomEvent(event->delta() * 0.01);
    update();
}

void RenderService::RenderProxy::bindVertexData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Submit vertices data to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    // TODO: Add texture coordinate attribute
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderService::RenderProxy::compileShaders()
{
    bool success = true;
    success &= shaderProrgam.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/render_service/vertex_shader.vsh");
    if ( !success ) {
        qDebug() << "Vertex shader compile error: " << shaderProrgam.log();
    }
    success &= shaderProrgam.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/render_service/fragment_shader.fsh");
    if ( !success ) {
        qDebug() << "Fragment shader compile error: " << shaderProrgam.log();
    }
    success &= shaderProrgam.link();
    if ( !success ) {
        qDebug() << "Shader program link error: " << shaderProrgam.log();
    }
}

void RenderService::RenderProxy::onSliderMouseEvent(Slider::Action sliderAction, Mouse::Action mouseAction, Slider::Axis sliderAxis, int position)
{
    int pitchPos = sliderAction == Slider::Action::ROTATE && sliderAxis == Slider::Axis::X ? position : 0;
    int yawPos = sliderAction == Slider::Action::ROTATE && sliderAxis == Slider::Axis::Y ? position : 0;

    int horizontalPos = sliderAction == Slider::Action::MOVE && sliderAxis == Slider::Axis::X ? position : INT_MAX;
    int verticalPos = sliderAction == Slider::Action::MOVE && sliderAxis == Slider::Axis::Y ? position : INT_MAX;

    switch (sliderAction) {
        case Slider::Action::ROTATE :
            switch (mouseAction) {
                case Mouse::Action::PRESSED :
                    eventHandler->onStartRotationEvent(yawPos, pitchPos);
                    break;
                case Mouse::Action::MOVED :
                    if ( eventHandler->isStartRotationEvent() ) {
                        eventHandler->onProcessRotationEvent(yawPos, pitchPos, SLIDER_ROTATION_SENSITIVITY);
                        camera->syncCameraOrientation();
                        update();
                    }
                    break;
                case Mouse::Action::RELEASED :
                    eventHandler->onStopRotationEvent(yawPos, pitchPos);
                    break;
            }
            break;

        case Slider::Action::MOVE :
            switch (mouseAction) {
                case Mouse::Action::PRESSED :
                    eventHandler->onStartPanEvent(horizontalPos, verticalPos);
                    break;
                case Mouse::Action::MOVED :
                    if ( eventHandler->isStartPanEvent() ) {
                        eventHandler->onProcessPanEvent(horizontalPos, verticalPos, SLIDER_PAN_SENSITIVITY);
                        camera->syncCameraOrientation();
                        update();
                    }
                    break;
                case Mouse::Action::RELEASED :
                    eventHandler->onStopPanEvent(horizontalPos, verticalPos);
                    break;
            }
            break;

        case Slider::Action::ZOOM:
            eventHandler->onProcessZoomEvent(position > camera->getFOV() ? -1 : 1);
            update();
            break;
    }
}
