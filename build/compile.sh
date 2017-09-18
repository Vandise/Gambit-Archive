#!/usr/bin/env bash

make clean
make directories

make parser
make lexer

make gambit
make check_handler

make all