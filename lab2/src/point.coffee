class Point

  constructor: (x, y, color = blue) ->
    @x = x
    @y = y
    @color = color

  add: (other) ->
    return new Point(@x + other.x, @y + other.y)

  sub: (other) -> 
    return new Point(@x - other.x, @y - other.y)

  dot: (other) -> 
    return new Point(@x * other.x, @y * other.y)

  mult: (other) -> 
    return new Point(@x * other, @y * other)

  draw: (ctx) ->
    sz = 4
    ctx.beginPath()
    ctx.moveTo(@x-sz, @y-sz)
    ctx.lineTo(@x+sz, @y+sz)
    ctx.moveTo(@x+sz, @y-sz)
    ctx.lineTo(@x-sz, @y+sz)
    ctx.strokeStyle = @color.asHex()
    ctx.stroke()
    
  norm: ->
    return @x*@x + @y*@y 
