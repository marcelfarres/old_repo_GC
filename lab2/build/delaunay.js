// Generated by CoffeeScript 1.7.1
(function() {
  var Point, a, b, circle, color, triangle;

  circle = (function() {
    circle.prototype.c = null;

    circle.prototype.r = null;

    function circle(c, r) {
      this.c = c;
      this.r = r;
    }

    conte(punt);

    draw;

    return circle;

  })();

  color = (function() {
    color.prototype.r = null;

    color.prototype.g = null;

    color.prototype.b = null;

    function color(r, g, b) {}

    return color;

  })();

  Point = (function() {
    Point.prototype.x = null;

    Point.prototype.y = null;

    function Point(x, y) {
      this.x = x;
      this.y = y;
    }

    Point.prototype.add = function(other) {
      return new Point(this.x + other.x, this.y + other.y);
    };

    return Point;

  })();

  a = new Point(2, 4);

  b = new Point(-5, 1);

  console.log(a);

  console.log(b);

  console.log(a.add(b));

  Point = (function() {
    Point.prototype.x = null;

    Point.prototype.y = null;

    function Point(x, y) {
      this.x = x;
      this.y = y;
    }

    Point.prototype.add = function(other) {
      return new Point(this.x + other.x, this.y + other.y);
    };

    Point.prototype.sub = function(other) {
      return new Point(this.x - other.x, this.y - other.y);
    };

    Point.prototype.dot = function(other) {
      return new Point(this.x * other.x, this.y * other.y);
    };

    Point.prototype.mult = function(other) {
      return new Point(this.x * other, this.y * other);
    };

    return Point;

  })();

  a = new Point(2, 4);

  b = new Point(-5, 1);

  console.log(a);

  console.log(b);

  console.log(a.add(b));

  console.log(a.sub(b));

  console.log(a.dot(b));

  console.log(a.mult(5));

  triangle = (function() {
    triangle.prototype.p0 = null;

    triangle.prototype.p1 = null;

    triangle.prototype.p2 = null;

    function triangle(p0, p1, p2) {
      this.p0 = p0;
      this.p1 = p1;
      this.p2 = p2;
    }

    return triangle;

  })();

}).call(this);
