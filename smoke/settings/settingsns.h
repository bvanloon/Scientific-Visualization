#ifndef SETTINGSNS_H
#define SETTINGSNS_H

namespace Settings {
    class Simulation;
    const Simulation& simulation();

    class Canvas;
    const Canvas &canvas();

    class Visualization;
    const Visualization &visualization();
}

#endif // SETTINGSNS_H
