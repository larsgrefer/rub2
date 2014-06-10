#!/bin/bash

make
echo ""

java Main *.java

echo ""
make clean