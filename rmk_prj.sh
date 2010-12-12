#!/bin/sh
rm fmi-reversi.pro
qmake -project 2> log && cat build_options >> fmi-reversi.pro &&
qmake fmi-reversi.pro 2> log &&
make 2> log
vim log
