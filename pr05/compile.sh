#!/bin/sh
echo "Kompiliere filter.c..."
gcc filter.c -o filter
echo "Kompiliere pipe.c..."
gcc pipe.c -o pipe
echo "Fertig"
