#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>

#include <QDebug>

#include "engines/triangleengine.h"
#include "simulation/simulation.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget* parent);
    ~Canvas();

    void setSimulation(Simulation *simulation);

signals:
    void mouseMoved(QPointF newPosition);

public slots:

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    //Shaders
    QOpenGLShaderProgram *shaderProgram;

    // OpenGL initialization
    void initializeShaders();

    //Uniforms
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 projectionMatrix;

    void setUniforms();
    void setMVPMatrix();

    //ONLY USE THIS TO PASS THE SIMULATION TO THE ENGINES
    Simulation* simulation;

    //Engines
    TriangleEngine *triangleEnginge;
};

#endif // CANVAS_H
