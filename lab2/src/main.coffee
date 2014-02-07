window.onload = ->
  
  # Don't touch this
  fps = 30
  canvas = document.getElementById('delaunay')
  ctx = canvas.getContext('2d')
  mouse = null
  window.setInterval(mainloop, 1000/ fps)
  # set global variables here
  points = []

  # edit this, it should be pretty straightforward
  mainloop = ->
    canvas = document.getElementById('delaunay')
    ctx = canvas.getContext('2d')
    ctx.clearRect(0,0, canvas.width, canvas.height)
    p?.draw(ctx) for p in points
    return

  onclick = (e) ->
    points.push mouse
  window.setInterval(mainloop, 1000/ fps)

  # handlers and thingies
  canvas.addEventListener('click', onclick)
  canvas.addEventListener('mousemove', (e) -> 
    mouse = new Point(e.offsetX, e.offsetY))
