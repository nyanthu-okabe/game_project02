#include <nyanchu/engine.h>
#include <nyanchu/renderer.h>

int main() {
    Engine engine;
    engine.init();

    Renderer renderer;

    while (engine.running()) {
        engine.pollEvents();
        engine.beginFrame();

        renderer.drawMesh("cube.obj");

        engine.endFrame();
    }
    return 0;
}
