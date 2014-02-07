class Point
  x: null
  y: null

  constructor: (x, y) ->
    @x = x
    @y = y

  add: (other) ->
    return new Point(@x + other.x, @y + other.y)
 
