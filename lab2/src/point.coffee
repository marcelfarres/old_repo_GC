class Point
  x: null
  y: null

  constructor: (x, y) ->
    @x = x
    @y = y

  add: (other) ->
    return new Point(@x + other.x, @y + other.y)

  sub: (other) -> 
    return new Point(@x - other.x, @y - other.y)

  dot: (other) -> 
    return new Point(@x * other.x, @y * other.y)

  mult: (other) -> 
    return new Point(@x * other, @y * other)
