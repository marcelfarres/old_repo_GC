class Triangle

  constructor: (p0, p1, p2) ->
    @p0 = p0
    @p1 = p1
    @p2 = p2

  getCircle: ->
    center = new Point(0,0)

    p0Slope = yDelta_p0/xDelta_p0
    p1Slope = yDelta_p1/xDelta_p1
    center.x = (aSlope*p1Slope*(p0.y - p2.y) + p1Slope*(p0.x + p1.x) - 
    p0Slope*(p1.x+p2.x) )/(2* (p1Slope-p0Slope) )
    center.y = -1*(center.x - (p0.x+p1.x)/2)/aSlope +  (p0.y+p1.y)/2
    return new Circle(center, (center-p0).norm())



    yDelta_a = B.y - A.y;
    xDelta_a = B.x - A.x;
    yDelta_b = C.y - B.y;
    xDelta_b = C.x - B.x;
    pt center = P(0,0);

    aSlope = yDelta_a/xDelta_a;
    bSlope = yDelta_b/xDelta_b;  
    center.x = (aSlope*bSlope*(A.y - C.y) + bSlope*(A.x + B.x)
        - aSlope*(B.x+C.x) )/(2* (bSlope-aSlope) );
    center.y = -1*(center.x - (A.x+B.x)/2)/aSlope +  (A.y+B.y)/2;

    return center;
  }
  draw: (ctx) ->
     