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

           public slots:
              void ontimeStepChanged(double newTimeStep);

              void onMaximumTimeChanged(double newMaximumTime);

              void onEdgeLengthFactorChanged(double newEdgeLengthFactor);

              void onMaximumTotalLengthFactorChanged(double newValue);

              void onCellSizeChanged(QSizeF currentCellSize);

              void onVectorFieldChanged(Settings::sim::Vector newVectorField);

           private slots:

           private:

              double edgeLengthFactor;
              double totalLengthFactor;

              void connectToOtherSettings();

              double computeEdgeLength(double factor, double cellSize);

              double computeMaximumTotalLength(double factor, double cellSize);

              Settings::sim::Scalar determineMagnitudeGetter(Settings::sim::Vector vectorField);
        };
    }
}

#endif // STREAMOBJECT_H
