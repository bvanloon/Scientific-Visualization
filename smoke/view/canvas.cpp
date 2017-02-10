#include "canvas.h"

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent)
{
    this->setMouseTracking(true);
}

Canvas::~Canvas()
{
    delete this->shaderProgram;
}

void Canvas::setSimulation(Simulation *simulation)
{
    this->simulation = simulation;
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

    this->shaderProgram->bind();

    this->triangleEnginge->draw(this->simulation);

    this->shaderProgram->release();
}

void Canvas::resizeGL(int w, int h)
{
    qDebug() << "resizeGL: not yet implemented" << &endl;

//    // Calculate aspect ratio
//    qreal aspect = qreal(w) / qreal(h ? h : 1);

//    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
//    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

//    // Reset projection
//    projection.setToIdentity();

//    // Set perspective projection
    //    projection.perspective(fov, aspect, zNear, zFar);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "moving!";
}
