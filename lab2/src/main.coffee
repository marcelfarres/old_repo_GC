
window.onload = ->
  canvas = document.getElementById('delaunay')
  ctx = canvas.getContext('2d')
  c = new Circle(new Point(10,10), 10 )
  c.draw(ctx)