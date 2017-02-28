#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include "settings/simulationsettings.h"


Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent),
    timer(new QTimer(this))
{

    this->initiateIdleLoop();
}

Canvas::~Canvas()
{
    delete this->timer;
}

void Canvas::setSimulation(Simulation *simulation)
{
    this->simulation = simulation;
}

void Canvas::idleLoop()
{
    if(!Settings::simulation().frozen)
    {
        this->simulation->step();
    }
    update();
}

void Canvas::initiateIdleLoop()
{
   this->timer->start();
   connect(timer, SIGNAL(timeout()), this, SLOT(idleLoop()));
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(!Settings::simulation().frozen){
        QPointF mousePosition = event->localPos();
        emit mouseMoved(QPoint(mousePosition.x(), mousePosition.y()));
    }
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //this->vectorEngine = new VectorEngine();
    this->smokeEngine = new SmokeEngine();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    smokeEngine->draw(this->simulation);
//    vectorEngine->draw(this->simulation);

}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0.0f, 0.0f, (GLfloat) width, (GLfloat) height);

    float nearClippingPlane = -1.0f;
    float farClippingPlane = 1.0f;


   this->smokeEngine->setProjectionMatrix(width, height, nearClippingPlane,farClippingPlane);

    emit windowResized(width, height);
    setMVPMatrix();//move
}


//// ----- REMOVE  ------

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
    if(isValid()){
        this->smokeEngine->AbstractEngine::setTexture(colormap);
    }

}

void Canvas::onForceChanged(float force)
{
    if(Settings::visualization().scalar == Settings::Visualization::ScalarVariable::fluidDensity){
        setColorMapValueRange(0.0f, force);
    }
}





void Canvas::setMVPMatrix()
{
    //change to signal slot construction

    this->smokeEngine->AbstractEngine::setMVPMatrix();

}


void Canvas::setColorMapValueRange(float min, float max)
{
    this->smokeEngine->AbstractEngine::setColorMapValueRange(min,max);
}

void Canvas::setColorMapClampRange(float startClamp, float endClamp)
{
    this->smokeEngine->AbstractEngine::setColorMapClampRange(startClamp, endClamp);
}

void Canvas::setColorMapClampingTo(bool clampingOn)
{
    this->smokeEngine->AbstractEngine::setColorMapClampingTo(clampingOn);
}


