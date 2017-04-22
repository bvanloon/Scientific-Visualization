#ifndef GLYPHSLICEENGINE_H
#define GLYPHSLICEENGINE_H

#include "abstractsliceengine.h"
#include "unused.h"
#include "grid/jittergrid.h"

class GlyphSliceEngine : public AbstractSliceEngine {
   Q_OBJECT

   public:
      GlyphSliceEngine();

   public slots:

   signals:

   protected:
      void updateCache();

      void draw();

   private:

      void connectToSettings();

      Settings::sim::Scalar unNormalizedAlpha;
};

#endif // GLYPHSLICEENGINE_H
