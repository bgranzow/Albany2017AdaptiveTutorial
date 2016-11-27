#include "gmodel.hpp"
#include <cassert>
#include <iostream>

using namespace gmod;

namespace {

static const double width = 0.0625;
static const double height1 = 0.125;
static const double height2 = 0.125;
static const double height3 = 0.5;
static const double depth = 0.125;
static const double ligament = 0.0375;
static const double notch_radius = 0.0035;
static const double large_radius = 0.04;
static const double tri_height = 0.025;
static const double tri_end_x = (width-ligament);
static const double tri_end_y = notch_radius+0.005;

PointPtr p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;
ObjPtr l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15,l16,l17,l18,l19;

static void create_points() {
  p1 = new_point2(Vector{0,0,0});
  p2 = new_point2(Vector{width-ligament-notch_radius,0,0});
  p3 = new_point2(Vector{width-ligament,0,0});
  p4 = new_point2(Vector{width-ligament,notch_radius,0});
  p5 = new_point2(Vector{tri_end_x,notch_radius,0});
  p6 = new_point2(
      Vector{sqrt(pow(large_radius,2)-pow(notch_radius,2)),notch_radius,0});
  p7 = new_point2(Vector{width,notch_radius,0});
  p8 = new_point2(Vector{width,height1,0});
  p9 = new_point2(Vector{0,height1,0});
  p10 = new_point2(Vector{0,large_radius,0});
  p11 = new_point2(Vector{0,tri_height,0});
  p12 = new_point2(Vector{tri_end_x,tri_end_y,0});
  p13 = new_point2(Vector{width,height1+height2,0});
  p14 = new_point2(Vector{0,height1+height2,0});
  p15 = new_point2(Vector{width,height1+height2+height3,0});
  p16 = new_point2(Vector{0,height1+height2+height3,0});
}

static void create_lines() {
  l1 = new_line2(p1,p2);
  l2 = new_arc2(p2,p3,p4);
  l3 = new_line2(p4,p5);
  l4 = new_line2(p5,p6);
  l5 = new_line2(p6,p7);
  l6 = new_line2(p7,p8);
  l7 = new_line2(p8,p9);
  l8 = new_line2(p9,p10);
  l9 = new_line2(p10,p11);
  l10 = new_line2(p11,p1);
  l11 = new_line2(p11,p12);
  l12 = new_line2(p12,p5);
  l13 = new_arc2(p10,p1,p6);
  l14 = new_line2(p8,p13);
  l15 = new_line2(p13,p14);
  l16 = new_line2(p14,p9);
  l17 = new_line2(p13,p15);
  l18 = new_line2(p15,p16);
  l19 = new_line2(p16,p14);
}

static ObjPtr create_face1() {
  auto loop = new_loop();
  add_use(loop, FORWARD, l5);
  add_use(loop, FORWARD, l6);
  add_use(loop, FORWARD, l7);
  add_use(loop, FORWARD, l8);
  add_use(loop, FORWARD, l13);
  return new_plane2(loop);
}

static ObjPtr create_face2() {
  auto loop = new_loop();
  add_use(loop, FORWARD, l4);
  add_use(loop, REVERSE, l13);
  add_use(loop, FORWARD, l9);
  add_use(loop, FORWARD, l11);
  add_use(loop, FORWARD, l12);
  return new_plane2(loop);
}

static ObjPtr create_face3() {
  auto loop = new_loop();
  add_use(loop, FORWARD, l1);
  add_use(loop, FORWARD, l2);
  add_use(loop, FORWARD, l3);
  add_use(loop, REVERSE, l12);
  add_use(loop, REVERSE, l11);
  add_use(loop, FORWARD, l10);
  return new_plane2(loop);
}

static ObjPtr create_face4() {
  auto loop = new_loop();
  add_use(loop, FORWARD, l14);
  add_use(loop, FORWARD, l15);
  add_use(loop, FORWARD, l16);
  add_use(loop, REVERSE, l7);
  return new_plane2(loop);
}

static ObjPtr create_face5() {
  auto loop = new_loop();
  add_use(loop, FORWARD, l17);
  add_use(loop, FORWARD, l18);
  add_use(loop, FORWARD, l19);
  add_use(loop, REVERSE, l15);
  return new_plane2(loop);
}

}

int main()
{
  default_size = 0.005;
  assert((width-ligament-notch_radius) > 0);
  assert((width-ligament) == tri_end_x);
  assert(tri_height < large_radius);
  assert(tri_end_x < large_radius);
  assert(tri_end_y > notch_radius);
  create_points();
  create_lines();
  auto f1 = create_face1();
  auto f2 = create_face2();
  auto f3 = create_face3();
  auto f4 = create_face4();
  auto f5 = create_face5();
  auto group = new_group();
  add_to_group(group, f1);
  add_to_group(group, f2);
  add_to_group(group, f3);
  add_to_group(group, f4);
  add_to_group(group, f5);
  auto ext = extrude_face_group(group,
      [](Vector a){return a + Vector{0,0,depth};});
  auto bar = ext.middle;
  write_closure_to_geo(bar, "notch.geo");
  write_closure_to_dmg(bar, "notch.dmg");
}
