set terminal pngcairo size 1200,600
set output 'TF_plot.png'

set grid
set xlabel "Frequency (seconds)"
set ylabel "Amplitude"

plot "TF.dat" using 1:1 with lines title "Transfer Function of Tuned Amplifier" lw 2 lc "blue"

set output

