#!/bin/bash

cpuname="\"$(cat /proc/cpuinfo | grep 'model name' | uniq | cut -d ':' -f2)\""
gnuplot -e "cpuname = $cpuname" src/plot/plot_graph.p