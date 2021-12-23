#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

const float g = 9.81;

struct Vector {
  float x;
  float y;

  Vector reflect() const { return {-x, y}; }
};

Vector integratePos(const Vector &pos, const Vector &vel, float endX) {
  const float time = (endX - pos.x) / vel.x;
  const float height = pos.y + vel.y * time - 0.5f * time * time * g;

  return {endX, height};
}

Vector integrateVel(const Vector &pos, const Vector &vel, float endX) {
  const float time = (endX - pos.x) / vel.x;

  return {vel.x, vel.y - g * time};
}

int findeSector(const Vector &startPos, const Vector &startVel,
                std::vector<Vector> &barriers) {
  Vector pos = startPos;
  Vector vel = startVel;
  int nextBarrier = 0;

  while (pos.y > 0) {
    if (nextBarrier > static_cast<int>(barriers.size()) - 1) {
      return barriers.size();
    } else if (nextBarrier < 0) {
      return 0;
    }

    const Vector newPos = integratePos(pos, vel, barriers[nextBarrier].x);
    vel = integrateVel(pos, vel, barriers[nextBarrier].x);
    pos = newPos;

    if (pos.y < barriers[nextBarrier].y) {
      vel = vel.reflect();
    }

    if (vel.x > 0) {
      ++nextBarrier;
    } else {
      --nextBarrier;
    }
  }

  return vel.x > 0 ? nextBarrier : nextBarrier + 1;
}
} // namespace

int main(int argc, char **argv) {
  float h0;
  float vx, vy;
  float x, h;
  std::string filename;
  std::vector<Vector> barriers;

  if (argc == 2) {
    filename = argv[1];
  } else {
    return -1;
  }

  std::ifstream input(filename);

  input >> h0;
  input >> vx >> vy;

  while (input >> x >> h) {
    barriers.push_back({x, h});
  }

  const Vector startPos = {0.f, h0};
  const Vector startVel = {vx, vy};

  int answer = findeSector(startPos, startVel, barriers);

  std::cout << answer << std::endl;

  return 0;
}