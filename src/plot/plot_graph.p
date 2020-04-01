unset log               # remove any log-scaling
unset label             # remove any previous labels
set autoscale 		# scale axes automatically
set autoscale xfixmax
set xtic auto           # set xtics automatically
set ytic auto           # set ytics automatically

set title "Whetstone benchmark"
set xlabel "No. of threads"
set ylabel "MWIPS"

set datafile separator ","	# for csv file
set terminal jpeg		# create jpeg image
set size 1.0, 1.0
set output "result/whetstone.jpeg"

set tics font ", 8"	# set font for axis values
set label sprintf("{/:bold=10 %s}", cpuname) at graph 0.5,0.5 center tc rgbcolor "#808080"

plot "result/whetstone.csv" using 1:2 with linespoints pt 10 notitle,\
	"" using  1:2:1 with labels offset char 1,0.5 notitle
	

