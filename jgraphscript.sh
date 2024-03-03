#!/bin/bash
rm jpg/*
rm frames/*
rm jgr/*
 # make
 make clean
 make

 # Ask for user input for number of lanes
 echo "Enter the odd number of lanes e.g. 1, 3, 5, 7, or 9: "
 read lanes

 # Ask for user input for SEC school
 echo "Enter an SEC school Options: [Alabama, Arkansas, Auburn, Florida, Georgia, Kentucky, LSU, Ole Miss, Mississippi State, Missouri, South Carolina, Tennessee, Texas A&M, Vanderbilt]:"
 read school

 # Creating the jgraph files
 echo "Creating the jgraph files..."
 # run the program
 bin/tracksplits $lanes "$school"



# Specify the directory path
directory_path="jgr"

# Use find to get a list of file names and sort them based on the numeric parts
sorted_files=$(find "$directory_path" -maxdepth 1 -type f | sort -t'_' -k1,1V -k3,3n)

# Converting to jpg
echo "Converting to jpg..."

# Process the sorted file names
i=1
for file in $sorted_files; do
    # echo "$file"
    # Your further processing logic here
    filename="${file#jgr/}"
    filename="${filename%.jgr}"
    jgraph -P $file | ps2pdf - | convert -density 300 - -quality 100 jpg/$filename.jpg
    new_filename=$(printf "frames/frame%03d.jpg" "$i")
    cp jpg/$filename.jpg $new_filename
    ((i++))
done

# Using ffmpeg to create the video
# Ask for name of the video
echo "What would you like to name the video?"
read video_name
echo "Creating the video..."
ffmpeg -framerate 2 -i frames/frame%03d.jpg -c:v libx264 -r 30 -pix_fmt yuv420p mp4/$video_name.mp4
