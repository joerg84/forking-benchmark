set terminal png
set output 'pagefaults.png'
set title "Pagefaults (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Pagefaults"
plot "output_forked.dat" using 3:5 t 'Forked" 'with linespoints, \
"output_nonforked.dat" using 3:5 t 'Non-Forked" 'with linespoints

set output 'time.png'
set title "Time (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Time"
plot "output_forked.dat" using 3:4 t 'Forked" 'with linespoints, \
"output_nonforked.dat" using 3:4 t 'Non-Forked" 'with linespoints