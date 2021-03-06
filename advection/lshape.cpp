#include "gmodel.hpp"

int main()
{
  using namespace gmod;
  default_size = 0.1;
  auto p0 = new_point2(Vector{2,2,0});
  auto p1 = new_point2(Vector{2,0,0});
  auto p2 = new_point2(Vector{4,0,0});
  auto p3 = new_point2(Vector{4,4,0});
  auto p4 = new_point2(Vector{0,4,0});
  auto p5 = new_point2(Vector{0,2,0});
  auto l0 = new_line2(p0,p1);
  auto l1 = new_line2(p1,p2);
  auto l2 = new_line2(p2,p3);
  auto l3 = new_line2(p3,p4);
  auto l4 = new_line2(p4,p5);
  auto l5 = new_line2(p5,p0);
  auto loop = new_loop();
  add_use(loop, FORWARD, l0);
  add_use(loop, FORWARD, l1);
  add_use(loop, FORWARD, l2);
  add_use(loop, FORWARD, l3);
  add_use(loop, FORWARD, l4);
  add_use(loop, FORWARD, l5);
  auto f = new_plane2(loop);
  write_closure_to_geo(f, "lshape.geo");
  write_closure_to_dmg(f, "lshape.dmg");
}
