#ifndef SETTINGSNS_H
#define SETTINGSNS_H

namespace Settings {
    class Simulation;
    const Simulation& simulation();

    class Canvas;
    const Canvas &canvas();

    class Visualization;
    const Visualization &visualization();

    namespace defaults {
        namespace simulation {
            static const float valueRangeMin = 0.0f;
            static const float valueRangeMax = 20.0f;

            static const int forceMin = 1;
            static const int forceMax = 100;
        }
        namespace visualization {
            namespace colormap {
                static const float clampMin = 0.0f;
                static const float clampMax = 1.0f;
                static const bool clampingOn = false;
                static const float clampEpsilon = 0.01;

                static const int numColors = 256;
                static const int minNumColors = 2;
                static const int maxNumColors = 256;
            }
        }
    }
}

#endif // SETTINGSNS_H
