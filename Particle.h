#pragma once
#include <array>
class Particle {
  public:
    static const int dim = 2;  // we are in two dimensions
    std::array<double, 2> pos;

    // default constructor
    Particle() {

    }
    // constructor, with a specified initial position
    Particle(std::array<double, 2> set_pos) {
      this->pos[0] = set_pos[0];
      this->pos[1] = set_pos[1];
    }
};
