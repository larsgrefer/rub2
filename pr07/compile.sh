#!/bin/sh

echo "Kompiliere delete"
gcc delete.c -o delete

echo "Kompiliere erzeuger"
gcc pv.c erzeuger.c -o erzeuger

echo "Kompiliere sender"
gcc pv.c sender.c -o sender
