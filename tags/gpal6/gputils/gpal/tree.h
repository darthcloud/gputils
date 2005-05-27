/* parse tree
   Copyright (C) 2003
   Craig Franklin

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef __TREE_H__
#define __TREE_H__

/* FIXME: change name from node_unknown to tag_unknown */

enum node_tag { 
  node_unknown,
  node_assembly,
  node_body,
  node_binop,
  node_call,
  node_constant, 
  node_cond,
  node_decl,
  node_file,
  node_func,  
  node_head,  
  node_loop,
  node_pragma,
  node_proc,
  node_string,
  node_symbol, 
  node_unop
};

enum node_op { 
  op_unknown,  /* unknown operation */
  op_add,      /* add */
  op_sub,      /* subtract */
  op_mult,     /* multiply */
  op_div,      /* divide */
  op_mod,      /* modulus */
  op_neg,      /* negative */
  op_com,      /* complement */
  op_and,      /* and */
  op_or,       /* or */
  op_xor,      /* exclusive or */
  op_not,      /* not */
  op_lsh,      /* left shift */
  op_rsh,      /* right shift */
  op_land,     /* logical and */
  op_lor,      /* logical or */
  op_gt,       /* branch if greater than */
  op_lt,       /* branch if less than */
  op_gte,      /* branch if greater than or equal */
  op_lte,      /* branch if less than or equal */
  op_eq,       /* branch if equal */
  op_ne        /* branch if not equal */
};

enum node_type { 
  type_unknown,
  type_var,
  type_const
};

enum node_size { 
  size_unknown,
  size_bit,
  size_byte
};

/* FIXME: maybe use near and far for bank and page storage key words */

enum node_storage { 
  storage_unknown,
  storage_public,  /* local data which is visible to other modules */
  storage_private, /* local data which is not visible to other modules */
  storage_local,   /* external data on the same page or bank with module */
  storage_extern   /* external data which is on an unknown page or bank */
};

enum source_type {
  source_unknown,
  source_header,   /* a processor header file */
  source_module,   /* a source file */
  source_public,   /* the public file for the module being compiled */
  source_with      /* the public file for a external module */ 
};

typedef struct node_struct tree;

typedef struct node_struct {
  enum node_tag tag;
  union {
    char *assembly;
    struct {
      tree *decl;
      tree *statements;
    } body;
    struct {
      int op;
      tree *p0, *p1;
    } binop;
    struct {
      char *name;
      tree *args;
    } call;
    int constant;
    struct {
      /* conditional (if) */
      tree *cond;
      tree *body;
      tree *next; /* else or elsif */
    } cond;    
    struct {
      enum node_type type;
      enum node_size size;
      char *name;
      tree *init;
    } decl;
    struct {
      enum source_type type;
      tree *body;
    } file;
    struct {
      tree *head;
      enum node_size ret;
      tree *body;
    } func;
    struct {
      char *name;
      tree *args;
    } head;
    struct {
      /* for, while, ... */
      tree *init;   /* initalization code */
      tree *exit;   /* exit loop if not true */
      tree *incr;   /* code executed at the end of each pass (for loops) */
      tree *body;
    } loop;
    tree *pragma;
    struct {
      tree *head;
      tree *body;
    } proc;
    char *string;
    char *symbol;
    struct {
      int op;
      tree *p0;
    } unop;
  } value;

  /* node list */
  tree *prev;
  tree *next;

  /* debug information */
  int file_id;
  int line_number;

} node;

#define BODY_DECL(B)       (B)->value.body.decl
#define BODY_STATEMENTS(B) (B)->value.body.statements
#define BINOP_OP(B)        (B)->value.binop.op
#define BINOP_LEFT(B)      (B)->value.binop.p0
#define BINOP_RIGHT(B)     (B)->value.binop.p1
#define CALL_NAME(C)       (C)->value.call.name
#define CALL_ARGS(C)       (C)->value.call.args
#define COND_TEST(C)       (C)->value.cond.cond
#define COND_BODY(C)       (C)->value.cond.body
#define COND_NEXT(C)       (C)->value.cond.next
#define DECL_TYPE(D)       (D)->value.decl.type
#define DECL_SIZE(D)       (D)->value.decl.size
#define DECL_NAME(D)       (D)->value.decl.name
#define DECL_INIT(D)       (D)->value.decl.init
#define FILE_TYPE(F)       (F)->value.file.type
#define FILE_BODY(F)       (F)->value.file.body
#define FUNC_HEAD(F)       (F)->value.func.head
#define FUNC_BODY(F)       (F)->value.func.body
#define HEAD_NAME(H)       (H)->value.head.name
#define HEAD_ARGS(H)       (H)->value.head.args
#define LOOP_INIT(L)       (L)->value.loop.init
#define LOOP_EXIT(L)       (L)->value.loop.exit
#define LOOP_INCR(L)       (L)->value.loop.incr
#define LOOP_BODY(L)       (L)->value.loop.body
#define PROC_HEAD(P)       (P)->value.proc.head
#define PROC_STOR(F)       (F)->value.proc.storage
#define PROC_BODY(P)       (P)->value.proc.body
#define UNOP_OP(B)         (B)->value.unop.op
#define UNOP_ARG(B)        (B)->value.unop.p0

void init_nodes(void);
void free_nodes(void);

tree *mk_node(enum node_tag tag);
tree *mk_assembly(char *assembly);
tree *mk_body(tree *decl, tree *statements);
tree *mk_binop(enum node_op op, tree *p0, tree *p1);
tree *mk_call(char *name, tree *args);
tree *mk_constant(int value);
tree *mk_cond(tree *cond, tree *body, tree *next);
tree *mk_decl(enum node_type type, enum node_size size, char *name, tree *init);
tree *mk_file(tree *body, enum source_type type);
tree *mk_func(tree *head, enum node_size ret, tree *body);
tree *mk_head(char *name, tree *args);
tree *mk_loop(tree *init, tree *exit, tree *incr, tree *body);
tree *mk_pragma(tree *pragma);
tree *mk_proc(tree *head, tree *body);
tree *mk_string(char *value);
tree *mk_symbol(char *value);
tree *mk_unop(enum node_op op, tree *p0);

tree *node_list(tree *head, tree *tail);

char *find_node_name(tree *node);
tree *find_node(tree *search, char *name, enum node_tag tag);

void print_node(tree *node, int level);

#endif