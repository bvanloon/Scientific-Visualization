#include "canvas.h"
#include <QMouseEvent>

Canvas::Canvas(QWidget* parent) :
    QOpenGLWidget(parent)
{
    //Enusre that the mouse is always tracked, even if we didn't click first.
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

void Canvas::setUniforms()
{
    setMVPMatrix();
}

void Canvas::setMVPMatrix()
{
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.translate(0.0, 0.0, -5.0);
//    matrix.rotate(rotation);

    this->shaderProgram->setUniformValue("mvp_matrix", this->projectionMatrix * modelViewMatrix);
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();

    setUniforms();

    triangleEnginge->draw(this->simulation);

    shaderProgram->release();
}

void Canvas::resizeGL(int w, int h)
{
    qreal aspectRatio = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0;
    const qreal zFar = 7.0;
    const qreal fov = 45.0;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fov, aspectRatio, zNear, zFar);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
}
