: NOD 
    2DUP  < IF  SWAP THEN
    BEGIN DUP
    WHILE
        2DUP MOD
        ROT
        DROP
    REPEAT DROP ;
    
: factorial 
    DUP 2 < IF DROP 1 
    ELSE
    DUP
    BEGIN
        1-
        SWAP OVER
        * SWAP
        DUP 1 =
    UNTIL
DROP THEN ;


1 factorial . 
5 factorial .

235 100 NOD .
100 235 NOD .
100 100 NOD .
5 7 NOD . 



