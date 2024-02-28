make clean
make
bin/tracksplits 8 0 0.5 0 > jgr/trackplot.jgr
jgraph -P jgr/trackplot.jgr| ps2pdf - | convert -density 300 - -quality 100 plots/trackplot.jpg
open plots/trackplot.jpg
