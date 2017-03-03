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

#include "engines/vectorengine.h"
#include "engines/smokeengine.h"
#include "simulation/simulation.h"
#include "colormaps/colormapfactory.h"



class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget* parent);
    ~Canvas();

    void setSimulation(Simulation *simulation);

    //Engines
    VectorEngine *vectorEngine;
    SmokeEngine *smokeEngine;




signals:
    void mouseMoved(QPoint newPosition);
    void windowResized(int width, int height);

public slots:
    void onValueRangeChanged(float minimum, float maximum);
    void onSetClamping(bool clampingOn);
    void onsetClampingRange(float minimum, float maximum);
    void onColorMapChanged(AbstractColorMap colormap);
    void onForceChanged(float force);

private slots:
    void idleLoop();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    // OpenGL initialization
    void initializeUniforms();
    void initializeColorMapInfo();


    void setTexture(QImage image);
    void setColorMapValueRange(float min, float max);
    void setColorMapClampRange(float startClamp, float endClamp);
    void setColorMapClampingTo(bool clampingOn);


    Simulation* simulation;



    //Idle Loop
    QTimer* timer;
    void initiateIdleLoop();
};

#endif // CANVAS_H
