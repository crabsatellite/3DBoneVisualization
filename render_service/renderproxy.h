#ifndef RENDERPROXY_H
#define RENDERPROXY_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

//**********************************************************************
// Forward declaration
//**********************************************************************
namespace RenderService {
class Camera;
}
namespace EventHandleService {
class EventHandler;
}

//**********************************************************************
// Class declaration
//**********************************************************************
namespace RenderService {

class RenderProxy : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:

//**********************************************************************
// Constructors & destructor
//**********************************************************************
    explicit RenderProxy(QWidget *parent = nullptr);
    ~RenderProxy();

protected:
//**********************************************************************
// Protected methods
//**********************************************************************
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
//**********************************************************************
// Private methods
//**********************************************************************
    void bindVertexData();
    void compileShaders();

private:
//**********************************************************************
// Private attributes
//**********************************************************************
    unsigned int VBO; // Vertex Buffer Object- stores the vertex data in GPU buffer
    unsigned int VAO; // Vertex Array Object - has attribute pointer to interpret the VBO data
    QOpenGLShaderProgram shaderProrgam; // Program to compile/link shaders
    QScopedPointer<RenderService::Camera> camera; // Define how we look at the object
    QScopedPointer<EventHandleService::EventHandler> eventHandler; // Handler user events
};

}
#endif // RENDERPROXY_H
