#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include <colormaps/rainbowcolormap.h>

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent),
    timer(new QTimer(this)),
    texture(0)
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
    delete this->texture;
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

void Canvas::onTextureUpdated()
{
    this->setTexture();
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

    setTexture();

}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/vertex.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/fragment.glsl");
    this->shaderProgram->link();
}

void Canvas::initializeTexture(QImage* image)
{
    if(isValid()){
        if (!texture) texture = new QOpenGLTexture(QOpenGLTexture::Target1D);
        if (texture->isCreated()) texture->destroy();

        texture->create();
        texture->setData(image->mirrored());
        texture->setMagnificationFilter(QOpenGLTexture::Nearest);
        texture->setWrapMode(QOpenGLTexture::Repeat);
    }
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();

    setUniforms();

    this->texture->bind();


    //vectorEngine->draw(this->simulation);
    smokeEngine->draw(this->simulation);

    this->texture->release();

    shaderProgram->release();
}

void Canvas::setUniforms()
{
    setMVPMatrix();
    setRange(5.0,15.0);
}

void Canvas::setMVPMatrix()
{
    QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

    this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
}

void Canvas::setTexture()
{
    QImage* colorMap = new RainbowColorMap(256);
    initializeTexture(colorMap);
    delete colorMap;
}

void Canvas::setRange(float minimum, float maximum)
{
    this->shaderProgram->setUniformValue("range.minimum", minimum);
    this->shaderProgram->setUniformValue("range.maximum", maximum);
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
