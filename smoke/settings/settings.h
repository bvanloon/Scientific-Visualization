#ifndef SETTINGSNS_H
#define SETTINGSNS_H

#include "colormaps/colormapfactory.h"
#include "QSize"
#include <limits>
#include "utilities/rotation.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif



namespace Settings {
    class Simulation;
    const Simulation& simulation();

    class Canvas;
    const Canvas& canvas();

    namespace visualization {
        QStringList getScalarVariableNames();

        QStringList getAllVectorVariableNames();

        QStringList getNonDerivedVectorVariableNames();

        class ColorMap;

        class Smoke;
        const Smoke& smoke();

        class Glyphs;
        const Glyphs& glyphs();

        class StreamLines;
        const StreamLines& streamLines();

        class Slices;
        const Slices& slices();
    }

    namespace sim {
        enum Scalar
        {
           fluidDensity,
           fluidVelocityMagnitude,
           forceFieldMagnitude
        };

        enum Vector
        {
           fluidVelocity,
           force,
           fluidDensityGradient,
           fluidVelocityMagnitudeGradient
        };

        enum GlyphsType
        {
           hedgehog,
           triangles,
           airplane,
           cone,
        };

        static const std::map<Settings::sim::GlyphsType, GLint> drawModes =
        {
           std::make_pair(Settings::sim::GlyphsType::hedgehog,  GL_LINES),
           std::make_pair(Settings::sim::GlyphsType::triangles, GL_TRIANGLES),
           std::make_pair(Settings::sim::GlyphsType::airplane,  GL_TRIANGLES),
           std::make_pair(Settings::sim::GlyphsType::cone,      GL_TRIANGLES)
        };
    }

    namespace engines {
        enum EnginesTypes
        {
           glyphs,
           seedPoints,
           streamLines,
           smoke,

           //Slice engines
           smokeSlices,
           glyphSlices,
           streamLineSlices,

           numberOfEngines
        };
    }

    namespace defaults {
        namespace simulation {
            static const float valueRangeMin = 0.0f;
            static const float valueRangeMax = 10.0f;

            static const int forceMin = 1;
            static const int forceMax = 100;
        }

        namespace canvas {
            static const double scalingFactor = 1.0;
            static const QVector3D panningPosition(0.0, 0.0, 0.0);
            static const Rotation rotation;
        }

        namespace visualization {
            namespace colormap {
                static const ColorMapFactory::colorMaps colormap = ColorMapFactory::colorMaps::rainbow;
                static const float clampMin = 0.0f;
                static const float clampMax = 1.0f;
                static const bool clampingOn = false;
                static const float clampEpsilon = 0.0001;
                static const Settings::sim::Scalar scalar = Settings::sim::fluidDensity;

                static const int numColors = 256;
                static const int minNumColors = 2;
                static const int maxNumColors = 256;
                static const float saturation = 1.0f;
                static const float minSaturation = 0.0f;
                static const float maxSaturation = 1.0f;
            }

            namespace glyphs {
                static const QSize gridSize = QSize(20, 15);
                static const Settings::sim::Vector vector = Settings::sim::Vector::fluidVelocity;
                static const Settings::sim::GlyphsType glyphType = Settings::sim::GlyphsType::triangles;
                static const GLint defaultDrawMode = Settings::sim::drawModes.at(Settings::defaults::visualization::glyphs::glyphType);
            }

            namespace streamlines {
                static const double edgeLengthFactor = 0.33;
                static const double totalLengthFactor = std::numeric_limits<double>::infinity();
            }
        }
        namespace engines {
            static const bool activeEngines[7] =
            {
               false, false, false, true,
               //Slice Engines
               true,  false, false
            };
        }
    }
}

#endif // SETTINGSNS_H
