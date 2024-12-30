#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    AND,OR,XOR
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
// #define error(errorNum) { \
//     if (PRINTERR) \
//         fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
//     err(errorNum); \
// }
#define error(errorNum) { \
    if (PRINTERR) \
        printf("EXIT 1\n"); \
    exit(0); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str);
// Set the value of a variable
int setval(char *str, int val);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);
BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *assign_expr(void);
BTNode *assign_expr_tail(BTNode *left);
void statement(void);
// Print error message and exit the program
void err(ErrorType errorNum);


// for codeGen
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// myfunction
int exist_ID(BTNode* root);        // 找除式有沒有變數
// Print the syntax tree in prefix
void printPrefix(BTNode *root);

int r;          // 紀錄下一個可以放的register位置
/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {  
        char prev=c;
        c=fgetc(stdin);
        if(c=='+'||c=='-'||c=='=')    // += 和 ++... 都被我視為assign
        {
            if(c=='=')
            {
                lexeme[0]=prev,lexeme[1]=c,lexeme[2]=0;
                return ASSIGN;
            }
            else if(c==prev)
            {
                lexeme[0]=lexeme[1]=c,lexeme[2]=0;
                return ASSIGN;
            }
            else 
            {
                ungetc(c,stdin);
            }
        }
        else ungetc(c,stdin);
        lexeme[0] = prev;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '&') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    } else if (c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c)||c=='_') {
        while (isdigit(c)||isalpha(c)||c=='_' && i < MAXLEN) {      // 讀至不是變數名稱
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);       // 讓符號可以在之後重新讀取
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
    //printf("%d\n",curToken);
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {       // 在此MOV
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
        {
            printf("MOV r%d [%d]\n",r,i*4); r++;
            return table[i].val;
        }  
    error(RUNOUT);        // 找不到
    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    printf("MOV r%d [%d]\n",r,sbcount*4); r++;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {    // 在此MOV
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            printf("MOV [%d] r%d\n",i*4,r-1);
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    printf("MOV [%d] r%d\n",sbcount*4,r-1);
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
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
        //printf("free: %s\n",root->lexeme);
        free(root);
    }
}

// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  |
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (!match(ASSIGN)) {
            retp = left;
        } else {
            if(!strcmp(getLexeme(),"++")){
                retp=makeNode(ASSIGN,getLexeme()); retp->val=1;  // 告訴program去找variable原值
                retp->left=left,retp->right=makeNode(ADDSUB,"+");
                retp->right->left=makeNode(ID,left->lexeme),retp->right->right=makeNode(INT,"1");
                advance();
            } 
            else if(!strcmp(getLexeme(),"--")){
                retp=makeNode(ASSIGN,getLexeme()); retp->val=1;
                retp->left=left,retp->right=makeNode(ADDSUB,"-");
                retp->right->left=makeNode(ID,left->lexeme),retp->right->right=makeNode(INT,"1");
                advance();
            }
            else retp=left;
        }
    } else if (match(ASSIGN)) {
        retp=makeNode(ASSIGN,getLexeme());
        advance();
        if(!match(ID)) error(UNDEFINED);
        retp->left=makeNode(ID,getLexeme());
        if(!strcmp(retp->lexeme,"++")) retp->right=makeNode(ADDSUB,"+");
        else if(!strcmp(retp->lexeme,"--")) retp->right=makeNode(ADDSUB,"-");
        retp->right->left=makeNode(ID,getLexeme());
        retp->right->right=makeNode(INT,"1");
        advance();
    } else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme());
            advance();
        } else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            advance();
        } else if (match(LPAREN)) {
            advance();
            retp->right = assign_expr();
            if (match(RPAREN))
                advance();
            else
                error(MISPAREN);
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return term_tail(node);
    } else {
        return left;
    }
}

// expr := term expr_tail
BTNode *expr(void) {
    BTNode *node = term();
    return expr_tail(node);
}

// expr_tail := ADDSUB term expr_tail | NiL
BTNode *expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    } else {
        return left;
    }
}
// Below are my bitwise function
BTNode *and_expr(void) {
    BTNode *node = expr();
    return and_expr_tail(node);
}
BTNode *and_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}
BTNode *or_expr(void) {
    BTNode *node = and_expr();
    return or_expr_tail(node);
}
BTNode *or_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}
BTNode *xor_expr(void) {
    BTNode *node = or_expr();
    return xor_expr_tail(node);
}
BTNode *xor_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = or_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}
BTNode *assign_expr(void) {
    BTNode *node = xor_expr();
    return assign_expr_tail(node);
}
BTNode *assign_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ASSIGN)) {
        node = makeNode(ASSIGN, getLexeme());
        advance();
        node->left = left;
        if(!strcmp(node->lexeme,"+=")){
            node->right=makeNode(ADDSUB,"+");
            node->right->left=makeNode(ID,left->lexeme); node->right->right=assign_expr();
        } else if(!strcmp(node->lexeme,"-=")){
            node->right=makeNode(ADDSUB,"-");
            node->right->left=makeNode(ID,left->lexeme); node->right->right=assign_expr();
        } else if(!strcmp(node->lexeme,"=")) node->right = assign_expr();
        else error(UNDEFINED);
        return node;
    } else {
        return left;
    }
}

// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\nEXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            evaluateTree(retp);
            freeTree(retp);
            // debug
            //for(int i=0;table[i].name[0]!=0;i++) printf("%s=%d\n",table[i].name,table[i].val);
            //printf("----------------\n");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
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
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                //printf("origin z=%d ,z=%d\n",table[2].val,retval);
                break;
            case INT:
                retval = atoi(root->lexeme);
                printf("MOV r%d %d\n",r,retval); r++;
                break;
            case ASSIGN:
                if(root->left->data!=ID) error(UNDEFINED);     // 左邊不是一個變數就error
                
                //printf("right value=%d\n",rv);
                if(root->val){
                    retval=getval(root->left->lexeme);
                    rv = evaluateTree(root->right);
                    setval(root->left->lexeme,rv);
                    r--;
                }
                else rv = evaluateTree(root->right),retval = setval(root->left->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case OR:
            case XOR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                //printf("%s %d\n",root->left->lexeme,root->left->val);
                //printf("lv=%d, rv=%d\n",lv,rv);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("SUB r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    printf("MUL r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0){
                        if(exist_ID(root->right)) rv=1;
                        else error(DIVZERO);
                    }
                    retval = lv / rv;
                    printf("DIV r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                    printf("AND r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                    printf("OR r%d r%d\n",r-2,r-1); r--;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                    printf("XOR r%d r%d\n",r-2,r-1); r--;
                }                 
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

int exist_ID(BTNode* root){
    if(root->data==ID) return 1;
    else if(root->left!=NULL&&exist_ID(root->left)) return 1;
    else if(root->right!=NULL&&exist_ID(root->right)) return 1;
    else return 0;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*============================================================================================
main
============================================================================================*/

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    initTable();
    //printf(">> ");
    while (1) {
        r=0;
        statement();
        //printf("OK\n");
    }
    return 0;
}
