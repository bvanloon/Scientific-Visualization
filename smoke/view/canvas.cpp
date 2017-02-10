#include "canvas.h"
#include <QMouseEvent>

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent)
{
    //Ensure that the mouse is always tracked, even if we didn't click first.
    this->setMouseTracking(true);

    modelViewMatrix.setToIdentity();
}

Canvas::~Canvas()
{
    delete this->shaderProgram;
}

void Canvas::setSimulation(Simulation *simulation)
{
    this->simulation = simulation;
}

void Canvas::onSimulationUpdated()
{
    update();
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    initializeShaders();

    this->triangleEnginge = new TriangleEngine();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/vertex.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/fragment.glsl");
    this->shaderProgram->link();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();

    setUniforms();

    triangleEnginge->draw(this->simulation);

    shaderProgram->release();
}

void Canvas::setUniforms()
{
    setMVPMatrix();
}

void Canvas::setMVPMatrix()
{
    QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

    this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0.0f, 0.0f, (GLfloat) width, (GLfloat) height);

    float nearClippingPlane = -1.0f;
    float farClippingPlane = 1.0f;

    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(0.0, width, 0.0, height, nearClippingPlane, farClippingPlane);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event->localPos());
}
