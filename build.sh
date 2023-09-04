#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib


FILES="main.c"
COMPILE_FLAGS="-Wall"
LINK_FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"

cc $FILES $COMPILE_FLAGS $LINK_FLAGS -o main

