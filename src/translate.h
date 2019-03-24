#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdint.h>

// constants
#define MIN_SHAMT 0
#define MAX_SHAMT ((1 << 6) - 1)
#define MIN_IMMEDIATE INT16_MIN
#define MAX_IMMEDIATE UINT16_MAX
#define MIN_OFFSET MIN_IMMEDIATE
#define MAX_OFFSET MAX_IMMEDIATE
#define MIN_LARGE_IMMEDIATE INT32_MIN
#define MAX_LARGE_IMMEDIATE UINT32_MAX

// instruction fields shift macro
#define OPCODE(opcode) (opcode << 26)
#define RS(rs) (rs << 21)
#define RT(rt) (rt << 16)
#define RD(rd) (rd << 11)
#define SHAMT(shamt) (shamt << 6)
#define FUNCT(funct) (funct & 0b111111)
#define IMMEDIATE(imm) (imm & 0xffff)
#define OFFSET(offset) IMMEDIATE(offset)
#define ADDRESS(addr) (addr)

/* IMPLEMENT ME - see documentation in translate.c */
unsigned write_pass_one(FILE* output, const char* name, char** args,
                        int num_args);

/* IMPLEMENT ME - see documentation in translate.c */
int translate_inst(FILE* output, const char* name, char** args, size_t num_args,
                   uint32_t addr, SymbolTable* symtbl, SymbolTable* reltbl);

/* Declaring helper functions: */

int write_rtype(uint8_t funct, FILE* output, char** args, size_t num_args);

int write_shift(uint8_t funct, FILE* output, char** args, size_t num_args);

/* SOLUTION CODE BELOW */

int write_jr(uint8_t funct, FILE* output, char** args, size_t num_args);

int write_addiu(uint8_t opcode, FILE* output, char** args, size_t num_args);

int write_ori(uint8_t opcode, FILE* output, char** args, size_t num_args);

int write_lui(uint8_t opcode, FILE* output, char** args, size_t num_args);

int write_mem(uint8_t opcode, FILE* output, char** args, size_t num_args);

int write_branch(uint8_t opcode, FILE* output, char** args, size_t num_args,
                 uint32_t addr, SymbolTable* symtbl);

int write_jump(uint8_t opcode, FILE* output, char** args, size_t num_args,
               uint32_t addr, SymbolTable* reltbl);

#endif
