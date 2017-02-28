#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include "settings/simulationsettings.h"

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent),
    texture(0),
    timer(new QTimer(this))
{
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

void Canvas::onValueRangeChanged(float minimum, float maximum)
{
    setColorMapValueRange(minimum, maximum);
}

void Canvas::onSetClamping(bool clampingOn)
{
    setColorMapClampingTo(clampingOn);
}

void Canvas::onsetClampingRange(float minimum, float maximum)
{
    setColorMapClampRange(minimum, maximum);
}

void Canvas::onColorMapChanged(AbstractColorMap colormap)
{
    setTexture(colormap);
}

void Canvas::onForceChanged(float force)
{
    if(Settings::visualization().scalar == Settings::Visualization::ScalarVariable::fluidDensity){
        setColorMapValueRange(0.0f, force);
    }
}

void Canvas::idleLoop()
{
    if(!Settings::simulation().frozen)
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

    this->vectorEngine = new VectorEngine();
    this->smokeEngine = new SmokeEngine();

    initializeUniforms();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/vertex.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/fragment.glsl");
    this->shaderProgram->link();
}

void Canvas::initializeUniforms()
{
    setMVPMatrix();
    initializeColorMapInfo();
}

void Canvas::initializeColorMapInfo()
{
    setTexture(*ColorMapFactory::get()->createColorMap(Settings::defaults::visualization::colormap::colormap,
                                                      Settings::defaults::visualization::colormap::numColors,
                                                      Settings::defaults::visualization::colormap::saturation));
    setColorMapValueRange(Settings::defaults::simulation::valueRangeMin, Settings::defaults::simulation::valueRangeMax);
    setColorMapClampRange(Settings::defaults::visualization::colormap::clampMin, Settings::defaults::visualization::colormap::clampMax);
    setColorMapClampingTo(Settings::defaults::visualization::colormap::clampingOn);
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();

    this->texture->bind();

    smokeEngine->draw(this->simulation);
//    vectorEngine->draw(this->simulation);

    this->texture->release();

    shaderProgram->release();
}

void Canvas::setMVPMatrix()
{
    shaderProgram->bind();
    QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

    this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
    shaderProgram->release();
}

void Canvas::setTexture(QImage image)
{
    if(isValid()){
        if (!texture) texture = new QOpenGLTexture(QOpenGLTexture::Target1D);
        if (texture->isCreated()) texture->destroy();

        texture->create();
        texture->setData(image.mirrored());
        texture->setMagnificationFilter(QOpenGLTexture::Nearest);
        texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    }
}

void Canvas::setColorMapValueRange(float min, float max)
{
    this->shaderProgram->bind();
    this->shaderProgram->setUniformValue("colorMapInfo.minimum", min);
    this->shaderProgram->setUniformValue("colorMapInfo.maximum", max);
    this->shaderProgram->release();
}

void Canvas::setColorMapClampRange(float startClamp, float endClamp)
{
    this->shaderProgram->bind();
    this->shaderProgram->setUniformValue("colorMapInfo.clampMin", startClamp);
    this->shaderProgram->setUniformValue("colorMapInfo.clampMax", endClamp);
    this->shaderProgram->release();
}

void Canvas::setColorMapClampingTo(bool clampingOn)
{
    this->shaderProgram->bind();
    this->shaderProgram->setUniformValue("colorMapInfo.clampingOn", clampingOn);
    this->shaderProgram->release();
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
    setMVPMatrix();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(!Settings::simulation().frozen){
        QPointF mousePosition = event->localPos();
        emit mouseMoved(QPoint(mousePosition.x(), mousePosition.y()));
    }
}
