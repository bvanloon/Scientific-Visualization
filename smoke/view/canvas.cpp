#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent),
    timer(new QTimer(this))
{
    //Ensure that the mouse is always tracked, even if we didn't click first.
    this->setMouseTracking(true);

    modelViewMatrix.setToIdentity();
    this->initiateIdleLoop();
}

Canvas::~Canvas()
{
    delete this->shaderProgram;
    delete this->timer;
}

void Canvas::setSimulation(Simulation *simulation)
{
    this->simulation = simulation;
}

void Canvas::setSettings(Settings *settings)
{
    this->settings = settings;
}

void Canvas::onSimulationUpdated()
{
    update();
}

void Canvas::idleLoop()
{
    if(!this->settings->simulation->frozen)
    {
        this->simulation->step();
    }
    update();
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    initializeShaders();

    this->triangleEnginge = new TriangleEngine();
    this->vectorEngine = new VectorEngine(this->settings);
    this->smokeEngine = new SmokeEngine(this->settings);
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

    //vectorEngine->draw(this->simulation);
    smokeEngine->draw(this->simulation);

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

void Canvas::initiateIdleLoop()
{
   this->timer->start();
   connect(timer, SIGNAL(timeout()), this, SLOT(idleLoop()));
}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0.0f, 0.0f, (GLfloat) width, (GLfloat) height);

    float nearClippingPlane = -1.0f;
    float farClippingPlane = 1.0f;

    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(0.0, width, 0.0, height, nearClippingPlane, farClippingPlane);

    emit windowResized(width, height);

}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPointF mousePosition = event->localPos();
    emit mouseMoved(QPoint(mousePosition.x(), mousePosition.y()));
}
