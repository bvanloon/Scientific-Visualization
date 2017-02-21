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
        }
        namespace visualization {
            static const float clampStart = 5.0f;
            static const float clampEnd = 15.0f;
            static const bool clampingOn = false;
        }
    }
}

#endif // SETTINGSNS_H
