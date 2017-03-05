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

    enum EnginesEnum {
        smoke,
        glyphs,
        nrOfEngine
    };

    typedef std::map<EnginesEnum, AbstractEngine*> EngineMap;
    typedef std::pair<EnginesEnum, AbstractEngine*> EnginePair;

    EngineMap enginemap; //Public since mainwindow accesses it to setup connections

public slots:
    void onGlyphsEngineToggled(bool checked);
    void onSmokeEngineToggled(bool checked);


signals:
    void mouseMoved(QPoint newPosition);
    void windowResized(int width, int height);
    void openGlReady();

private slots:
    void idleLoop();


protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Simulation* simulation;

    //Active Engines
    bool activeEngines[EnginesEnum::nrOfEngine] = {true, false};
    void enginesDraw();

    //Idle Loop
    QTimer* timer;
    void initiateIdleLoop();


    // OpenGL initialization
    void initializeUniforms();
    void initializeColorMapInfo();
    void connectThisAndEngine(AbstractEngine* engine);



};

#endif // CANVAS_H
