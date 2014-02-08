class Triangle

  constructor: (p0, p1, p2, color=green) ->
    @p0 = p0
    @p1 = p1
    @p2 = p2
    @color = color

  getCircle: ->
<<<<<<< HEAD

    yDelta_p0 = p1.y - p0.y;
    xDelta_p0 = p1.x - p0.x;
    yDelta_p1 = p2.y - p1.y;
    xDelta_p1 = p2.x - p1.x;
    pt center = P(0,0);

    p0Slope  = yDelta_p0/xDelta_p0;
    p1Slope  = yDelta_p1/xDelta_p1;  
    center.x = (p0Slope*p1Slope*(p0.y - p2.y) + p1Slope*(p0.x + p1.x) - p0Slope*(p1.x+p2.x) )/(2*(p1Slope-p0Slope) );
    center.y = -1*(center.x - (p0.x+p1.x)/2)/p0Slope + (p0.y+p1.y)/2;
=======
    #TODO
    edge1 = p1.sub p0
    edge2 = p2.sub p1
    slope1= edge1.y / edge1.x
    slope2= edge2.y / edge2.x
>>>>>>> 0788215111a0af3e820231735dc708ae121a377a

    center = new Point(0,0)

    midpoint_edge1 = new Point((p0.x+p1.x)/2, (p0.y+p1.y)/2)
    midpoint_edge2 = new Point((p1.x+p2.x)/2, (p1.y+p2.y)/2)

    return new Circle(center, (center-p0).norm())

  draw: (ctx) ->
    ctx.beginPath()
    ctx.moveTo(@p0.x, @p0.y)
    ctx.lineTo(@p1.x, @p1.y)
    ctx.lineTo(@p2.x, @p2.y)
    ctx.lineTo(@p0.x, @p0.y)
    ctx.strokeStyle = @color.asHex()
    ctx.stroke()
