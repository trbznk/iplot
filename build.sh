#!/bin/bash

# cc -Wall -Wextra -o iplot iplot.c
clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a iplot.c -o iplot