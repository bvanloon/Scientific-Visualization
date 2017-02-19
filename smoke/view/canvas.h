#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QDebug>
#include <QTimer>

#include "engines/triangleengine.h"
#include "engines/vectorengine.h"
#include "engines/smokeengine.h"
#include "simulation/simulation.h"



class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget* parent);
    ~Canvas();

    void setSimulation(Simulation *simulation);

signals:
    void mouseMoved(QPoint newPosition);
    void windowResized(int width, int height);

public slots:
    void onSimulationUpdated();
    void onTextureUpdated();
    void onRangeChanged(float minimum, float maximum);

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
    void initializeTexture(QImage *image);

    //Uniforms
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 projectionMatrix;

    QOpenGLTexture *texture;

    void setUniformsToDefaults();
    void setUniforms();
    void setMVPMatrix();
    void setTexture();
    void setRange(float minimum, float maximum);

    Simulation* simulation;

    //Engines
    TriangleEngine *triangleEnginge;
    VectorEngine *vectorEngine;
    SmokeEngine *smokeEngine;


    //Idle Loop
    QTimer* timer;
    void initiateIdleLoop();
};

#endif // CANVAS_H
