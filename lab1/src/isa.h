/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define OLD_SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))
#define DROP_ZEROS(v, sb) (v << (31-sb)) >> (31-sb)

#define SIGNEXT(v, sb) OLD_SIGNEXT(DROP_ZEROS(v, sb), sb)
#define ZEROEXT(v, sb) (~0U >> (31-sb)) & v

// R instruction
int ADD (int Rd, int Rs1, int Rs2, int Funct3) { //R Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SUB (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLL (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLT (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  int cRs2 = CURRENT_STATE.REGS[Rs2];
  cur = (cRs1 < cRs2);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  unsigned int cRs1 = CURRENT_STATE.REGS[Rs1];
  unsigned int cRs2 = CURRENT_STATE.REGS[Rs2];
  cur = (cRs1 < cRs2);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int XOR (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRL (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRA (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  int cRs2 = CURRENT_STATE.REGS[Rs2];
  cur = (cRs1 < 0) ? ((cRs1 >> cRs2) | ~(~0U >> cRs2)) : (cRs1 >> cRs2);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int OR(int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int AND (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

// I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) { //I Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,11);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LB (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  cur = SIGNEXT(valInMem, 7);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LH (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  cur = SIGNEXT(valInMem, 15);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LW (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  cur = valInMem;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LBU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  cur = ZEROEXT(valInMem, 7);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LHU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int valInMem = mem_read_32(CURRENT_STATE.REGS[Rs1] + Imm);
  cur = ZEROEXT(valInMem, 15);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLLI (int Rd, int Rs1, int Zimm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << Zimm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = (CURRENT_STATE.REGS[Rs1] < Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  unsigned int cRs1u = CURRENT_STATE.REGS[Rs1];
  unsigned int Immu = Imm;
  cur = cRs1u < Immu;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int XORI (int Rd, int Rs1, int Imm, int Funct3) { //I Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm,11);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRLI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRAI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  int cRs1 = CURRENT_STATE.REGS[Rs1];
  cur = (cRs1 < 0) ? ((cRs1 >> Imm) | ~(~0U >> Imm)) : (cRs1 >> Imm);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int ORI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm,11);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int ANDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & SIGNEXT(Imm,11);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

// U Instruction
int AUIPC (int Rd, int Upimm) { 

  int cur = 0;
  cur = Upimm << 12;
  NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + cur;
  return 0;

}
int LUI (int Rd, int Upimm) { 

  int cur = 0;
  cur = Upimm << 12;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

// S Instruction
int SB (int Rs1, int Rs2, int Imm, int Funct3){
  
  return 0;
}
int SH (int Rs1, int Rs2, int Imm, int Funct3){
  
  return 0;
}
int SW (int Rs1, int Rs2, int Imm, int Funct3){

  return 0;
}

// B instructions
int BNE (int Rs1, int Rs2, int Imm, int Funct3) { //B Type
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}

int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;
}

int BLT (int Rs1, int Rs2, int Imm, int Funct3) { //B Type

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BGE (int Rs1, int Rs2, int Imm, int Funct3) { //B Type

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + SIGNEXT(Imm,13);
  return 0;

}
int BLTU (int Rs1, int Rs2, int Imm, int Funct3) { //B Type

  int cur = 0;
  Imm = Imm << 1;
  unsigned int cRs1u = CURRENT_STATE.REGS[Rs1];
  unsigned int cRs2u = CURRENT_STATE.REGS[Rs2];
  if (cRs1u < cRs2u)
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BGEU (int Rs1, int Rs2, int Imm, int Funct3) { //B Type

  int cur = 0;
  Imm = Imm << 1;
  unsigned int cRs1u = CURRENT_STATE.REGS[Rs1];
  unsigned int cRs2u = CURRENT_STATE.REGS[Rs2];
  if (cRs1u >= cRs2u)
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}

// I instruction
int JALR (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0;
  cur = CURRENT_STATE.PC + 4;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.REGS[Rd] + SIGNEXT(Imm, 12);
  return 0;

}

// J instruction
int JAL (int Rd, int Imm) { 

  int cur = 0;
  cur = CURRENT_STATE.PC + 4;
  NEXT_STATE.REGS[Rd] = cur;
  NEXT_STATE.PC = CURRENT_STATE.PC + SIGNEXT(Imm, 12);
  return 0;

}

int ECALL (char* i_){return 0;}

#endif
