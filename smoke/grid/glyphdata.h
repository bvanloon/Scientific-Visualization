#ifndef GLYPHDATA_H
#define GLYPHDATA_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>

class GlyphData
{
public:
    GlyphData();
    GlyphData(int numGlyphs);

    void extend(GlyphData* other);
    void extend(GlyphData other);

    void addGlyph(QVector3D position, QVector2D vector, float scalar);

private:

    QVector<QVector3D> positions;
    QVector<QVector3D> vectors;
    QVector<float> scalars;

};

#endif // GLYPHDATA_H
