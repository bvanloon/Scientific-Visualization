#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QDebug>
#include <QTimer>

#include "engines/triangleengine.h"
#include "engines/vectorengine.h"
#include "simulation/simulation.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget* parent);
    ~Canvas();

    void setSimulation(Simulation *simulation);
    void setSettings(Settings *settings);

signals:
    void mouseMoved(QPoint newPosition);
    void windowResized(int width, int height);

public slots:
    void onSimulationUpdated();

private slots:
    void idleLoop();

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

    Simulation* simulation;
    Settings* settings;

    //Engines
    TriangleEngine *triangleEnginge;
    VectorEngine *vectorEngine;

    //Idle Loop
    QTimer* timer;
    void initiateIdleLoop();
};

#endif // CANVAS_H
