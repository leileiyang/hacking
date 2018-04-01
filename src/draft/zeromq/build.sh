#!/bin/bash

# This a gcc build script.

gcc $1.c -g -I../../ -o $1 -lzmq
