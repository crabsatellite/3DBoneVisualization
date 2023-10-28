//**********************************************************************
// Header includes
//**********************************************************************
#include "renderproxy.h"
#include "camera.h"
#include "event_handle_service/eventhandler.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QMouseEvent>

// TODO: need to avoid hardcode here
namespace {

const float RADIUS = 2.0f;
const QVector3D VIEW_CENTER = QVector3D(0.0f, 0.0f, 0.0f);
const QVector3D CAMERA_POSITION = QVector3D(0.0f, 0.0f, 2.0f);

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
    eventHandler->onStartMouseClickEvent(event);
}

void RenderService::RenderProxy::mouseReleaseEvent(QMouseEvent *event)
{
    eventHandler->onStopMouseClickEvent(event);
}

void RenderService::RenderProxy::mouseMoveEvent(QMouseEvent *event)
{
    if ( eventHandler->isStartMouseClickEvent() ) {
        eventHandler->onProcessMouseClickEvent(event);
        camera->syncCameraOrientation();
        update();
    }
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
