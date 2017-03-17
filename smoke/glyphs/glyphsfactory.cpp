#include "glyphsfactory.h"
#include "glyphs/hedgehog.h"
#include "glyphs/triangle.h"
#include "glyphs/airplane.h"
#include "glyphs/cone.h"

#include <QDebug>

GlyphsFactory::GlyphsFactory()
{}

GlyphsTriangulation GlyphsFactory::createGlyphs(GlyphData data, Settings::sim::GlyphsType glypType)
{
   switch (glypType)
   {
   case Settings::sim::GlyphsType::hedgehog:
      return createHedgehogs(data);

   case Settings::sim::GlyphsType::triangles:
      return createTriangles(data);

   case Settings::sim::GlyphsType::airplane:
      return createAirplanes(data);

   case Settings::sim::GlyphsType::cone:
      return createCones(data);

   default:
      return GlyphsTriangulation();
   }
}

GlyphsTriangulation GlyphsFactory::createHedgehogs(GlyphData data)
{
   GlyphsTriangulation triangulation;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = HedgeHog(data.getPositions().at(i),
                                            data.getDirections().at(i),
                                            data.getTextureCoordinates().at(i));
      triangulation.extend(currentGlyph);
   }
   return triangulation;
}

GlyphsTriangulation GlyphsFactory::createTriangles(GlyphData data)
{
   GlyphsTriangulation triangulation;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = Triangle(data.getPositions().at(i),
                                             data.getDirections().at(i),
                                             data.getTextureCoordinates().at(i));
      triangulation.extend(currentGlyph);
   }
   return triangulation;
}

GlyphsTriangulation GlyphsFactory::createAirplanes(GlyphData data)
{
   GlyphsTriangulation triangulation;

   for (int i = 0; i < data.numGlyphs(); ++i)
   {
      AbstractGlyph currentGlyph = Airplane(data.getPositions().at(i),
                                              data.getDirections().at(i),
                                              data.getTextureCoordinates().at(i));
      triangulation.extend(currentGlyph);
   }
   return triangulation;
}

GlyphsTriangulation GlyphsFactory::createCones(GlyphData data)
{
   GlyphsTriangulation triangulation;

   AbstractGlyph currentGlyph = Cone(QVector3D(200, 100, 0), QVector3D(0.0, 0.1, 0.0), 0.0);
   triangulation.extend(currentGlyph);

   static bool warningPrinted = false;
   if(!warningPrinted){
       qDebug() << "GlyphsFactory::createCones: Computing the triangluation of a single hardcoded cone";
       warningPrinted = true;
   }

//   for (int i = 0; i < data.numGlyphs(); ++i)
//   {
//      AbstractGlyph currentGlyph = Cone(data.getPositions().at(i),
//                                               data.getDirections().at(i),
//                                               data.getTextureCoordinates().at(i));
//      triangulation.extend(currentGlyph);
//   }
   return triangulation;
}

QStringList GlyphsFactory::getGlyphsNames()
{
   QStringList glyphsNamesList;

   glyphsNamesList << "Hedgehogs"
                   << "Triangles"
                   << "Airplanes"
                   << "Cones";

   return glyphsNamesList;
}
