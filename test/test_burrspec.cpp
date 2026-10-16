#include <catch2/catch_test_macros.hpp>

#include "test_helpers.h"

#include "lib/burrspec.h"
#include "lib/gridtype.h"
#include "lib/voxel.h"

#include <memory>
#include <string>

using namespace bttest;

TEST_CASE("burrSpec: an empty shape is an empty array", "[burrspec]") {
  gridType_c gt(gridType_c::GT_BRICKS);
  auto vp = makeVoxel(gt, 3, 3, 3);
  voxel_c & v = *vp;
  REQUIRE(burrSpec(v) == "[]");
}

TEST_CASE("burrSpec: a single voxel is one layer of one cell", "[burrspec]") {
  gridType_c gt(gridType_c::GT_BRICKS);
  auto vp = makeVoxel(gt, 4, 4, 4);
  voxel_c & v = *vp;
  v.setState(2, 1, 3, voxel_c::VX_FILLED);
  REQUIRE(burrSpec(v) == "[\"x\"]");
}

TEST_CASE("burrSpec: output is cropped to the bounding box", "[burrspec]") {
  gridType_c gt(gridType_c::GT_BRICKS);
  auto vp = makeVoxel(gt, 6, 6, 6);
  voxel_c & v = *vp;
  v.setState(0, 4, 0, voxel_c::VX_FILLED);
  v.setState(1, 4, 0, voxel_c::VX_FILLED);
  v.setState(0, 5, 0, voxel_c::VX_FILLED);
  v.setState(1, 4, 1, voxel_c::VX_FILLED);
  // rows are y, layers are z; the gaps inside the box stay as '.'
  REQUIRE(burrSpec(v) == "[\"xx|x.\", \".x|..\"]");
}

TEST_CASE("burrSpec: a shape away from the origin is not padded", "[burrspec]") {
  gridType_c gt(gridType_c::GT_BRICKS);
  auto vp = makeVoxel(gt, 5, 5, 5);
  voxel_c & v = *vp;
  for (unsigned int x = 2; x < 5; x++)
    v.setState(x, 3, 2, voxel_c::VX_FILLED);
  REQUIRE(burrSpec(v) == "[\"xxx\"]");
}

TEST_CASE("burrSpec: variable voxels are 'v' and count towards the box", "[burrspec]") {
  gridType_c gt(gridType_c::GT_BRICKS);
  auto vp = makeVoxel(gt, 3, 3, 3);
  voxel_c & v = *vp;
  v.setState(0, 0, 0, voxel_c::VX_FILLED);
  v.setState(2, 0, 0, voxel_c::VX_VARIABLE);
  REQUIRE(burrSpec(v) == "[\"x.v\"]");
}
