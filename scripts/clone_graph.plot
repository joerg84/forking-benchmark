set terminal png
set output 'clone-pagefaults.png'
set title "Pagefaults (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Pagefaults"
plot "clone_output_forked_line.dat" using 3:5 t 'Clone,All" 'with linespoints, \
"clone_output_forked_page.dat" using 3:5 t 'Clone,CacheLine/page" 'with linespoints, \
"clone_output_nonforked_line.dat" using 3:5 t 'Non-Clone,All" 'with linespoints, \
"clone_output_nonforked_page.dat" using 3:5 t 'Non-Clone,CacheLine/page" 'with linespoints

set output 'clone-time.png'
set title "Time (300 MB)"
set xlabel "Percentage of memory touched"
set ylabel "Time"
plot "clone_output_forked_line.dat" using 3:4 t 'Clone,All" 'with linespoints, \
"clone_output_forked_page.dat" using 3:4 t 'Clone,CacheLine/page" 'with linespoints, \
"clone_output_nonforked_line.dat" using 3:4 t 'Non-Clone,All" 'with linespoints, \
"clone_output_nonforked_page.dat" using 3:4 t 'Non-Clone,CacheLine/page" 'with linespoints
