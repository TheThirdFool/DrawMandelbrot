set print "-"

print ""
print "Drawing Mandelbrot set graphs..."

set terminal png size 800,800

set output 'Mandelbrot_Full.png'

set title "Mandelbrot set" font "Times:Roman,24"
unset key
set tic scale 0
set tics font "Times:Roman, 16"

load 'inferno.pal'
set cbrange [0:50]
set cblabel "Escape time" font "Times:Roman,20" offset 1.0,0.0
set samples 10000

set origin -0.02,0.0
set view map
splot "MandelbrotData.txt" using 1:2:3 with image

# ================================================================

set terminal png size 800,800

set output 'Mandelbrot_Valley.png'

set title "Mandelbrot set - Seahorse Valley" font "Times:Roman,24"
unset key
set tic scale 0
set tics font "Times:Roman, 16"

load 'inferno.pal'
set cbrange [0:50]
set cblabel "Escape time" font "Times:Roman,20" offset 1.0,0.0
set samples 10000

set origin -0.02,0.0
set view map
splot "Mandelbrot_ValleyData.txt" using 1:2:3 with image

# ================================================================

print ""
print "Drawing Julia set graph..."

set terminal png size 800,800

set output 'Julia.png'

set title "Julia Set" font "Times:Roman,24"
unset key
set tic scale 0
set tics font "Times:Roman, 16"

load 'inferno.pal'
set cbrange [0:50]
set cblabel "Escape time" font "Times:Roman,20" offset 1.0,0.0
set samples 10000

set origin -0.02,0.0
set view map
splot "JuliaData.txt" using 1:2:3 with image

print ""
print "Done!"
print ""

