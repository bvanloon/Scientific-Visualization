#ifndef ABSTRACT3DENGINE_H
#define ABSTRACT3DENGINE_H

#include "abstractengine.h"

#include <QObject>
#include <QMatrix4x4>
#include "utilities/range.h"

class Abstract3DEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      Abstract3DEngine(AbstractEngine::lightModel lightModel,
                       Settings::engines::EnginesTypes engineType);
      virtual void draw() = 0;

   signals:

   public slots:
      void onUpdateModelViewMatrix();

   protected:
      void updateModelViewMatrix(QMatrix4x4 modelMatrix = QMatrix4x4());
      QMatrix4x4 computeViewMatrix();

      static const Range<double> zTranslationRange;

   private slots:

   private:

      QMatrix4x4 toOriginTranslation();

      void connectToSettings();
};

#endif // ABSTRACT3DENGINE_H
