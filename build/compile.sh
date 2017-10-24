#!/usr/bin/env bash

cat << "EOF"


                .::.          
                _::_           
              _/____\_        ()       
              \      /      <~~~~>
               \____/        \__/         <>_
               (____)       (____)      (\)  )                        __/"""\
                |  |         |  |        \__/      WWWWWW            ]___ 0  }
                |__|         |  |       (____)      |  |       __        /   }
               /    \        |__|        |  |       |  |      (  )     /~    }
              (______)      /____\       |__|       |__|       ||      \____/
             (________)    (______)     /____\     /____\     /__\     /____\
             /________\   (________)   (______)   (______)   (____)   (______)

             RookVM, Pawn Instruction Set, Check Handler, and the Gambit Language

                                  Benjamin J. Anderson - 2017

                          Licensed under MIT - For educational purposes only!


EOF

make clean
make directories

make sqlite_src
make ext_sqlite


cat << "GMB"


                                        ()
                                      <~~~~>
             <>_                       \__/ 
           (\)  )                     (____) 
            \__/                       |  | 
           (____)                      |  | 
            |  |                       |__| 
            |__|                      /____\ 
           /____\                    (______)
          (______)                  (________)

            Setting up the Queen's Gambit



GMB

make parser
make lexer

make gambit


cat << "CHK"



                  __/"""\
                  ]___ 0  }
                      /   }
                    /~    }
                    \____/
                    /____\
                   (______)

                    CHECK


CHK


make check_handler



cat << "PWN"


           WWWWWW 
            |  |                 __ 
            |  |                (  ) 
            |__|                 || 
           /____\               /__\ 
          (______)             (____)

        RookVM with Pawn Instruction Set


PWN

make rook_parser
make rook_lexer
make rook

make all