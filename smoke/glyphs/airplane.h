#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector3D>
#include "glyphs/abstractglyph.h"

class Airplane : public AbstractGlyph
{
   public:
      Airplane(QVector3D position, QVector3D direction, float scalar);

   private:
      class AirplaneBuilder;
};

class Airplane::AirplaneBuilder {
   public:
      AirplaneBuilder(QVector3D position, QVector3D direction);

      QVector<QVector3D> getNormals();
      QVector<QVector3D> getVertices();

   private:
      QVector3D position;
      QVector3D direction;
};

#endif // AIRPLANE_H
