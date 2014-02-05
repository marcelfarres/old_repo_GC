class circle
  c: null
  r: null 
  color: null

  constructor: (c, r, color=blue) ->
    @c = c
    @r = r

  contains: (point) ->
  	r*r > (@c.x - point.x)*(@c.x - point.x) + (@c.y - point.y) * (@c.y - point.y)

  draw: ->
    context.beginPath();
    context.arc(95,50,40,0,2*Math.PI);
    context.strokeStyle = @color.asHex;
    context.stroke();