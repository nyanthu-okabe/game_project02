#include <nyanchu/ecs.h>
#include <iostream> // For debugging

namespace nyanchu {

ECS::ECS() : m_world() {
    std::cout << "ECS initialized" << std::endl;
}

ECS::~ECS() {
    std::cout << "ECS shutdown" << std::endl;
}

flecs::world& ECS::getWorld() {
    return m_world;
}

} // namespace nyanchu