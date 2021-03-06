#ifndef STREAMOBJECT_H
#define STREAMOBJECT_H

#include <QObject>
#include <QSizeF>
#include "grid/vertex.h"

namespace Settings {
    namespace visualization {
        class StreamObject : public QObject {
           Q_OBJECT

           public:
              explicit StreamObject(QObject *parent = 0);

              Settings::visualization::ColorMap *colorMap;

              double timeStep;
              double maximumTime;

              double edgeLength;
              double totalLength;

              double minimumMagnitude;

              Settings::sim::Vector vectorField;
              Vertex::vectorGetter getVector;

              Settings::sim::Scalar vectorFieldMagnitude;
              Vertex::scalarGetter getMagnitude;

              double getEdgeLengthFactor() const;

              double getTotalLengthFactor() const;

           signals:
              void clearCache();

              void vectorFieldChanged(Settings::sim::Vector vectorField, Settings::sim::Scalar magnitude);

              void textureVariableChanged(Settings::sim::Scalar textureVariable);

           public slots:
              void ontimeStepChanged(double newTimeStep);

              void onMaximumTimeChanged(double newMaximumTime);

              void onEdgeLengthFactorChanged(double newEdgeLengthFactor);

              void onMaximumTotalLengthFactorChanged(double newValue);

              void onCellSizeChanged(QSizeF currentCellSize);

              void onVectorFieldChanged(Settings::sim::Vector newVectorField);

              void onMinimumMagnitudeChanged(double magnitude);

           private slots:

           private:

              double edgeLengthFactor;
              double totalLengthFactor;

              void connectToOtherSettings();

              double computeEdgeLength(double factor, double cellSize);

              double computeMaximumTotalLength(double factor, double cellSize);

              void setVectorField(Settings::sim::Vector vectorField);

              void setVectorFieldMagnitude(Settings::sim::Scalar magnitude);

              Settings::sim::Scalar determineMagnitudeEnum(Settings::sim::Vector vectorField);
        };
    }
}

#endif // STREAMOBJECT_H
