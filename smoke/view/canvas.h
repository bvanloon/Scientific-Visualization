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
#include "engines/seedpointengine.h"
#include "simulation/simulation.h"
#include "colormaps/colormapfactory.h"



class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
   Q_OBJECT

   public:
      Canvas(QWidget *parent);
      ~Canvas();

      void setSimulation(Simulation *simulation);

      typedef std::map<Settings::engines::EnginesTypes, AbstractEngine *> EngineMap;
      typedef std::pair<Settings::engines::EnginesTypes, AbstractEngine *> EnginePair;
      typedef std::map<Settings::engines::EnginesTypes, bool> ActiveEnginesMap;

      EngineMap enginemap; //Public since mainwindow accesses it to setup connections
      ActiveEnginesMap activeEngines;
   public slots:

      void onEngineToggled(Settings::engines::EnginesTypes engine, bool checked);

   signals:
      void mouseMoved(QPoint newPosition);

      void windowResized(int width, int height);

      void openGlReady();

      void seedPointAdded(QPointF position);

   private slots:
      void idleLoop();


   protected:
      void initializeGL() Q_DECL_OVERRIDE;

      void paintGL() Q_DECL_OVERRIDE;

      void resizeGL(int width, int height) Q_DECL_OVERRIDE;

      void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

      void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

   private:
      Simulation *simulation;

      //Engines
      void initializeActiveEngines();

      void connectThisAndEngine(AbstractEngine *engine);

      void enginesDraw();

      //Idle Loop
      QTimer *timer;
      void initiateIdleLoop();


      // OpenGL initialization
      void initializeUniforms();

      void initializeColorMapInfo();
};

#endif // CANVAS_H
