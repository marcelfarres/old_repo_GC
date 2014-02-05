class Circle
  c: null
  r: null 
  color: null

  constructor: (c, r, color=blue) ->
    @c = c
    @r = r
    @color = color

  contains: (point) ->
  	r*r > (@c.x - point.x)*(@c.x - point.x) + (@c.y - point.y) * (@c.y - point.y)

  draw: (ctx) ->
    ctx.beginPath()
    ctx.arc(95,50,40,0,2*Math.PI)
    ctx.strokeStyle = @color.asHex()
    ctx.stroke()