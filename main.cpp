#include "framework/ScreenComponent.h"

int main() {
    ScreenComponent *sc = new ScreenComponent(1366, 768);
    sc->init();
    sc->run();
    delete sc;

    return 0;
}