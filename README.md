# CS594: JGraph Project 
## Top 9 Men's 100m Dash Race Replication

* [YouTube Link](https://youtube.com/shorts/amDHzSdRS-c?feature=share)
* Steps to Recreate:
  - Clone Git Repository
  - Run `jgraphscript.sh`
      - clears directories
      - compiles source code
      - runs program 
        - specify number of lanes
        - specify SEC School (Track adopts school's colors)
      - converts to jpeg (~1min to complete)
      - converts jpegs to mpg via ffmpeg
* Directory Structure
  - `src` contains source code
  - `bin` contains excutables
  - `jpg` contains jpg images of race at given split and place (see file name)
  - `frame` contains frames for ffmpeg
  - `jgr` contains jgraph files (later converted to jpg's (see `jpg`))
  - `mp4` contains individual track race videos and a combined race video of SEC tracks
* Data
  - Data collected from (https://jmureika.lmu.build/track/splits/splits.html) & (https://worldathletics.org/download/download?filename=26370fd8-c843-448b-960e-5a3620884ac0.pdf&urlSlug=biomechanical-fast-analysis-of-mens-100m)
  - Data entered into CSV file format and read by program
  - Therefore, this program can be fed any 100m race csv data file with up to 9 competitors with reaction and split times e.g. NCAA/USA Championships, World Championships, Olympics, etc.
