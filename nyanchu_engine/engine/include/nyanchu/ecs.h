#pragma once

#include <flecs.h>

namespace nyanchu {

class ECS {
public:
    ECS();
    ~ECS();

    flecs::world& getWorld();

private:
    flecs::world m_world;
};

} // namespace nyanchu