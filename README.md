I'm still working on this project _(:з」∠)_

use a kociemba binary file from https://github.com/muodov/kociemba

the cube looks like this


              |************|
              |*U1**U2**U3*|
              |************|
              |*U4**U5**U6*|
              |************|
              |*U7**U8**U9*|
              |************|
 |************|************|************|************|
 |*L1**L2**L3*|*F1**F2**F3*|*R1**R2**R3*|*B1**B2**B3*|
 |************|************|************|************|
 |*L4**L5**L6*|*F4**F5**F6*|*R4**R5**R6*|*B4**B5**B6*|
 |************|************|************|************|
 |*L7**L8**L9*|*F7**F8**F9*|*R7**R8**R9*|*B7**B8**B9*|
 |************|************|************|************|
              |************|
              |*D1**D2**D3*|
              |************|
              |*D4**D5**D6*|
              |************|
              |*D7**D8**D9*|
              |************|

 and the input order is
 U1, U2, U3, U4, U5, U6, U7, U8, U9,
 U refered to servo 1
 R1, R2, R3, R4, R5, R6, R7, R8, R9,
 R refered to servo 2
 F1, F2, F3, F4, F5, F6, F7, F8, F9,
 F refered to servo 3
 D1, D2, D3, D4, D5, D6, D7, D8, D9,
 D refered to servo 4
 L1, L2, L3, L4, L5, L6, L7, L8, L9,
 L refered to servo 5
 B1, B2, B3, B4, B5, B6, B7, B8, B9.
 B refered to servo 6

 Solution string consists of space-separated parts, each of them represents a single move:


 A single letter by itself means to turn that face clockwise 90 degrees.
 A letter followed by an apostrophe means to turn that face counterclockwise 90 degrees.
 A letter with the number 2 after it means to turn that face 180 degrees.
 e.g. R U R’ U R U2 R’ U

