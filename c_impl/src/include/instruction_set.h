#ifndef _INSTRUCTION_SET_H
#define _INSTRUCTION_SET_H

#define NOP             0x00
#define LD_BC_U16       0x01
#define LD_IND_BC_A     0x02
#define INC_BC          0x03
#define INC_B           0x04
#define DEC_B           0x05
#define LD_B_U8         0x06
#define RLCA            0x07
#define LD_U16_SP       0x08
#define ADD_HL_BC       0x09
#define LD_A_IND_BC     0x0A
#define DEC_BC          0x0B
#define INC_C           0x0C
#define DEC_C           0x0D
#define LD_C_U8         0x0E
#define RRCA            0x0F
#define STOP            0x10
#define LD_IND_DE_U16   0x11
#define LD_DE_A         0x12
#define INC_DE          0x13
#define INC_D           0x14
#define DEC_D           0x15
#define LD_D_U8         0x16
#define RLA             0x17
#define JR_S8           0x18
#define ADD_HL_DE       0x19
#define LD_A_IND_DE     0x1A
#define DEC_DE          0x1B
#define INC_E           0x1C
#define DEC_E           0x1D
#define LD_E_D8         0x1E
#define RRA             0x1F
#define JR_NZ_S8        0x20
#define LD_HL_U16       0x21
#define LD_IND_HL_INC_A 0x22
#define INC_HL          0x23
#define INC_H           0x24
#define DEC_H           0x25
#define LD_H_U8         0x26
#define DAA             0x27
#define JR_Z_I8         0x28
#define ADD_HL_HL       0x29 
#define LD_A_IND_HL_INC 0x2A
#define DEC_HL          0x2B
#define INC_L           0x2C
#define DEC_L           0x2D
#define LD_L_U8         0x2E
#define CPL             0x2F
#define JR_NC_I8        0x30
#define LD_SP_U16       0x31
#define LD_IND_HL_DEC_A 0x32
#define INC_SP          0x33
#define INC_IND_HL      0x34
#define DEC_IND_HL      0x35
#define LD_IND_HL_U8    0x36
#define SCF             0x37
#define JR_C_I8         0x38
#define ADD_HL_SP       0x39
#define LD_A_IND_HL_DEC 0x3A
#define DEC_SP          0x3B
#define INC_A           0x3C
#define DEC_A           0x3D
#define LD_A_U8         0x3E
#define CFF             0x3F
#define LD_B_B          0x40
#define LD_B_C          0x41
#define LD_B_D          0x42
#define LD_B_E          0x43
#define LD_B_H          0x44
#define LD_B_L          0x45
#define LD_B_IND_HL     0x46
#define LD_B_A          0x47
#define LD_C_B          0x48
#define LD_C_C          0x49
#define LD_C_D          0x4A
#define LD_C_E          0x4B
#define LD_C_H          0x4C
#define LD_C_L          0x4D
#define LD_C_IND_HL     0x4E
#define LD_C_A          0x4F
#define LD_D_B          0x50
#define LD_D_C          0x51
#define LD_D_D          0x52
#define LD_D_E          0x53
#define LD_D_H          0x54
#define LD_D_L          0x55
#define LD_D_IND_HL     0x56
#define LD_D_A          0x57
#define LD_E_B          0x58
#define LD_E_C          0x59
#define LD_E_D          0x5A
#define LD_E_E          0x5B
#define LD_E_H          0x5C
#define LD_E_L          0x5D
#define LD_E_IND_HL     0x5E
#define LD_E_A          0x5F
#define LD_H_B          0x60
#define LD_H_C          0x61
#define LD_H_D          0x62
#define LD_H_E          0x63
#define LD_H_H          0x64
#define LD_H_L          0x65
#define LD_H_IND_HL     0x66
#define LD_H_A          0x67
#define LD_L_B          0x68
#define LD_L_C          0x69
#define LD_L_D          0x6A
#define LD_L_E          0x6B
#define LD_L_H          0x6C
#define LD_L_L          0x6D
#define LD_L_IND_HL     0x6E
#define LD_L_A          0x6F
#define LD_IND_HL_B     0x70
#define LD_IND_HL_C     0x71
#define LD_IND_HL_D     0x72
#define LD_IND_HL_E     0x73
#define LD_IND_HL_H     0x74
#define LD_IND_HL_L     0x75
#define HALT            0x76
#define LD_IND_HL_A     0x77
#define LD_A_B          0x78
#define LD_A_C          0x79
#define LD_A_D          0x7A
#define LD_A_E          0x7B
#define LD_A_H          0x7C
#define LD_A_L          0x7D
#define LD_A_IND_HL     0x7E
#define LD_A_A          0x7F
/*
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
#define
*/

#endif
