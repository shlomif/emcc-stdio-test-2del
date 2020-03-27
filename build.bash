#! /bin/bash
#
# build.bash
#

emcc untitled.cpp -o filetest.html -lidbfs.js -s FETCH=1 -s FORCE_FILESYSTEM=1 -s NO_EXIT_RUNTIME=1
emcc hellow.cpp -o hellow.html -lidbfs.js -s FETCH=1 -s FORCE_FILESYSTEM=1 -s NO_EXIT_RUNTIME=1
