build: dummy
	coffee -c src/*.coffee
	rm src/*.js
	coffee -b -j build/delaunay.js -c src/*.coffee
clean:
	rm build/delaunay.js

dummy:
