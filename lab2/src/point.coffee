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




    
a = new Point(2, 4)
b = new Point(-5, 1)
console.log a
console.log b
console.log a.add b
console.log a.sub b
console.log a.dot b
console.log a.mult 5
