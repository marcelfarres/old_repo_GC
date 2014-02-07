class Triangle

  constructor: (p0, p1, p2) ->
    @p0 = p0
    @p1 = p1
    @p2 = p2

  getCircle: ->
    edge1 = p1 - p0
    edge2 = p2 - p1
    slope1= edge1.y / edge1.x
    slope2= edge2.y / edge2.x

    return new Circle(center, (center-p0).norm())
  draw: (ctx) ->
     