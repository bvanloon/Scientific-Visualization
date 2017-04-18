#ifndef STREAMOBJECT_H
#define STREAMOBJECT_H

#include <QObject>

class StreamObject : public QObject {
   Q_OBJECT

   public:
      explicit StreamObject(QObject *parent = 0);

      double timeStep;

   signals:
      void clearCache();

   public slots:
      void ontimeStepChanged(double newTimeStep);

   private slots:

   private:
};

#endif // STREAMOBJECT_H
