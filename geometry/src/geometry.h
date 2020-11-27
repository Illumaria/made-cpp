#pragma once

#include <algorithm>
#include <tr1/cmath>
#include <vector>

const double EPS = 1e-6;

bool equals_(const double& a, const double& b) { return fabs(a - b) < EPS; }

struct Point {
  double x, y;

  explicit Point() : x(0), y(0) {}

  explicit Point(double x, double y) : x(x), y(y) {}

  ~Point() {}

  Point rotate(const Point& center, const double& angle) const {
    double sin_a = std::sin(angle);
    double cos_a = std::cos(angle);

    Point result;
    result.x = center.x + (x - center.x) * cos_a - (y - center.y) * sin_a;
    result.y = center.y + (y - center.y) * cos_a - (x - center.x) * sin_a;

    return result;
  }

  bool operator==(const Point& other) const {
    return equals_(x, other.x) && equals_(y, other.y);
  }

  bool operator!=(const Point& other) const { return !(*this == other); }
};

double distance_(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

size_t mod(const ssize_t& a, const size_t& i, const size_t& b) {
  return a - i < 0 ? b - i : a - i;
}

class Line {
 private:
  double slope, intercept;

 public:
  explicit Line(const Point& a, const Point& b) {
    slope = (a.y - b.y) / (a.x - b.x + EPS * EPS);
    intercept = a.y - slope * a.x;
  }

  explicit Line(const double& k, const double& b) : slope(k), intercept(b) {}

  explicit Line(const Point& a, const double& k)
      : slope(k), intercept(a.y - k * a.x) {}

  double getSlope() const { return slope; }

  double getIntercept() const { return intercept; }

  bool operator==(const Line& other) const {
    return equals_(slope, other.slope) && equals_(intercept, other.intercept);
  }

  bool operator!=(const Line& other) const { return !(*this == other); }
};

class Shape {
 public:
  virtual ~Shape() = 0;

  virtual double perimeter() const = 0;
  virtual double area() const = 0;

  virtual void rotate(const Point& center, const double& angle) = 0;
  virtual void reflex(const Point& center) = 0;
  virtual void reflex(const Line& axis) = 0;
  virtual void scale(const Point& center, const double& coefficient) = 0;

  virtual bool operator==(const Shape& other) const = 0;
  virtual bool operator!=(const Shape& other) const = 0;
};

Shape::~Shape(){};

class Polygon : public Shape {
 protected:
  size_t verticles_num;
  Point* verticles;

 public:
  explicit Polygon(const std::vector<Point>& vec)
      : verticles_num(vec.size()), verticles(new Point[vec.size()]) {
    for (size_t i = 0; i < verticles_num; ++i) verticles[i] = vec[i];
  }

  Polygon(const Polygon& copy)
      : verticles_num(copy.verticles_num),
        verticles(new Point[copy.verticles_num]) {
    for (size_t i = 0; i < verticles_num; ++i) verticles[i] = copy.verticles[i];
  }

  ~Polygon() {}

  std::vector<Point> getVertices() const {
    std::vector<Point> result(verticles_num);
    for (size_t i = 0; i < verticles_num; ++i) result[i] = verticles[i];

    return result;
  }

  double perimeter() const override {
    double result = 0;
    for (size_t i = 1; i < verticles_num; ++i)
      result += sqrt(pow(verticles[i].x - verticles[i - 1].x, 2) +
                     pow(verticles[i].y - verticles[i - 1].y, 2));
      result += sqrt(pow(verticles[0].x - verticles[verticles_num - 1].x, 2) +
                     pow(verticles[0].y - verticles[verticles_num - 1].y, 2));

    return result;
  }

  double area() const override {
    double result = 0;
    for (size_t i = 0; i < verticles_num; ++i) {
      if (i != verticles_num - 1)
        result += (verticles[i].x * verticles[i + 1].y -
                   verticles[i].y * verticles[i + 1].x);
      else
        result +=
            (verticles[i].x * verticles[0].y - verticles[i].y * verticles[0].x);
    }

    return (result >= 0) ? (result * 0.5) : (-result * 0.5);
  }

  void rotate(const Point& center, const double& angle_deg) override {
    double angle = angle_deg * M_PI / 180.;
    double sin_a = std::sin(angle);
    double cos_a = std::cos(angle);
    double temp_x, temp_y;
    for (size_t i = 0; i < verticles_num; ++i) {
      temp_x = verticles[i].x;
      temp_y = verticles[i].y;
      verticles[i].x =
          center.x + (temp_x - center.x) * cos_a - (temp_y - center.y) * sin_a;
      verticles[i].y =
          center.y + (temp_x - center.x) * sin_a + (temp_y - center.y) * cos_a;
    }
  }

  void reflex(const Point& center) override {
    for (size_t i = 0; i < verticles_num; ++i) {
      verticles[i].x += 2 * (center.x - verticles[i].x);
      verticles[i].y += 2 * (center.y - verticles[i].y);
    }
  }

  void reflex(const Line& axis) override {
    double k = axis.getSlope();
    double b = axis.getIntercept();

    double ort_k = -1 / (k + EPS * EPS);

    double ort_x, ort_y, ort_b;
    for (size_t i = 0; i < verticles_num; ++i) {
      ort_b = verticles[i].y - ort_k * verticles[i].x;
      ort_x = (b - ort_b) / (ort_k - k + EPS * EPS);
      ort_y = k * ort_x + b;

      verticles[i].x += 2 * (ort_x - verticles[i].x);
      verticles[i].y += 2 * (ort_y - verticles[i].y);
    }
  }

  void scale(const Point& center, const double& coeff) override {
    for (size_t i = 0; i < verticles_num; ++i) {
      verticles[i].x += (coeff - 1) * (verticles[i].x - center.x);
      verticles[i].y += (coeff - 1) * (verticles[i].y - center.y);
    }
  }

  bool operator==(const Shape& other) const override { return false; }

  bool operator!=(const Shape& other) const override { return true; }

  bool operator==(const Polygon& other) const {
    if (verticles_num != other.verticles_num) return false;

    size_t start = 0;
    bool match_found = false;
    for (size_t i = 0; i < verticles_num; ++i)
      if (verticles[0] == other.verticles[i]) {
        start = i;
        match_found = true;
        break;
      }
    if (!match_found) return false;

    if (verticles[1] == other.verticles[(start + 1) % verticles_num])
      for (size_t i = 2; i < verticles_num; ++i)
        if (verticles[i] != other.verticles[(start + i) % verticles_num])
          return false;
        else if (verticles[1] == other.verticles[mod(start, 1, verticles_num)])
          for (size_t i = 2; i < verticles_num; ++i)
            if (verticles[i] != other.verticles[mod(start, i, verticles_num)])
              return false;
            else
              return false;

    return true;
  }

  bool operator!=(const Polygon& other) const { return !(*this == other); }
};

class Ellipse : public Shape {
 protected:
  Point focus_1, focus_2;
  double dist_sum;

 public:
  explicit Ellipse(const Point& a, const Point& b, const double& dist_sum)
      : focus_1(a), focus_2(b), dist_sum(dist_sum) {}

  Ellipse(const Ellipse& copy)
      : focus_1(copy.focus_1), focus_2(copy.focus_2), dist_sum(copy.dist_sum) {}

  ~Ellipse() {}

  std::pair<Point, Point> focuses() const {
    return std::make_pair(focus_1, focus_2);
  }

  double eccentricity() const { return distance_(focus_1, focus_2) / dist_sum; }

  Point center() const {
    Point result((focus_1.x + focus_2.x) / 2, (focus_1.y + focus_2.y) / 2);
    return result;
  }

  double perimeter() const override {
    return 2 * dist_sum * std::tr1::comp_ellint_2(eccentricity());
  }

  double area() const override {
    return M_PI * pow(dist_sum / 2., 2) * sqrt(1 - pow(eccentricity(), 2));
  }

  void rotate(const Point& center, const double& angle) override {
    double sin_a = std::sin(angle);
    double cos_a = std::cos(angle);
    focus_1.x = center.x + (focus_1.x - center.x) * cos_a -
                (focus_1.y - center.y) * sin_a;
    focus_1.y = center.y + (focus_1.y - center.y) * cos_a -
                (focus_1.x - center.x) * sin_a;
    focus_2.x = center.x + (focus_2.x - center.x) * cos_a -
                (focus_2.y - center.y) * sin_a;
    focus_2.y = center.y + (focus_2.y - center.y) * cos_a -
                (focus_2.x - center.x) * sin_a;
  }

  void reflex(const Point& center) override {
    focus_1.x += 2 * (center.x - focus_1.x);
    focus_1.y += 2 * (center.y - focus_1.y);
    focus_2.x += 2 * (center.x - focus_2.x);
    focus_2.y += 2 * (center.y - focus_2.y);
  }

  void reflex(const Line& axis) override {
    double k = axis.getSlope();
    double b = axis.getIntercept();

    double ort_k = -1 / (k + EPS * EPS);

    double ort_x, ort_y, ort_b;

    ort_b = focus_1.y - ort_k * focus_1.x;
    ort_x = (b - ort_b) / (ort_k - k + EPS * EPS);
    ort_y = k * ort_x + b;

    focus_1.x += 2 * (ort_x - focus_1.x);
    focus_1.y += 2 * (ort_y - focus_1.y);

    ort_b = focus_2.y - ort_k * focus_2.x;
    ort_x = (b - ort_b) / (ort_k - k + EPS * EPS);
    ort_y = k * ort_x + b;

    focus_2.x += 2 * (ort_x - focus_2.x);
    focus_2.y += 2 * (ort_y - focus_2.y);
  }

  void scale(const Point& center, const double& coeff) override {
    focus_1.x += (coeff - 1) * (focus_1.x - center.x);
    focus_1.y += (coeff - 1) * (focus_1.y - center.y);
    focus_2.x += (coeff - 1) * (focus_2.x - center.x);
    focus_2.y += (coeff - 1) * (focus_2.y - center.y);
    dist_sum *= coeff;
  }

  bool operator==(const Shape& other) const override { return false; }

  bool operator!=(const Shape& other) const override { return true; }

  bool operator==(const Ellipse& other) const {
    return equals_(dist_sum, other.dist_sum) &&
           (((focus_1 == other.focus_1) && (focus_2 == other.focus_2)) ||
            ((focus_2 == other.focus_1) && (focus_1 == other.focus_2)));
  }

  bool operator!=(const Ellipse& other) const { return !(*this == other); }
};

class Circle : public Ellipse {
 public:
  explicit Circle(const Point& a, const double& r) : Ellipse(a, a, 2 * r) {}
  ~Circle() {}

  double radius() const { return dist_sum / 2; }

  Point center() const { return focus_1; }

  double perimeter() { return M_PI * dist_sum; }

  double area() { return M_PI * pow(dist_sum, 2) / 4; }
};

class Rectangle : public Polygon {
 public:
  explicit Rectangle(const Point& a, const Point& c, const double& ratio)
      : Polygon({a, Point(), c, Point()}) {
    double angle = atan(ratio);
    Point center;
    center.x = (verticles[0].x + verticles[2].x) / 2;
    center.y = (verticles[0].y + verticles[2].y) / 2;

    verticles[1] = verticles[0].rotate(center, angle);
    verticles[3] = verticles[2].rotate(center, angle);
  }

  ~Rectangle() {}

  Point center() const {
    Point result;
    result.x = (verticles[0].x + verticles[2].x) / 2;
    result.y = (verticles[0].y + verticles[2].y) / 2;

    return result;
  }

  std::pair<Line, Line> diagonals() const {
    Line diag1(verticles[0], verticles[2]);
    Line diag2(verticles[1], verticles[3]);

    return std::make_pair(diag1, diag2);
  }
};

class Square : public Rectangle {
 public:
  explicit Square(const Point& a, const Point& c) : Rectangle(a, c, 1) {}

  ~Square() {}

  Circle circumscribedCircle() const {
    Point center;
    center.x = (verticles[0].x + verticles[2].x) / 2;
    center.y = (verticles[0].y + verticles[2].y) / 2;
    double radius = distance_(center, verticles[0]);
    return Circle(center, radius);
  }

  Circle inscribedCircle() const {
    Point center;
    center.x = (verticles[0].x + verticles[2].x) / 2;
    center.y = (verticles[0].y + verticles[2].y) / 2;
    double radius = distance_(verticles[0], verticles[1]) / 2;
    return Circle(center, radius);
  }
};

class Triangle : public Polygon {
 public:
  explicit Triangle(const Point& a, const Point& b, const Point& c)
      : Polygon({a, b, c}) {}

  ~Triangle() {}

  Circle circumscribedCircle() const {
    Point center;
    double d = 2 * (verticles[0].x * (verticles[1].y - verticles[2].y) +
                    verticles[1].x * (verticles[2].y - verticles[0].y) +
                    verticles[2].x * (verticles[0].y - verticles[1].y));

    center.x = ((pow(verticles[0].x, 2) + pow(verticles[0].y, 2)) *
                    (verticles[1].y - verticles[2].y) +
                (pow(verticles[1].x, 2) + pow(verticles[1].y, 2)) *
                    (verticles[2].y - verticles[0].y) +
                (pow(verticles[2].x, 2) + pow(verticles[2].y, 2)) *
                    (verticles[0].y - verticles[1].y)) /
               d;

    center.y = ((pow(verticles[0].x, 2) + pow(verticles[0].y, 2)) *
                    (verticles[2].x - verticles[1].x) +
                (pow(verticles[1].x, 2) + pow(verticles[1].y, 2)) *
                    (verticles[0].x - verticles[2].x) +
                (pow(verticles[2].x, 2) + pow(verticles[2].y, 2)) *
                    (verticles[1].x - verticles[0].x)) /
               d;

    return Circle(center, distance_(center, verticles[0]));
  }

  Circle inscribedCircle() const {
    double a = distance_(verticles[1], verticles[2]);
    double b = distance_(verticles[0], verticles[2]);
    double c = distance_(verticles[0], verticles[1]);

    Point center;
    center.x = (a * verticles[0].x + b * verticles[1].x + c * verticles[2].x) /
               (a + b + c);
    center.y = (a * verticles[0].y + b * verticles[1].y + c * verticles[2].y) /
               (a + b + c);

    double radius = 2 * area() / perimeter();

    return Circle(center, radius);
  }

  Point centroid() const {
    Point centroid;
    centroid.x = (verticles[0].x + verticles[1].x + verticles[2].x) / 3;
    centroid.y = (verticles[0].y + verticles[1].y + verticles[2].y) / 3;
    return centroid;
  }

  Point orthocenter() const {
    double k_1 = (verticles[2].x - verticles[1].x) /
                 (verticles[1].y - verticles[2].y + EPS * EPS);
    double k_2 = (verticles[2].x - verticles[0].x) /
                 (verticles[0].y - verticles[2].y + EPS * EPS);

    Point ort;
    ort.x = (verticles[1].y - k_2 * verticles[1].x - verticles[0].y +
             k_1 * verticles[0].x) /
            (k_1 - k_2 + EPS * EPS);
    ort.y = k_1 * ort.x + verticles[0].y - k_1 * verticles[0].x;

    return ort;
  }

  Line EulerLine() const {
    return Line(circumscribedCircle().center(), orthocenter());
  }

  Circle ninePointsCircle() const {
    Point ort = orthocenter();
    Circle circ = circumscribedCircle();

    Point center;
    center.x = (ort.x + circ.center().x) / 2;
    center.y = (ort.y + circ.center().y) / 2;

    double radius = circ.radius() / 2;

    return Circle(center, radius);
  }
};
