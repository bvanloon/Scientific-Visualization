#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include <QApplication>
#include <QVector3D>



Canvas::Canvas(QWidget *parent) :
   QOpenGLWidget(parent),
   timer(new QTimer(this))
{
   this->setUpPrivateConnections();

   connectToSettings();

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
}

void Canvas::initializeActiveEngines()
{
   for (int i = 0; i < Settings::engines::EnginesTypes::numberOfEngines; i++)
   {
      activeEngines[static_cast<Settings::engines::EnginesTypes>(i)] = Settings::defaults::engines::activeEngines[i];
   }
}

void Canvas::buildEngineMap()
{
   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::smoke,
                         new SmokeEngine(simulation->getSimulationGrid())));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::glyphs,
                         new GlyphEngine(simulation->getSimulationGrid())));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::seedPoints,
                         new SeedPointEngine()));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::streamLines,
                         new StreamLineEngine(simulation->getSimulationGrid())));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::smokeSlices,
                         new SmokeSlicesEngine()));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::glyphSlices,
                         new GlyphSliceEngine()));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::streamLineSlices,
                        new StreamLineSlicesEngine()));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::seedCurve,
                        new SeedCurveEngine()));

   enginemap.insert(EnginePair(
                         Settings::engines::EnginesTypes::streakObjects,
                        new StreakSurfaceEngine()));
}

void Canvas::connectEngines()
{
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::smoke));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::glyphs));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::seedPoints));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::streamLines));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::seedCurve));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::streakObjects));

   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::smokeSlices));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::glyphSlices));
   connectThisAndEngine(getEngine(Settings::engines::EnginesTypes::streamLineSlices));
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
      if (engine.second) enginemap.find(engine.first)->second->draw();
   }
}

void Canvas::initializeGL()
{
   initializeOpenGLFunctions();
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

   glPointSize(5.0);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   buildEngineMap();

   emit openGlReady();
}

void Canvas::idleLoop()
{
   if (!Settings::simulation().frozen) this->simulation->step();
   update();
}

void Canvas::onOpenGLReady()
{
   connectEngines();
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
   if (QApplication::keyboardModifiers().testFlag(Qt::AltModifier)) return altMouseEvent(event);

   if (QApplication::mouseButtons() && Qt::AllButtons) return clickMouseEvent(event);
}

void Canvas::clickMouseEvent(QMouseEvent *event)
{
   if (!Settings::simulation().frozen)
   {
      QPointF mousePosition = event->localPos();
      emit mouseMoved(QPoint(mousePosition.x(), mousePosition.y()));
   }
}

void Canvas::altMouseEvent(QMouseEvent *event)
{
   static QVector3D previousMousePosition;

   QVector3D currentMousePosition = QVector3D(Settings::canvas().convertToNormalCoordinates(event->localPos()));

   QVector3D panningDirection = (currentMousePosition - previousMousePosition).normalized();

   emit panningDirectionChanged(panningDirection);

   previousMousePosition = currentMousePosition;
}

void Canvas::controlMouseEvent(QMouseEvent *event)
{
   QPointF mousePosition = event->localPos();
   emit seedPointAdded(mousePosition);
}

void Canvas::shiftMouseEvent(QMouseEvent *event)
{
   QPointF mousePosition = event->localPos();
   emit seedCurveVertexAdded(mousePosition);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
   if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) controlMouseEvent(event);
   if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) shiftMouseEvent(event);
}

void Canvas::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPointSize(5.0);
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

void Canvas::connectToSettings()
{
   connect(&Settings::canvas(), SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            this, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}

void Canvas::setUpPrivateConnections()
{
   connect(this, SIGNAL(openGlReady()), this, SLOT(onOpenGLReady()));
   connect(timer, SIGNAL(timeout()), this, SLOT(idleLoop()));
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
   if (changeFlags & QPinchGesture::ScaleFactorChanged) emit scalingFactorChanged(gesture->scaleFactor());
   if (gesture->state() == Qt::GestureFinished) qDebug() << "Never happens?";
   update();
}
