
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include "utils.h"

const int SYMTBL_NON_UNIQUE = 0;
const int SYMTBL_UNIQUE_NAME = 1;

/*******************************
 * Helper Functions
 *******************************/

void allocation_failed() {
    write_to_log("Error: allocation failed\n");
    exit(1);
}

void addr_alignment_incorrect() {
    write_to_log("Error: address is not a multiple of 4.\n");
}

void name_already_exists(const char* name) {
    write_to_log("Error: name '%s' already exists in table.\n", name);
}

void write_symbol(FILE* output, uint32_t addr, const char* name) {
    fprintf(output, "%u\t%s\n", addr, name);
}

/* Copy symbol table from TABLE to resized new allocated symbol table,
   CAP will be set to new tabel cap.
 */
Symbol* resize_symbol_array(Symbol* tabel, int len, uint32_t* cap) {
    Symbol* rt = NULL;
    uint32_t rcap;

    if (len == 0)
        rcap = 2;
    else
        rcap = len * 2;

    rt = malloc(sizeof(Symbol) * rcap);
    if (rt == NULL) allocation_failed();
    memcpy(rt, tabel, sizeof(Symbol) * len);
    *cap = rcap;
    return rt;
}

/* Find name in symbol table, if find return index else return -1.
 */
int find_symbol_name(Symbol* table, int len, const char* name) {
    int i = 0;

    while (i < len) {
        if (strcmp(name, table[i].name) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

char* copy_str(const char* name) {
    size_t len;
    char* cs;

    len = strlen(name);
    cs = malloc(sizeof(char) * len + 1);
    if (cs == NULL) allocation_failed();
    strcpy(cs, name);
    return cs;
}

/*******************************
 * Symbol Table Functions
 *******************************/

/* Creates a new SymbolTable containg 0 elements and returns a pointer to that
   table. Multiple SymbolTables may exist at the same time.
   If memory allocation fails, you should call allocation_failed().
   Mode will be either SYMTBL_NON_UNIQUE or SYMTBL_UNIQUE_NAME. You will need
   to store this value for use during add_to_table().
 */
SymbolTable* create_table(int mode) {
    /* YOUR CODE HERE */
    SymbolTable* st;

    st = malloc(sizeof(SymbolTable));
    if (st == NULL) allocation_failed();
    st->tbl = NULL;
    st->cap = 0;
    st->len = 0;
    st->mode = mode;
    return st;
}

/* Frees the given SymbolTable and all associated memory. */
void free_table(SymbolTable* table) {
    /* YOUR CODE HERE */
    Symbol* symbol;
    int i = 0;

    while (i < table->len) {
        symbol = table->tbl + i;
        free(symbol->name);
        i++;
    }
    free(table->tbl);
    free(table);
}

/* Adds a new symbol and its address to the SymbolTable pointed to by TABLE.
   ADDR is given as the byte offset from the first instruction. The SymbolTable
   must be able to resize itself as more elements are added.

   Note that NAME may point to a temporary array, so it is not safe to simply
   store the NAME pointer. You must store a copy of the given string.

   If ADDR is not word-aligned, you should call addr_alignment_incorrect() and
   return -1. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists
   in the table, you should call name_already_exists() and return -1. If memory
   allocation fails, you should call allocation_failed().

   Otherwise, you should store the symbol name and address and return 0.
 */
int add_to_table(SymbolTable* table, const char* name, uint32_t addr) {
    /* YOUR CODE HERE */
    if ((addr % 4) != 0) {
        addr_alignment_incorrect();
        return -1;
    }

    if (table->mode == SYMTBL_UNIQUE_NAME &&
        find_symbol_name(table->tbl, table->len, name) >= 0) {
        name_already_exists(name);
        return -1;
    }

    Symbol* sblarr = NULL;

    if (table->len == table->cap) {
        sblarr = resize_symbol_array(table->tbl, table->len, &table->cap);
        free(table->tbl);
        table->tbl = sblarr;
    }
    sblarr = table->tbl;

    table->len = table->len + 1;
    sblarr[table->len - 1].name = copy_str(name);
    sblarr[table->len - 1].addr = addr;
    return 0;
}

/* Returns the address (byte offset) of the given symbol. If a symbol with name
   NAME is not present in TABLE, return -1.
 */
int64_t get_addr_for_symbol(SymbolTable* table, const char* name) {
    /* YOUR CODE HERE */
    int i;

    i = find_symbol_name(table->tbl, table->len, name);
    if (i == -1) return -1;
    return table->tbl[i].addr;
}

/* Writes the SymbolTable TABLE to OUTPUT. You should use write_symbol() to
   perform the write. Do not print any additional whitespace or characters.
 */
void write_table(SymbolTable* table, FILE* output) {
    /* YOUR CODE HERE */
    Symbol* symbol = NULL;
    int i = 0;

    while (i < table->len) {
        symbol = table->tbl + i;
        write_symbol(output, symbol->addr, symbol->name);
        i++;
    }
}
