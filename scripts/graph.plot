set terminal png
set output 'pagefaults.png'
set title "Pagefaults (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Pagefaults"
plot "output_forked_line.dat" using 3:5 t 'Forked,All" 'with linespoints, \
"output_forked_page.dat" using 3:5 t 'Forked,CacheLine/page" 'with linespoints, \
"output_nonforked_line.dat" using 3:5 t 'Non-Forked,All" 'with linespoints, \
"output_nonforked_page.dat" using 3:5 t 'Non-Forked,CacheLine/page" 'with linespoints

set output 'time.png'
set title "Time (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Time"
plot "output_forked_line.dat" using 3:4 t 'Forked,All" 'with linespoints, \
"output_forked_page.dat" using 3:4 t 'Forked,CacheLine/page" 'with linespoints, \
"output_nonforked_line.dat" using 3:4 t 'Non-Forked,All" 'with linespoints, \
"output_nonforked_page.dat" using 3:4 t 'Non-Forked,CacheLine/page" 'with linespoints
