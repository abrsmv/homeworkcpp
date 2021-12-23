#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>


namespace {

const double epsilon = 1e-15;

double compare_angles(double xn, double yn, double x, double y) {
  const double length = std::sqrt(x * x + y * y);
  const double x_norm = x / length;
  const double y_norm = y / length;

  const double sin = xn * y_norm - yn * x_norm;
  const double cos = xn * x_norm + yn * y_norm;
  return std::fabs(sin) < epsilon || -sin > 0 ? -(cos - 1.1) : cos - 1.1;
}
}

int main() {
  std::ifstream inputFile("in.txt");

  double xn, yn;
  double x_value, y_value;

  inputFile >> xn >> yn;

  const double length = std::sqrt(xn * xn + yn * yn);
  const double xn_norm = xn / length;
  const double yn_norm = yn / length;

  double maxValue = 0;
  double minValue = 0;

  double x_max = 0, y_max = 0, x_min = 0, y_min = 0;

  while (inputFile >> x_value >> y_value) {
    const double value =
        compare_angles(xn_norm, yn_norm, x_value, y_value);
    const double maxDif = value - maxValue;
    const double minDif = value - minValue;

    if (std::fabs(maxDif) < epsilon || maxDif > 0) {
      maxValue = value;
      x_max = x_value;
      y_max = y_value;
    } else if (std::fabs(minDif) < epsilon || minDif < 0) {
      minValue = value;
      x_min = x_value;
      y_min = y_value;
    }
  }

  std::cout << "Leftmost: " << x_min << " " << y_min << std::endl;
  std::cout << "Rightmost: " << x_max << " " << y_max << std::endl;

  return 0;
}