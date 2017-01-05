#include "gmodel.hpp"
#include <cassert>
#include <iostream>

using namespace gmod;

int main(int argc, char** argv)
{
  default_size = 0.025;
  auto bar = new_cube(Vector{0,0,0}, Vector{0.1,0,0}, Vector{0,0.1,0},
      Vector{0,0,0.5});
  write_closure_to_geo(bar, "bar.geo");
  write_closure_to_dmg(bar, "bar.dmg");
}
