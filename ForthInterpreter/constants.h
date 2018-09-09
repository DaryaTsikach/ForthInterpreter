#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>

/*RESERVED FORTH WORDS*/

/*LOGICAL OPERANDS*/
#define AND         0x0001
#define OR          0x0002
#define XOR         0x0003
#define LESS        0x0004
#define GREATER     0x0005
#define EQUAL       0x0006
#define NOT         0x0007
#define LESS0       0x0008
#define GREATER0    0x0009
#define EQUAL0      0x0010
#define ULESS       0x0011
#define DEQUAL0     0x0012
#define DLESS       0x0013
#define DEQUAL      0x0014
#define DULESS      0x0015

/*ARIPHMETICAL OPERANDS*/
#define ADD         0x0030
#define SUB         0x0031
#define MULT        0x0032
#define DIV         0x0033
#define MOD         0x0034
#define DIVMOD      0x0035
#define ADD1        0x0036
#define SUB1        0x0037
#define ADD2        0x0038
#define SUB2        0x0039
#define DIV2        0x0040
#define MULDIV      0x0041
#define MULDIVMOD   0x0042

#define ABS         0x0043
#define NEGATE      0x0044
#define DABS        0x0045
#define DNEGATE     0x0046

#define DADD        0x0047
#define DSUB        0x0048
#define DMUL        0x0049
#define DDIV        0x0050
#define DMOD        0x0051

#define UMMUL       0x0052
#define UMDIVMOD    0x0053

/*STACK OPERATIONS*/
#define DUP         0x0070
#define DROP        0x0071
#define OVER        0x0072
#define ROT         0x0073
#define SWAP        0x0074
#define PICK        0x0075
#define ROLL        0x0076
#define DROP2       0x0077
#define DUP2        0x0078
#define OVER2       0x0079
#define ROT2        0x0080
#define SWAP2       0x0081
#define OUT         0x0082
#define OUT2        0x0083

#define NOT_A_WORD          0x1000
#define ONE_LINE_COMMENT    0x1001
#define DOC_COMMENT         0x1002

#define ADD_NEW_WORD        0x3000
#define END_NEW_WORD        0x3001
#define FORGET              0x3002

#define IF                  0x4000
#define ELSE                0x4001
#define THEN                0x4002

#define BEGIN               0x5000
#define UNTIL               0x5001
#define WHILE               0x5002
#define REPEAT              0x5003

#endif // CONSTANTS_H
