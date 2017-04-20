#ifndef ABSTRACT3DENGINE_H
#define ABSTRACT3DENGINE_H

#include "abstractengine.h"

#include <QObject>

class Abstract3DEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      Abstract3DEngine(AbstractEngine::lightModel lightModel,
                       Settings::engines::EnginesTypes engineType);

   signals:

   public slots:

   protected:

   private slots:

   private:
};

#endif // ABSTRACT3DENGINE_H
