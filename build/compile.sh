#!/usr/bin/env bash

make clean
make directories

make sqlite_src
make ext_sqlite

make parser
make lexer

make gambit
make check_handler

make rook_parser
make rook_lexer
make rook

make all