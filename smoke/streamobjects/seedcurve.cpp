#include "seedcurve.h"

SeedCurve::SeedCurve() :
   shapes::PolyLine()
{}

GPUData SeedCurve::toGPUData(float textureCoordinate, float alpha)
{
   qDebug() << "NOT IMPLEMENTED: SeedCurve::toGPUData";
}

void SeedCurve::applyTransformation(QMatrix4x4 transform)
{
   qDebug() << "NOT IMPLEMENTED: SeedCurve::applyTransformation";
}
