#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include "settings/simulationsettings.h"
#include <QApplication>



Canvas::Canvas(QWidget *parent) :
   QOpenGLWidget(parent),
   timer(new QTimer(this))
{
   this->initiateIdleLoop();
   this->initializeActiveEngines();

   grabGesture(Qt::PinchGesture);
}

Canvas::~Canvas()
{
   delete this->timer;
}

void Canvas::initiateIdleLoop()
{
   this->timer->start();
   connect(timer, SIGNAL(timeout()), this, SLOT(idleLoop()));
}

void Canvas::initializeActiveEngines()
{
   for (int i = 0; i < Settings::engines::EnginesTypes::numberOfEngines; i++)
   {
      activeEngines[static_cast<Settings::engines::EnginesTypes>(i)] = Settings::defaults::engines::activeEngines[i];
   }
}

void Canvas::connectThisAndEngine(AbstractEngine *engine)
{
   connect(this, SIGNAL(windowResized(int,int)),
          engine, SLOT(onWindowChanged(int,int)));
}

void Canvas::enginesDraw()
{
   for (auto const& engine : activeEngines)
   {
      if (engine.second)
      {
         enginemap.find(engine.first)->second->draw(this->simulation);
      }
   }
}

void Canvas::initializeGL()
{
   initializeOpenGLFunctions();
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glEnable(GL_DEPTH_TEST);

   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::smoke, new SmokeEngine()));
   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::glyphs, new VectorEngine(simulation->getSimulationGrid())));
   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::seedPoints, new SeedPointEngine()));
   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::streamLines, new StreamLineEngine(simulation->getSimulationGrid())));

   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::smokeSlices, new SmokeSlicesEngine()));
   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::glyphSlices, new GlyphSliceEngine(simulation->getSimulationGrid())));
   enginemap.insert(EnginePair(Settings::engines::EnginesTypes::streamLineSlices, new StreamLineSlicesEngine(simulation->getSimulationGrid())));

   emit openGlReady();

   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::smoke));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::glyphs));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::seedPoints));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::streamLines));

   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::smokeSlices));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::glyphSlices));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::streamLineSlices));
}

void Canvas::idleLoop()
{
   if (!Settings::simulation().frozen) this->simulation->step();
   update();
}

void Canvas::setSimulation(Simulation *simulation)
{
   this->simulation = simulation;
}

AbstractEngine *Canvas::getEngine(Settings::engines::EnginesTypes engine)
{
   return this->enginemap.find(engine)->second;
}

void Canvas::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   activeEngines[engine] = checked;
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
   if (!Settings::simulation().frozen)
   {
      QPointF mousePosition = event->localPos();
      emit mouseMoved(QPoint(mousePosition.x(), mousePosition.y()));
   }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
   if (QApplication::keyboardModifiers() & Qt::ControlModifier)
   {
      QPointF mousePosition = event->localPos();
      emit seedPointAdded(mousePosition);
   }
}

void Canvas::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   enginesDraw();
}

void Canvas::resizeGL(int width, int height)
{
   glViewport(0.0f, 0.0f, (GLfloat)width, (GLfloat)height);

   emit windowResized(width, height);
}

bool Canvas::event(QEvent *event)
{
   if (event->type() == QEvent::Gesture)
   {
      return gestureEvent(static_cast<QGestureEvent *>(event));
   }
   return QWidget::event(event);
}

bool Canvas::gestureEvent(QGestureEvent *event)
{
   if (QGesture *pinch = event->gesture(Qt::PinchGesture))
   {
      pinchTriggered(static_cast<QPinchGesture *>(pinch));
   }
   return true;
}

void Canvas::pinchTriggered(QPinchGesture *gesture)
{
   QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
   if (changeFlags & QPinchGesture::ScaleFactorChanged)
   {
//        this->zoomingFactor = gesture->scaleFactor();
      qDebug() << "Do stuff!";
   }
   if (gesture->state() == Qt::GestureFinished)
   {
      qDebug() << "Never happens?";
   }
   update();
}
