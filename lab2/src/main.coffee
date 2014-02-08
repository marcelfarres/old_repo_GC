window.onload = ->
  
  # Can't touch this
  fps = 30
  canvas = document.getElementById('delaunay')
  ctx = canvas.getContext('2d')
  mouse = new Point(0,0)
  ctx.translate(0.5, 0.5)
  window.setInterval(mainloop, 1000/ fps)
  newButton = (name, text, action) -> 
    b = document.createElement("input")
    b.type      = "submit"
    b.className = "btn"
    b.value     = text
    b.id        = name
    b.onclick   = action
    document.getElementById('buttons').appendChild(b)

  # set global variables here (processing 'setup')
  points    = []
  triangles = []
  circles   = []
  show_circles = false

  # edit this, it should prettyjs  be straightforward
  mainloop = ->
    ctx.clearRect(0,0, canvas.width, canvas.height)
    p.draw(ctx) for p in points
    for i in [0..points.length-3] by 3
      t = new Triangle(points[i], points[i+1], points[i+2])
      c = t.getCircle()
      t.draw(ctx)
      c.draw(ctx)
  # handlers and thingies that can't be initialized earlier.
  
  window.setInterval(mainloop, 1000/ fps)
  
  canvas.addEventListener('click', (e) ->
    points.push mouse
  )


  canvas.addEventListener('mousemove', (e) -> 
    mouse = new Point(e.offsetX, e.offsetY)
  )
  newButton('toggle-circles', 'Toggle Circles', -> show_circles = !show_circles)

