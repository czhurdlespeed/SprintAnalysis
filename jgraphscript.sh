make clean
make
bin/tracksplits 9 255 162 68 > jgr/trackplot.jgr
jgraph -P jgr/trackplot.jgr| ps2pdf - | convert -density 300 - -quality 100 plots/trackplot.jpg
open plots/trackplot.jpg
