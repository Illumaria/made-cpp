# Project 2: geometry

### Problem statement:
Implement the following class hierarchy for geometry shapes on a plane:
- Struct `Point`: a point on a plane. It can be set with two numbers of `double` type. The struct must have `x` and `y` fields and support `==` and `!=` operators.

- Class `Line`: a straight line on a plane. It can be set with two Points, with two numbers — an angular coefficient and an offset, or with a Point and a number (an angular coefficient). Lines must support comparison with `==` and `!=` operators.

- Abstract class `Shape`: a figure.

- Class `Polygon`: a polygon. This is a special case of a `Shape`. A `Polygon` must support the following methods:
  - `verticesCount()`: returns the number of vertices;
  - `std::vector<Point> getVertices`: returns the vertices of the `Polygon`.

A `Polygon` can be constructed from a vector of `Point`s in the order of traverse. We'll assume that polygons with self-intersections do not occur.

- Class `Ellipse`: an ellipse. This is a special case of a `Shape`. An `Ellipse` must support the following methods:
  - `std::pair<Point,Point> focuses()`: returns the focuses of an ellipse;
  - `double eccentricity()`: returns the eccentricity of an ellipse;
  - `Point center()`: returns the center of an ellipse.

An `Ellipse` can be constructed from two `Point`s (focuses) and a `double` number (the sum of distances from any ellipse point to the focuses).

- Class `Circle`: a circle. This is a special case of an `Ellipse`. A `Circle` must support the following methods:
  - `double radius()`: returns the radius of an ellipse.

A `Circle` can be constructed with a `Point` (center) and a number (radius).

- Class `Rectangle`: a rectangle. This is a special case of a `Polygon`. A `Polygon` must support the following methods:
  - `Point center()`: returns the center of a rectangle;
  - `std::pair<Line, Line> diagonals()`: returns the pair of a rectangle disgonals.

A `Rectangle` can be constructed with two `Points` (its opposite vertices) and a number (the ratio of adjacent sides of a rectangle). From the two suitable rectangles we choose the one with the shorter side located on the left side of the diagonal if we look from the first specified point in the direction of the second.

- Class `Square`: a square. This is a special case of a `Rectangle`. A `Square` must support the following methods:
  - `Circle circumscribedCircle()`;
  - `Circle inscribedCircle()`.

A `Square` can be constructed with two `Point`s (its opposite vertices).

- Class `Triangle`: a triangle. This is a special case of a `Polygon`. A `Triangle` must support the following methods:
  - `Circle circumscribedCircle()`;
  - `Circle inscribedCircle()`;
  - `Point centroid()`: the center of mass of a triangle;
  - `Point orthocenter()`: the orthocenter of a triangle;
  - `Line EulerLine()`: the Euler line of a triangle;
  - `Circle ninePointsCircle()`: the Euler's circle of a triangle.

Every figure must support the following methods:
- `double perimeter()`: the perimeter of a figure;
- `double area()`: the area of a figure;
- `operator==(const Shape& another)`: check if the figure matches `another` figure.

Every figure must support the following transformations:
- `rotate(Point center, double angle)`: rotate by the `angle` (in degrees, counter clockwise) relative to the `center`;
- `reflex(Point center)`: symmetry relative to the `center`;
- `reflex(Line axis)`: symmetry relative to the `axis`;
- `scale(Point center, double coefficient)`: homothety with the specified `coefficient` and the `center`.
