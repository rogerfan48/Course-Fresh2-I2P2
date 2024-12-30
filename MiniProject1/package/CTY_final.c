#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define
#define MAXLEN 256
#define TBLSIZE 64
#define PRINTERR 0
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

//enum
typedef enum {
    UNKNOWN, END, ENDFILE, INT, ID, 
    ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN,
    OR, AND, XOR, INCDEC, ADDSUB_ASSIGN
} TokenSet;

typedef enum { 
    CONST, MEMORY, REGISTER, TEMPMEMORY
} OperandType;

typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, 
    NOTFOUND, RUNOUT, NOTLVAL,
    DIVZERO, SYNTAXERR
} ErrorType;

//struct
typedef struct {
    char name[MAXLEN];
    OperandType type;
    int pos;
    int value;
} Symbol;

typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

typedef struct {
    int value;
    OperandType type;
    int has_var;
    int pos;
} ret;

//global variable
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];
int sbcount = 0;
Symbol table[64];
short register_available[8];
int borrow = TBLSIZE;
//function prototype
TokenSet getToken(void);
int match(TokenSet token);
void advance(void);
char *getLexeme(void);
void err(ErrorType errorNum);
void initTable(void);
void statement(void);
BTNode *makeNode(TokenSet tok, const char *lexe);
BTNode *factor(void);
BTNode *assign_expr(void);
BTNode *or_expr(BTNode *temp);
BTNode *or_expr_tail(BTNode *left);
BTNode *and_expr(BTNode *temp);
BTNode *and_expr_tail(BTNode *left);
BTNode *xor_expr(BTNode *temp);
BTNode *xor_expr_tail(BTNode *left);
BTNode *addsub_expr(BTNode *temp);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr(BTNode *temp);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr(BTNode *temp);
void freeTree(BTNode *root);
Symbol *get_or_declare_var(char *str);
Symbol *search_val(char *str);
int get_reg(void);
int remain_reg(void);
void print_op(char c);
ret codeGen(BTNode *root);
//functions

TokenSet getToken(void) {
    int i = 0;
    char c = '\0';
    while ((c = fgetc(stdin)) == ' ' || c == '\t');
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        if (c == '_' || isalpha(c)) error(SYNTAXERR);
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } 
    else if (c == '+') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '+') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else if (c == '=') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        } //else if(c=='-') error(SYNTAXERR);
        ungetc(c, stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } 
    else if (c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '-') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else if (c == '=') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        }
        //else if(c=='+') error(SYNTAXERR);
        ungetc(c, stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } 
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } 
    else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } 
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } 
    else if (c == '&') {
        strcpy(lexeme, "&");
        return AND;
    } 
    else if (c == '|') {
        strcpy(lexeme, "|");
        return OR;
    } 
    else if (c == '^') {
        strcpy(lexeme, "^");
        return XOR;
    } 
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } 
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } 
    else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } 
    else if (c == EOF) return ENDFILE;
    else return UNKNOWN;
}
int match(TokenSet token) {
    if (curToken == UNKNOWN) advance();
    return token == curToken;
}

void advance(void) { curToken = getToken(); }


char *getLexeme(void) { 
    return lexeme; 
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}

void initTable(void) {
    strcpy(table[0].name, "x");
    strcpy(table[1].name, "y");
    strcpy(table[2].name, "z");
    table[0].pos = 0;
    table[1].pos = 4;
    table[2].pos = 8;
    table[0].type = table[1].type = table[2].type = MEMORY;
    sbcount = 3;
}

void statement(void) {
    BTNode *retp = NULL;
    if (match(ENDFILE)) {
        if(table[0].type==CONST) printf("MOV r0 %d\n", table[0].value);
        else printf("MOV r0 [0]\n");
        if(table[1].type==CONST) printf("MOV r1 %d\n", table[1].value);
        else printf("MOV r1 [4]\n");
        if(table[2].type==CONST) printf("MOV r2 %d\n", table[2].value);
        else printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } 
    else if (match(END)) advance();
    else {
        retp = assign_expr();
        if (match(END)) {
            ret tmp = codeGen(retp);
            if (tmp.type == REGISTER) register_available[tmp.pos] = 1;
            else if(tmp.type == TEMPMEMORY) borrow++;
            freeTree(retp);
            advance();
        } 
        else {
            error(SYNTAXERR);
        }
    }
}

Symbol *get_or_declare_var(char *str) {
    for (int i = 0; i < sbcount; i++)
        if (!strcmp(str, table[i].name)) return &table[i];
    if (sbcount >= borrow) {error(RUNOUT);}
    strcpy(table[sbcount].name, str);
    table[sbcount].pos = sbcount * 4;
    table[sbcount].type = MEMORY;
    return &table[sbcount++];
}

Symbol *search_val(char *str) {
    for (int i = 0; i < sbcount; i++)
        if (!strcmp(str, table[i].name)) return &table[i];
    error(UNDEFINED);
    return NULL;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTNode *factor() {
    BTNode *retp = NULL;
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        retp->val = atoi(getLexeme());
        advance();
    } 
    else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } 
    else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID)) {
            retp->left = makeNode(ID, getLexeme());
            advance();
            retp->right = makeNode(INT, "1");
            retp->right->val = 1;
        } else {error(NOTNUMID);}
    } 
    else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else {error(MISPAREN);}
    } 
    else {error(NOTNUMID);}
    return retp;
}

BTNode *assign_expr(void) {
    BTNode *retp = NULL, *left = NULL;
    if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (match(ADDSUB_ASSIGN)) {
            retp = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
        } else if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
        } else
            retp = or_expr(left);
    } else
        retp = or_expr(NULL);
    return retp;
}

BTNode *or_expr(BTNode *temp) {
    BTNode *node = xor_expr(temp);
    return or_expr_tail(node);
}

BTNode *or_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = or_expr(NULL);
        return or_expr_tail(node);
    } else
        return left;
}

BTNode *and_expr(BTNode *temp) {
    BTNode *node = addsub_expr(temp);
    return and_expr_tail(node);
}

BTNode *and_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr(NULL);
        return and_expr_tail(node);
    } else
        return left;
}

BTNode *xor_expr(BTNode *temp) {
    BTNode *node = and_expr(temp);
    return xor_expr_tail(node);
}

BTNode *xor_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr(NULL);
        return xor_expr_tail(node);
    } else
        return left;
}

BTNode *addsub_expr(BTNode *temp) {
    BTNode *node = muldiv_expr(temp);
    return addsub_expr_tail(node);
}

BTNode *addsub_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr(NULL);
        return addsub_expr_tail(node);
    } else
        return left;
}

BTNode *muldiv_expr(BTNode *temp) {
    BTNode *node = unary_expr(temp);
    return muldiv_expr_tail(node);
}

BTNode *muldiv_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return muldiv_expr_tail(node);
    } else
        return left;
}

BTNode *unary_expr(BTNode *temp) {
    if (temp) return temp;
    if (match(ADDSUB)) {
        BTNode *node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = makeNode(INT, "0");
        node->right = unary_expr(NULL);
        return node;
    } else
        return factor();
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int get_reg() {
    for (int i = 0; i < 8; i++)
        if (register_available[i]) {
            register_available[i] = 0;
            return i;
        }
    {error(RUNOUT);}
    return -1;
}

int remain_reg(){
    int num=0;
    for(int i=0;i<8;i++) if(register_available[i]) num++;
    return num;
}

void print_op(char c){
    if(c=='+') printf("ADD ");
    else if(c=='-') printf("SUB ");
    else if(c=='*') printf("MUL ");
    else if(c=='/') printf("DIV ");
    else if(c=='&') printf("AND ");
    else if(c=='|') printf("OR ");
    else if(c=='^') printf("XOR ");
}

ret codeGen(BTNode *root) {
    ret retval={}, lv, rv;
    char c;
    int reg1, reg2;
    if (root != NULL) {
        Symbol *sym;
        c = root->lexeme[0];
        switch (root->data) {
            case ID:
                sym = search_val(root->lexeme);
                if(sym->type==CONST){
                    retval.type = CONST;
                    retval.has_var = 1;
                    retval.value = sym->value;
                }
                else if(sym->type==MEMORY){
                    retval.type = MEMORY;
                    retval.pos = sym->pos;
                }
                break;
            case INT:
                retval.type = CONST;
                retval.value = root->val;
                retval.has_var = 0;
                break;
            case ASSIGN:
                if (root->left->data != ID) {error(SYNTAXERR);}
                rv = codeGen(root->right);
                sym = get_or_declare_var(root->left->lexeme);
                if (rv.type == CONST) {
                    sym->type = CONST;
                    sym->value = rv.value;
                    retval.type = CONST;
                    retval.has_var = 1;
                    retval.value = rv.value;
                } 
                else if (rv.type == MEMORY||rv.type == TEMPMEMORY) {
                    reg1 = get_reg();
                    printf("MOV r%d [%d]\n", reg1, rv.pos);
                    printf("MOV [%d] r%d\n", sym->pos, reg1);
                    sym->type = MEMORY;
                    if(rv.type == TEMPMEMORY) borrow++;
                    if(remain_reg()<2){
                        register_available[reg1] = 1;
                        retval.type = MEMORY;
                        retval.pos = sym->pos;
                        return retval;
                    }
                    else{
                        retval.type = REGISTER;
                        retval.pos = reg1;
                        return retval;
                    }
                } 
                else if (rv.type == REGISTER) {
                    printf("MOV [%d] r%d\n", sym->pos, rv.pos);
                    sym->type = MEMORY;
                    retval.type = REGISTER;
                    retval.pos = rv.pos;
                }
                break;
            case ADDSUB: case MULDIV: case OR: case AND: case XOR:
                lv = codeGen(root->left);
                rv = codeGen(root->right);
                if (lv.type == CONST) {
                    if (rv.type == CONST) {
                        retval.type = CONST;
                        if(rv.has_var||lv.has_var)
                            retval.has_var = 1;
                        else
                            retval.has_var = 0;
                        if (c == '+') retval.value = lv.value + rv.value;
                        else if (c == '-') retval.value = lv.value - rv.value;
                        else if (c == '*') retval.value = lv.value * rv.value;
                        else if (c == '|') retval.value = lv.value | rv.value;
                        else if (c == '&') retval.value = lv.value & rv.value;
                        else if (c == '^') retval.value = lv.value ^ rv.value;
                        else if (c == '/') {
                            if (rv.value == 0&&!rv.has_var){
                                error(DIVZERO);
                            }
                            else if(rv.value == 0){
                                reg1 = get_reg();
                                printf("MOV r%d %d\n", reg1, lv.value);
                                reg2 = get_reg();
                                printf("MOV r%d 0\n", reg2);
                                print_op(c);
                                printf("r%d r%d\n", reg1, reg2);
                                register_available[reg2] = 1;
                                if(remain_reg()<2&&borrow>sbcount){
                                    retval.type = TEMPMEMORY;
                                    retval.pos = (--borrow)*4;
                                    printf("MOV [%d] r%d\n", retval.pos, reg1);
                                    register_available[reg1] = 1;
                                    return retval;
                                }
                                else{
                                    retval.type = REGISTER;
                                    retval.pos = reg1;
                                    return retval;
                                }
                                return retval;
                            }
                            else retval.value = lv.value / rv.value;
                        }
                    } 
                    else if (rv.type == MEMORY||rv.type == TEMPMEMORY) {
                        reg1 = get_reg();
                        reg2 = get_reg();
                        printf("MOV r%d %d\n", reg1, lv.value);
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        register_available[reg2] = 1;
                        if(rv.type==TEMPMEMORY) borrow++;
                        if(remain_reg()<2&&borrow>sbcount){
                            register_available[reg1] = 1;
                            retval.type = TEMPMEMORY;
                            retval.pos = (--borrow)*4;
                            printf("MOV [%d] r%d\n", retval.pos, reg1);
                            return retval;
                        }
                        else{
                            retval.type = REGISTER;
                            retval.pos = reg1;
                            return retval;
                        }
                    } 
                    else if (rv.type == REGISTER) {
                        reg1 = get_reg();
                        printf("MOV r%d %d\n", reg1, lv.value);
                        print_op(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        register_available[rv.pos] = 1;
                        retval.type = REGISTER;
                        retval.pos = reg1;
                    }
                    return retval;
                } 
                else if (lv.type == MEMORY||lv.type == TEMPMEMORY) {
                    if(lv.type==TEMPMEMORY) borrow++;
                    reg1 = get_reg();
                    printf("MOV r%d [%d]\n", reg1, lv.pos);
                    if (rv.type == CONST) {
                        reg2 = get_reg();
                        printf("MOV r%d %d\n", reg2, rv.value);
                        if(c=='/'&&rv.value==0&&!rv.has_var) {error(DIVZERO);}
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        register_available[reg2] = 1;
                    }
                    else if (rv.type == MEMORY||rv.type == TEMPMEMORY) {
                        reg2 = get_reg();
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        if(rv.type==TEMPMEMORY) borrow++;
                        register_available[reg2] = 1;
                    } 
                    else if (rv.type == REGISTER) {
                        print_op(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        register_available[rv.pos] = 1;
                    }
                    if(remain_reg()<2&&borrow>sbcount){
                        register_available[reg1] = 1;
                        retval.type = TEMPMEMORY;
                        retval.pos = (--borrow)*4;
                        printf("MOV [%d] r%d\n", retval.pos, reg1);
                        return retval;
                    }
                    else{
                        retval.type = REGISTER;
                        retval.pos = reg1;
                        return retval;
                    }
                    return retval;
                } 
                else if (lv.type == REGISTER) {
                    if (rv.type == REGISTER) {
                        print_op(c);
                        printf("r%d r%d\n", lv.pos, rv.pos);
                        register_available[rv.pos] = 1;
                    } 
                    else if (rv.type == CONST) {
                        reg1 = get_reg();
                        printf("MOV r%d %d\n", reg1, rv.value);
                        if(c=='/'&&rv.value==0&&!rv.has_var) {error(DIVZERO);}
                        print_op(c);
                        printf("r%d r%d\n", lv.pos, reg1);
                        register_available[reg1] = 1;
                    } 
                    else if (rv.type == MEMORY||rv.type == TEMPMEMORY) {
                        reg1 = get_reg();
                        printf("MOV r%d [%d]\n", reg1, rv.pos);
                        print_op(c);
                        printf("r%d r%d\n", lv.pos, reg1);
                        register_available[reg1] = 1;
                        if(rv.type==TEMPMEMORY) borrow++;
                    }
                    retval.type = REGISTER;
                    retval.pos = lv.pos;
                    return retval;
                }
                break;
            case ADDSUB_ASSIGN:
                if (root->left->data != ID) {error(UNDEFINED);}
                rv = codeGen(root->right);
                sym = search_val(root->left->lexeme);
                if (rv.type == CONST) {
                    if(sym->type==CONST){
                        if(c=='+')
                            sym->value = sym->value + rv.value;
                        else if(c=='-')
                            sym->value = sym->value - rv.value;
                        retval.type = CONST;
                        retval.value = sym->value;
                        retval.has_var = 1;
                        return retval;
                    }
                    else{
                        reg1 = get_reg();
                        reg2 = get_reg();
                        printf("MOV r%d [%d]\n", reg1, sym->pos);
                        printf("MOV r%d %d\n", reg2, rv.value);
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        register_available[reg2] = 1;
                    }
                } 
                else if (rv.type == REGISTER) {
                    reg1 = get_reg();
                    if(sym->type==CONST){
                        printf("MOV r%d %d\n", reg1, sym->value);
                        print_op(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        sym->type = MEMORY;
                        register_available[rv.pos] = 1;
                    }
                    else{
                        printf("MOV r%d [%d]\n", reg1, sym->pos);
                        print_op(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        register_available[rv.pos] = 1;
                    }
                } 
                else if (rv.type == MEMORY||rv.type == TEMPMEMORY) {
                    if(rv.type==TEMPMEMORY) borrow++;
                    if(sym->type==CONST){
                        reg1 = get_reg();
                        printf("MOV r%d %d\n", reg1, sym->value);
                        reg2 = get_reg();
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        sym->type = MEMORY;
                        register_available[reg2] = 1;
                    }
                    else{
                        reg1 = get_reg();
                        printf("MOV r%d [%d]\n", reg1, sym->pos);
                        reg2 = get_reg();
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        print_op(c);
                        printf("r%d r%d\n", reg1, reg2);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        register_available[reg2] = 1;
                    }
                }
                if(remain_reg()<2&&borrow>sbcount){
                    register_available[reg1] = 1;
                    retval.type = MEMORY;
                    retval.pos = sym->pos;
                    return retval;
                }
                else{
                    retval.type = REGISTER;
                    retval.pos = reg1;
                    return retval;
                }
                break;
            case INCDEC:
                if (root->left->data != ID) error(SYNTAXERR);
                sym = search_val(root->left->lexeme);
                if (sym->type == CONST) {
                    if (c == '+') sym->value++;
                    else if (c == '-') sym->value--;
                    retval.type = CONST;
                    retval.value = sym->value;
                    retval.has_var = 1;
                    return retval;
                } 
                else if (sym->type == MEMORY) {
                    reg1 = get_reg();
                    printf("MOV r%d [%d]\n", reg1, sym->pos);
                    reg2 = get_reg();
                    printf("MOV r%d 1\n", reg2);
                    print_op(c);
                    printf("r%d r%d\n", reg1, reg2);
                    printf("MOV [%d] r%d\n", sym->pos, reg1);
                    register_available[reg2] = 1;
                    if(remain_reg()<2&&borrow>sbcount){
                        register_available[reg1] = 1;
                        retval.type = MEMORY;
                        retval.pos = sym->pos;
                        return retval;
                    }
                    else{
                        retval.type = REGISTER;
                        retval.pos = reg1;
                        return retval;
                    }
                    break;
                }
                break;
            default:
                error(SYNTAXERR);
                break;
        }
    } 
    else error(SYNTAXERR);
    return retval;
}

//main function
int main() {
    //freopen("input.txt", "r", stdin);
    // freopen("output_cal.txt", "w", stdout);
    for (int i = 0; i < 8; i++) register_available[i] = 1;
    initTable();
    while (1) statement();
    return 0;
}