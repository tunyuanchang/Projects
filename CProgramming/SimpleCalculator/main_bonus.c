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
    //add tokens
    AND, OR, XOR, INCDEC
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Store the cur register
int reg = 0;
// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);

// for parser
#define TBLSIZE 64
// print error message while calling error()
#define PRINTERR 0

// Call this macro to print error message and exit the program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
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
// Check the existence of a variable
void table_exist(char *str);
// Add a variable to the table
void table_add(char *str);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);

//grammar
void statement(void);
BTNode *assign_expr(void);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr(void);
BTNode *factor(void);

// Print error message and exit the program
void err(ErrorType errorNum);
// for codeGen
// Judge the graph of the syntax tree
int judge(BTNode *root);
// Check the syntax tree exist variable
int check(BTNode *root);
// Evaluate the syntax tree
long long int cal(BTNode *root);
// Print assembly code
void evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);

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
        lexeme[0] = c;
        char ch = fgetc(stdin);
        if(ch == c){
            lexeme[1] = ch;
            lexeme[2] = '\0';
            ch = fgetc(stdin);
            if(ch == c) {
                error(SYNTAXERR);
            }
            else {
                ungetc(ch,stdin);
                return INCDEC;
            }
        }
        ungetc(ch, stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
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
    }  else if (c == '&'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    } else if (c == '^'){
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
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

void table_exist(char *str) {
    int i = 0;
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return ;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    error(NOTFOUND);
}

void table_add(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return ;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    sbcount++;
    return ;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    if(tok == INT) node->val = atoi(lexe);
    else node->val = 0;
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

//statement := END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;
    if (match(ENDFILE)) {
        printf("MOV r0 [0]\n");
		printf("MOV r1 [4]\n");
		printf("MOV r2 [8]\n");
		printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            reg = 0;  //initial
            evaluateTree(retp);
            freeTree(retp);
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}
//assign_expr := ID ASSIGN assign_expr | or_expr
BTNode *assign_expr(void){
    BTNode *retp = NULL, *left = NULL;
    if(match(ID)){
        char c;
        while ((c = fgetc(stdin)) == ' ' || c == '\t');
        if(c == '=') {
            left = makeNode(ID, getLexeme());
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
            return retp;
        }
        else{
            ungetc(c,stdin);
            return retp = or_expr();
        }
    } else {
        return retp = or_expr();
    }
}
//or_expr := xor_expr or_expr_tail
BTNode *or_expr(void){
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}
//or_expr_tail := OR xor_expr or_expr_tail | NiL
BTNode *or_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}
//xor_expr := and_expr xor_expr_tail
BTNode *xor_expr(void){
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}
//xor_expr_tail := XOR and_expr xor_expr_tail | NiL
BTNode *xor_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}
//and_expr := addsub_expr and_expr_tail
BTNode *and_expr(void){
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}
//and_expr_tail := AND addsub_expr and_expr_tail | NiL
BTNode *and_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}
//addsub_expr := muldiv_expr addsub_expr_tail
BTNode *addsub_expr(void){
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}
// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    } else {
        return left;
    }
}
//muldiv_expr := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(void){
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}
//muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else {
        return left;
    }
}
//unary_expr := ADDSUB unary_expr | factor
BTNode *unary_expr(void){
    BTNode *retp = NULL;
    if(match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        advance();
        retp->right = unary_expr();
        return retp;
    } else {
        return factor();
    }
}
//factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL;
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)){
        retp = makeNode(INCDEC, getLexeme());
        retp->left = NULL;
        advance();
        if(match(ID)){
            retp->right = makeNode(ID, getLexeme());
            advance();
        }
        else {
            error(NOTNUMID);
        }
    }  else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else
        error(NOTNUMID);

    return retp;
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        //fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                //fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                //fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                //fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                //fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                //fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                //fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                //fprintf(stderr, "syntax error\n");
                break;
            default:
                //fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}
/*============================================================================================
codeGen implementation
============================================================================================*/
int check(BTNode *root){
    if(root != NULL) {
        if(root->data == ID) return 1;
        if(check(root->right)) return 1;
        if(check(root->left)) return 1;
    }
    return 0;
}

int judge(BTNode *root) {
    if(root != NULL) {
        switch(root->data) {
            case ID:
            case INT:
            case INCDEC:
                return 1;
                break;
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND:
                return 2;
                break;
        }
    }
    return 0;
}
long long int cal(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    if (root != NULL) {
        switch (root->data) {
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND:
                lv = cal(root->left);
                rv = cal(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if(rv == 0) error(DIVZERO);
                    retval = lv / rv;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                } else if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void evaluateTree(BTNode *root) {
    int retval = 0, rv = 0, lv = 0;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                table_exist(root->lexeme);
                for (int i = 0; i < TBLSIZE; i++) {
				    if (strcmp(root->lexeme, table[i].name) == 0) {
					    printf("MOV r%d [%d]\n", reg++, 4 * i);
					    break;
				    }
			    }
                break;
            case INT:
                retval = atoi(root->lexeme);
                printf("MOV r%d %d\n", reg++, retval);
                break;
            case ASSIGN:
                evaluateTree(root->right);
                table_add(root->left->lexeme);
                for (int i = 0; i < TBLSIZE; i++) {
				    if (strcmp(root->left->lexeme, table[i].name) == 0) {
					    printf("MOV [%d] r%d\n", 4 * i, reg - 1);
                        //reg--  not essential
					    break;
				    }
			    }
                break;
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND:
                /*evaluateTree(root->left);
                evaluateTree(root->right);*/

                if(judge(root->left) == 1 && judge(root->right) == 2) {
                    evaluateTree(root->right);
                    evaluateTree(root->left);
                } else {
                    evaluateTree(root->left);
                    evaluateTree(root->right);
                }

                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n",reg - 2, reg - 1);
                    reg--;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    if(judge(root->left) == 1 && judge(root->right) == 2) {
                        printf("SUB r%d r%d\n", reg - 1, reg - 2);
                        printf("MOV r%d r%d\n", reg - 2, reg - 1);
                    }
                    else{
                        printf("SUB r%d r%d\n", reg - 2, reg - 1);
                    }
                    /*printf("SUB r%d r%d\n", reg - 2, reg - 1);*/
                    reg--;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n",reg - 2, reg - 1);
                    reg--;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if(check(root->right)){
                        if(judge(root->left) == 1 && judge(root->right) == 2) {
                            printf("DIV r%d r%d\n", reg - 1, reg - 2);
                            printf("MOV r%d r%d\n", reg - 2, reg - 1);
                        }
                        else{
                            printf("DIV r%d r%d\n", reg - 2, reg - 1);
                        }
                        /*printf("DIV r%d r%d\n", reg - 2, reg - 1);*/
                        reg--;
                    }
                    else {
                        if(cal(root->right) == 0) {
                            error(SYNTAXERR);
                        }
                        else {
                            if(judge(root->left) == 1 && judge(root->right) == 2) {
                                printf("DIV r%d r%d\n", reg - 1, reg - 2);
                                printf("MOV r%d r%d\n", reg - 2, reg - 1);
                            }
                            else{
                                printf("DIV r%d r%d\n", reg - 2, reg - 1);
                            }
                            /*printf("DIV r%d r%d\n", reg - 2, reg - 1)*/
                            reg--;
                        }
                    }
                } else if (strcmp(root->lexeme, "|") == 0) {
                    printf("OR r%d r%d\n",reg - 2, reg - 1);
                    reg--;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    printf("XOR r%d r%d\n",reg - 2, reg - 1);
                    reg--;
                } else if (strcmp(root->lexeme, "&") == 0) {
                    printf("AND r%d r%d\n",reg - 2, reg - 1);
                    reg--;
                }
                break;
            case INCDEC:  //regarded as var = var +- 1
                evaluateTree(root->right);
                table_add(root->right->lexeme);
                if (strcmp(root->lexeme, "++") == 0) {
                    //ADD 1
                    printf("MOV r%d %d\n", reg, 1);
				    printf("ADD r%d r%d\n", reg - 1, reg);
				    //ASSIGN
				    for (int i = 0; i < TBLSIZE; i++) {
					    if (strcmp(root->right->lexeme, table[i].name) == 0) {
						    printf("MOV [%d] r%d\n", 4 * i, reg - 1);
						    break;
					    }
				    }
                } else if (strcmp(root->lexeme, "--") == 0) {
                    //SUB 1
                    printf("MOV r%d %d\n", reg, 1);
				    printf("SUB r%d r%d\n", reg - 1, reg);
				    //ASSIGN
				    for (int i = 0; i < TBLSIZE; i++) {
					    if (strcmp(root->right->lexeme, table[i].name) == 0) {
						    printf("MOV [%d] r%d\n", 4 * i, reg - 1);
						    break;
					    }
				    }
                }
                break;
        }
    }
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
int main() {
    //freopen("input.txt", "w", stdout);
    initTable();
    while (1) {
        statement();
    }
    return 0;
}
