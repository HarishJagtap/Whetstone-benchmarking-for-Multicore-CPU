@ECHO off

FOR /F "tokens=* skip=1 delims= usebackq" %%A IN (`wmic cpu get name`) DO FOR /F "tokens=* usebackq" %%B IN ('%%A') DO (SET cpuname="%%B")
gnuplot -e 'cpuname = %cpuname%' src/plot/plot_graph.p