#ifndef ABSTRACT3DENGINE_H
#define ABSTRACT3DENGINE_H

#include "abstractengine.h"

#include <QObject>
#include <QMatrix4x4>

class Abstract3DEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      Abstract3DEngine(AbstractEngine::lightModel lightModel,
                       Settings::engines::EnginesTypes engineType);

   signals:

   public slots:

   protected:
      void updateModelViewMatrix(QMatrix4x4 modelMatrix = QMatrix4x4());
      QMatrix4x4 computeViewMatrix();

   private slots:

   private:
};

#endif // ABSTRACT3DENGINE_H
