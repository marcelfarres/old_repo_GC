class Triangle
  p0: null
  p1: null
  p2: null

  constructor: (p0, p1, p2) ->
    @p0 = p0
    @p1 = p1
    @p2 = p2

  getcircle: ()->
    yDelta_p0 = p1.y - p0.y
    xDelta_p0 = p1.x - p0.x
    yDelta_p1 = p2.y - p1.y
    xDelta_p1 = p2.x - p1.x
    center = new Point(0,0)

    p0Slope = yDelta_p0/xDelta_p0
    p1Slope = yDelta_p1/xDelta_p1
    center.x = (aSlope*p1Slope*(p0.y - p2.y) + p1Slope*(p0.x + p1.x) - 
        p0Slope*(p1.x+p2.x) )/(2* (p1Slope-p0Slope) )
    center.y = -1*(center.x - (p0.x+p1.x)/2)/aSlope +  (p0.y+p1.y)/2

    return new Circle(center, (center-p0).norm())

a = new Point(1,1)
b = new Point(-1,-1)
c = new Point(4,4)
t = new Triangle(a,b,c)
t.getcircle()