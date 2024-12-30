#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define REGSIZE 8
#define MEMSIZE 64
#define PRINTERR 0      // whether error() print error message
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

typedef enum _TokenSet {
    UNKNOWN, END, ENDFILE, INT, ID,
    ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN, 
    OR, AND, XOR, INCDEC, ADDSUB_ASSIGN     // new added
} TokenSet;

typedef enum _ErrorType {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, 
    RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

typedef enum _DataType {
    CONST, REGISTER, MEMORY
} DataType;

typedef struct _Symbol {
    char name[MAXLEN];
    DataType type;
    int pos;
    int val;
} Symbol;

typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

TokenSet getToken();
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];
void advance();                 // Get the next token
int match(TokenSet token);      // Test if a token matches the current token
char *getLexeme();              // Get the lexeme of the current token

int regNum = 0;
int regInUse[REGSIZE];
// Symbol reg[REGSIZE];
int memNum = 0;
Symbol mem[MEMSIZE];

void init();
Symbol *searchVar(char *str);
Symbol *getOrSetVar(char *str);
int getReg();
void freeReg(int idx);
BTNode *makeNode(TokenSet tok, const char *lex);
void freeTree(BTNode *root);

// <<-- Lexical Parser
void statement();
BTNode *assign_expr();
BTNode *xor_expr(BTNode* temp);
BTNode *xor_expr_tail(BTNode* left);
BTNode *or_expr(BTNode* temp);
BTNode *or_expr_tail(BTNode* left);
BTNode *and_expr(BTNode* temp);
BTNode *and_expr_tail(BTNode* left);
BTNode *addsub_expr(BTNode* temp);
BTNode *addsub_expr_tail(BTNode* left);
BTNode *muldiv_expr(BTNode* temp);
BTNode *muldiv_expr_tail(BTNode* left);
BTNode *unary_expr(BTNode* temp);
BTNode *factor();
// -->>
void err(ErrorType errorNum);

void printOp(char c);
Symbol codeGen(BTNode *root);           // Evaluate the syntax tree
void printPrefix(BTNode *root);         // Print the syntax tree in prefix


/*======================================================================================
lex implementation
======================================================================================*/

TokenSet getToken() {
    char c;
    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        int i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        if (isalpha(c) || c=='_') error(SYNTAXERR);     // naming error
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = getc(stdin);
        if (c == lexeme[0]) {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else if (c == '=') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        } else {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '&') {
        strcpy(lexeme, "&");
        return AND;
    } else if (c == '|') {
        strcpy(lexeme, "|");
        return OR;
    } else if (c == '^') {
        strcpy(lexeme, "^");
        return XOR;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c=='_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        int i = 1;
        while ((isalnum(c) || c=='_') && i < MAXLEN) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == EOF) return ENDFILE;
    else return UNKNOWN;
}

void advance() {
    curToken = getToken();
}
int match(TokenSet token) {
    if (curToken == UNKNOWN) advance();
    return token == curToken;
}
char *getLexeme() {
    return lexeme;
}


/*======================================================================================
parser implementation
======================================================================================*/

void init() {
    for (int i=0; i<REGSIZE; i++) regInUse[i] = 0;
    for (int i=0; i<MEMSIZE; i++) mem[i].pos = -1;
    strcpy(mem[0].name, "x"); mem[0].val = 0; mem[0].pos = 0; mem[0].type = MEMORY;
    strcpy(mem[1].name, "y"); mem[1].val = 0; mem[1].pos = 4; mem[1].type = MEMORY;
    strcpy(mem[2].name, "z"); mem[2].val = 0; mem[2].pos = 8; mem[2].type = MEMORY;
    memNum = 3;
}

Symbol *searchVar(char *str) {
    for (int i=0; i<MEMSIZE; i++) if (strcmp(mem[i].name, str) == 0) return &mem[i];
    error(UNDEFINED); return NULL;
}
Symbol *getOrSetVar(char *str) {
    for (int i=0; i<MEMSIZE; i++) if (strcmp(mem[i].name, str) == 0) return &mem[i];
    for (int i=0; i<MEMSIZE; i++) 
        if (mem[i].pos == -1) {
            strcpy(mem[i].name, str);
            mem[i].pos = i*4;
            mem[i].type = MEMORY;
            memNum++;
            return &mem[i];
        }
    error(RUNOUT); return NULL;
}
int getReg() {
    for (int i=0; i<REGSIZE; i++)
        if (!regInUse[i]) {
            regInUse[i] = 1;
            regNum++;
            return i;
        }
    error(RUNOUT); return 0;
}
void freeReg(int idx) {
    regInUse[idx] = 0;
    regNum--;
}

BTNode *makeNode(TokenSet tok, const char *lex) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lex);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// statement := ENDFILE | END | expr END
void statement() {
    BTNode *retp = NULL;
    if (match(ENDFILE)) {
        if (mem[0].type == CONST) printf("MOV r0 %d\n", mem[0].val);
        else printf("MOV r0 [0]\n");
        if (mem[1].type == CONST) printf("MOV r1 %d\n", mem[1].val);
        else printf("MOV r1 [4]\n");
        if (mem[2].type == CONST) printf("MOV r2 %d\n", mem[2].val);
        else printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            Symbol rt = codeGen(retp);
            if (rt.type == REGISTER) freeReg(rt.pos);   // !!!
            // printPrefix(retp);
            freeTree(retp);
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

// assign_expr := ID ASSIGN assign_expr | ID ADDSUB_ASSIGN assign_expr | or_expr
BTNode *assign_expr() {
    BTNode *retp = NULL;
    if (match(ID)) {
        BTNode *left = makeNode(ID, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
        } else if (match(ADDSUB_ASSIGN)) {
            retp = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
        } else 
            retp = xor_expr(left);
    } else
        retp = xor_expr(NULL);
    return retp;
}

// xor_expr := and_expr xor_expr_tail
BTNode *xor_expr(BTNode *temp) {
    BTNode* node = or_expr(temp);
    return xor_expr_tail(node);
}

// xor_expr_tail := XOR and_expr xor_expr_tail | NiL
BTNode *xor_expr_tail(BTNode *left) {
    if (match(XOR)) {
        BTNode *node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr(NULL);
        return xor_expr_tail(node);
    } else 
        return left;
}

// or_expr := xor_expr or_expr_tail
BTNode *or_expr(BTNode* temp) {
    BTNode *node = and_expr(temp);
    return or_expr_tail(node);
}

// or_expr_tail := OR xor_expr or_expr_tail | NiL
BTNode *or_expr_tail(BTNode *left) {
    if (match(OR)) {
        BTNode *node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = or_expr(NULL);
        return or_expr_tail(node);
    } else
        return left;
}

// and_expr := addsub_expr and_expr_tail;
BTNode *and_expr(BTNode *temp) {
    BTNode *node = addsub_expr(temp);
    return and_expr_tail(node);
}

// and_expr_tail := AND addsub_expr and_expr_tail | NiL
BTNode *and_expr_tail(BTNode *left) {
    if (match(AND)) {
        BTNode *node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr(NULL);
        return and_expr_tail(node);
    } else
        return left;
}

// addsub_expr := muldiv_expr addsub_expr_tail
BTNode *addsub_expr(BTNode *temp) {
    BTNode *node = muldiv_expr(temp);
    return addsub_expr_tail(node);
}

// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left) {
    if (match(ADDSUB)) {
        BTNode *node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr(NULL);
        return addsub_expr_tail(node);
    } else 
        return left;
}

// muldiv_expr := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(BTNode *temp) {
    BTNode *node = unary_expr(temp);
    return muldiv_expr_tail(node);
}

// muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode *left) {
    if (match(MULDIV)) {
        BTNode *node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return muldiv_expr_tail(node);
    } else
        return left;
}

// unary_expr := ADDSUB unary_expr | factor
BTNode *unary_expr(BTNode *temp) {
    if (temp) return temp;      // !!!
    if (match(ADDSUB)) {
        BTNode *node = makeNode(ADDSUB, getLexeme());
        node->left = makeNode(INT, "0");
        node->right = unary_expr(NULL);
        return node;
    } else 
        return factor();
}

// factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor() {
    BTNode *retp = NULL;
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        retp->val = atoi(getLexeme());
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID)) {
            retp->left = makeNode(ID, getLexeme());
            // right NOT USED: unary operator
        } else error(SYNTAXERR);
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (!match(RPAREN)) error(MISPAREN);
    } else error(NOTNUMID);
    advance();      // !!!
    return retp;
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
                fprintf(stderr, "out of mem\n");
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

/*======================================================================================
codeGen implementation
======================================================================================*/

void printOp(char c) {
    if (c == '+') printf("ADD ");
    else if (c == '-') printf("SUB ");
    else if (c == '*') printf("MUL ");
    else if (c == '/') printf("DIV ");
    else if (c == '&') printf("AND ");
    else if (c == '|') printf("OR ");
    else if (c == '^') printf("XOR ");
}

Symbol codeGen(BTNode *root) {
    Symbol retval={}, lv, rv;
    Symbol *sym;
    int reg1, reg2;
    if (root != NULL) {
        char c = root->lexeme[0];
        switch (root->data) {
            case ID:
                retval = *searchVar(root->lexeme);
                break;
            case INT:
                retval.type = CONST;
                retval.val = root->val;
                break;
            case ASSIGN:
                if (root->left->data != ID) error(SYNTAXERR);
                rv = codeGen(root->right);
                sym = getOrSetVar(root->left->lexeme);
                if (rv.type == CONST) {
                    sym->type = CONST;
                    sym->val = rv.val;
                    retval = *sym;
                } else if (rv.type == MEMORY) {
                    reg1 = getReg();
                    printf("MOV r%d [%d]\n", reg1, rv.pos);
                    printf("MOV [%d] r%d\n", sym->pos, reg1);
                    if (regNum > REGSIZE-2) {
                        freeReg(reg1);
                        retval = *sym;
                    } else {
                        retval.type = REGISTER;
                        retval.pos = reg1;
                    }
                } else if (rv.type == REGISTER) {
                    printf("MOV [%d] r%d\n", sym->pos, rv.pos);
                    retval.type = REGISTER;
                    retval.pos = rv.pos;
                }
                break;
            case MULDIV: case ADDSUB: case AND: case XOR: case OR:
                lv = codeGen(root->left);
                rv = codeGen(root->right);
                if (lv.type == CONST) {
                    if (rv.type == CONST) {
                        retval.type = CONST;
                        if (c == '+') retval.val = lv.val + rv.val;
                        else if (c == '-') retval.val = lv.val - rv.val;
                        else if (c == '*') retval.val = lv.val * rv.val;
                        else if (c == '&') retval.val = lv.val & rv.val;
                        else if (c == '^') retval.val = lv.val ^ rv.val;
                        else if (c == '|') retval.val = lv.val | rv.val;
                        else if (c == '/') {
                            if (rv.val == 0) error(DIVZERO);
                            retval.val = lv.val / rv.val;
                        }
                    } else if (rv.type == MEMORY) {
                        reg1 = getReg();
                        reg2 = getReg();
                        printf("MOV r%d %d\n", reg1, lv.val);
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        freeReg(reg2);
                        retval.type = REGISTER;
                        retval.pos = reg1;
                    } else if (rv.type == REGISTER) {
                        reg1 = getReg();
                        printf("MOV r%d %d\n", reg1, lv.val);
                        printOp(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        freeReg(rv.pos);
                        retval.type = REGISTER;
                        retval.pos = reg1;
                    }
                } else if (lv.type == MEMORY) {
                    reg1 = getReg();
                    printf("MOV r%d [%d]\n", reg1, lv.pos);
                    if (rv.type == CONST) {
                        reg2 = getReg();
                        printf("MOV r%d %d\n", reg2, rv.val);
                        if (c == '/' && rv.val == 0) error(DIVZERO);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        freeReg(reg2);
                    } else if (rv.type == MEMORY) {
                        reg2 = getReg();
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        freeReg(reg2);
                    } else if (rv.type == REGISTER) {
                        printOp(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        freeReg(rv.pos);
                    }
                    // ?!?!?! TEMP_MEMORY ?
                    retval.type = REGISTER;
                    retval.pos = reg1;
                } else if (lv.type == REGISTER) {
                    if (rv.type == CONST) {
                        reg1 = getReg();
                        printf("MOV r%d %d\n", reg1, rv.val);
                        if (c == '/' && rv.val == 0) error(DIVZERO);
                        printOp(c);
                        printf("r%d r%d\n", lv.pos, reg1);
                        freeReg(reg1);
                    } else if (rv.type == MEMORY) {
                        reg1 = getReg();
                        printf("MOV r%d [%d]\n", reg1, rv.pos);
                        printOp(c);
                        printf("r%d r%d\n", lv.pos, reg1);
                        freeReg(reg1);
                    } else if (rv.type == REGISTER) {
                        printOp(c);
                        printf("r%d r%d\n", lv.pos, rv.pos);
                        freeReg(rv.pos);
                    }
                    retval = lv;
                }
                break;
            case ADDSUB_ASSIGN:
                if (root->left->data != ID) error(UNDEFINED);
                rv = codeGen(root->right);
                sym = getOrSetVar(root->left->lexeme);
                if (sym->type == CONST) {
                    if (rv.type == CONST) {
                        if (c == '+') sym->val = sym->val + rv.val;
                        else if (c == '-') sym->val = sym->val - rv.val;
                        retval.type = CONST;
                        retval.val = sym->val;
                        return retval;  // ? return AT NOW
                    } else if (rv.type == MEMORY) {
                        reg1 = getReg();
                        reg2 = getReg();
                        printf("MOV r%d %d\n", reg1, sym->val);
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        printf("MOV [%d] r%d\n", sym->pos, reg1);
                        sym->type = MEMORY;
                        freeReg(reg2);
                    } else if (rv.type == REGISTER) {
                        reg1 = getReg();
                        printf("MOV r%d %d\n", reg1, sym->val);
                        printOp(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                        printf("MOV [%d] %d\n", sym->pos, reg1);
                        sym->type = MEMORY;
                    }
                } else if (sym->type == MEMORY) {
                    reg1 = getReg();
                    printf("MOV r%d [%d]\n", reg1, sym->pos);
                    if (rv.type == CONST) {
                        reg2 = getReg();
                        printf("MOV r%d %d\n", reg2, rv.val);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        freeReg(reg2);
                    } else if (rv.type == MEMORY) {
                        reg2 = getReg();
                        printf("MOV r%d [%d]\n", reg2, rv.pos);
                        printOp(c);
                        printf("r%d r%d\n", reg1, reg2);
                        freeReg(reg2);
                    } else if (rv.type == REGISTER) {
                        printOp(c);
                        printf("r%d r%d\n", reg1, rv.pos);
                    }
                    printf("MOV [%d] r%d\n", sym->pos, reg1);
                }
                if (regNum > REGSIZE-2) {
                    freeReg(reg1);
                    retval = *sym;
                } else {
                    retval.type = REGISTER;
                    retval.pos = reg1;
                }
                break;
            case INCDEC:
                if (root->left->data != ID) error(SYNTAXERR);
                sym = searchVar(root->left->lexeme);
                if (sym->type == CONST) {
                    if (c == '+') sym->val++;
                    else if (c == '-') sym->val--;
                    retval = *sym;
                } else if (sym->type == MEMORY) {
                    reg1 = getReg();
                    reg2 = getReg();
                    printf("MOV r%d [%d]\n", reg1, sym->pos);
                    printf("MOV r%d 1\n", reg2);
                    printOp(c);
                    printf("r%d r%d\n", reg1, reg2);
                    printf("MOV [%d] r%d\n", sym->pos, reg1);
                    freeReg(reg2);
                    if (regNum > REGSIZE-2) {
                        freeReg(reg1);
                        retval = *sym;
                    } else {
                        retval.type = REGISTER;
                        retval.pos = reg1;
                    }
                }
                break;
            default:
                error(SYNTAXERR);
        }
    } else error(SYNTAXERR);
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*======================================================================================
main
======================================================================================*/

int main() {
    init();
    while (1) statement();
}
