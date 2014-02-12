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
    b.className = "btn active"
    b.value     = text
    b.id        = name
    b.onclick   = action
    document.getElementById('buttons').appendChild(b)
  reset= -> 
    points.length = 0
    triangles     = 0
    circles       = 0
    if show_circles 
      show_circles = !show_circles
    console.log 'Reset Done!'
    ctx.clearRect(0,0, canvas.width, canvas.height)

  # set global variables here (processing 'setup')
  # no need to actually use Cthese, feel free to add/remove them
  points    = []
  triangles = []
  circles   = []
  show_circles = false

  # edit this, it should be pretty straightforward
  mainloop = ->
    ctx.clearRect(0,0, canvas.width, canvas.height)
    p.draw(ctx) for p in points
    for i in [0..points.length-2] by 3
      if points.length > i+2
        t = new Triangle(points[i], points[i+1], points[i+2])
      else
        t = new Triangle(points[i], points[i+1], mouse)
      t.draw(ctx)
      c = t.getCircle()
      #console.log c
      if show_circles is true
        c.draw(ctx)

  # handlers and thingies that can't be initialized earlier.
  
  window.setInterval(mainloop, 1000/ fps)
  
  canvas.onclick = (e) ->
    points.push mouse

  canvas.onmousemove = (e) -> 
    mouse = new Point(e.offsetX, e.offsetY)

  window.onkeypress = (e) ->
    key = String.fromCharCode e.which
    if key is 'q' 
      show_circles = !show_circles
    if key is 'r'
      reset()
  

  newButton('toggle-circles', 'Toggle Circles', -> show_circles = !show_circles)
  A = new Point(0,5) 
  B = new Point(0,-5) 
  C = new Point(5,0)
  t = new Triangle(A,B,C)
  c = t.getCircle()  
  console.log c

# REQUIREMENTS

# Remove the base trinagle at the end 
# Change the color of the next candidate
# A key for restart it. 
