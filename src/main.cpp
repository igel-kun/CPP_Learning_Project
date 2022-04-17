#include "tower_sim.hpp"

void test_generic_points() {
    Point<float, 3> p1;
    Point<float, 3> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    std::cout << p3.x() << std::endl;
    Point3D p4{1, 4, 5};
    std::cout << p4.x() << " " << p4.y() << " " << p4.z() << std::endl;
}

int main(int argc, char** argv)
{

    //test_generic_points();
    ContextInitializer contextInitializer {argc, argv};
    TowerSimulation simulation { contextInitializer};
    simulation.launch();

    return 0;
}