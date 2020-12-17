// ; Author: Meetesh Kalpesh Mehta
// ; Compiler Name: XOPE
// ; year: 2020
// ; version: 0.4.2
// ; version_changes:
// ; 1) Code refactoring
// ;
// ; comment: Refactoring the code
//
// LICENSE INFORMATION
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <unistd.h>

#include "base/core.h"
#include "base/headers.h"
int debugging = 0;
char* YEAR = "2020";
char* VERSION = "0.4.2";
char* CHANGES ="\
; 1) If else bridging\n\
; 2) Fix infinite loop possibility in Loop\n\
; 3) Semi-conditional Break statement for Loops\n\
; 4) 4) Added support for comments\
";
char* COMMENT ="\
Refactoring the code\
";

// 1) MATH FUNCTIONS
void Add();              // Addition { + }
void Substract();        // Subtraction { - }
void Multiply();         // Multiplication { * }
void Divide();           // Division { / }
void Modulus();          // Modulus { % }
void OR();               // OR { | }
void XOR();              // XOR { ^ }
// ******************************************
// 2) BOOLEAN FUNCTIONS  
void GTE();              // Greater than | Greater than or equal to { >= }
void LTE();              // Less than | Less than or equal to { <= }
void EQ();               // Equals { == }
void NEQ();              // Not Equals { != }
// ******************************************
// 3) LOGICAL FRAMEWORK
void StartCompiler();    // Start the compiler
void Block();            // A Basic Block
// DOIF
void Bridge();           // IF-ELSE Bridging { EL | EL() }
void DoIf();             // Start IF-ELSE { I() | If() | E }
// END-DOIF
void Comment();          // Handle Comments { // }
void While();            // While Loop { W() | While() }
// PRINTVARIABLE
void PrintVariableIntermediate();
void PrintStatement();
void PrintVariable();    // Printf function { >"". | >a. | >a.| | >""+a. | >.|  }
// END-PRINTVARIABLE
void Loop();             // Standard Loop { L() | Loop() }
void CompleteLoop();     // Complete Loop Prematurely { C. | Complete. }
void ScanVariable();     // Read Value into variable { <a. | Read a. }
void Other();            // Expression Parsing
// ******************************************
// 3) NESTING EXPRESSION
void Assignment();       // Assignment, 
void BoolExpression();
void BoolTerm();
void NotFactor();
void BoolFactor();
void Relation();
void Expression();
void Term();
void Factor();
void Ident();
// ******************************************
// 1) MATH FUNCTIONS
void Add() {
  Match('+');
  Term();
  EmitLn("pop rbx");
  EmitLn("add rax, rbx");
}

void Substract() {
  Match('-');
  Term();
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("sub rax, rbx");
}

void Multiply() {
  Match('*');
  Factor();
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("imul rbx");
} 

void Divide() {
  Match('/');
  Factor();
  EmitLn("mov rdx, 0; because god says so");
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("idiv rbx");
}

void Modulus() {
  Match('%');
  Factor();
  EmitLn("mov rdx, 0; because god says so");
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("idiv rbx");
  EmitLn("mov rax, rdx");
}
// ******************************************
// 2) LOGICAL FRAMEWORK
void GTE() {
  int equal = 0;
  Match('>');
  if(Look == '=') {
    Match('=');
    equal = 1;
  }
  Expression();
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("cmp rax, rbx");
  (equal == 0) ? EmitLn("setg al") : EmitLn("setge al");
}
void LTE() {
  int equal = 0;
  Match('<');
  if(Look == '=') {
    Match('=');
    equal = 1;
  }
  Expression();
  EmitLn("mov rbx, rax");
  EmitLn("pop rax");
  EmitLn("cmp rax, rbx");
  (equal == 0) ? EmitLn("setl al") : EmitLn("setle al");

  // EmitLn("cmp %eax, (%esp)");
  // EmitLn("setl %al");
  // EmitLn("addl $4, %esp");     /* recover the stack */
}
void EQ() {
  Match('=');
  Match('=');
  Expression();
  EmitLn("pop rbx");
  EmitLn("cmp rax, rbx");
  EmitLn("sete al");
}
void NEQ() {
  Match('!');
  Match('=');
  Expression();
  EmitLn("pop rbx");
  EmitLn("cmp rax, rbx");
  EmitLn("setne al");
}
void OR() {
  Match('|');
  BoolTerm();
  EmitLn("pop rbx");
  EmitLn("or rax, rbx");
}
void XOR() {
  Match('^');
  BoolTerm();
  EmitLn("pop rbx");
  EmitLn("xor rax, rbx");
}
// ******************************************
// 3) LOGICAL FRAMEWORK
void StartCompiler() {
  Block();
  if (Look != 'E') {
    Expected("End");
  }
  EmitLn("mov rax, 60");
  EmitLn("mov rdi, 0");
  EmitLn("syscall");
}
void Block() {
  while (! strchr("E", Look)) {
    LineNo++;
    Newline();
    SkipSpaces();
    SkipTab();
    SkipSpaces();
    Newline();
    if(debugging == 1) printf("\tLook:%c\n",Look); 
    if(Look == 'E') return;
    switch (Look) {
      case 'I':
        DoIf();
        break;
      case '/':
        Comment();
        break;
      case 'W':
        While();
        break;
      case '>':
        Match('>');
        PrintVariable();
        if(Look == '|') {
          // shortcut for newline :)
          Match('|');
          EmitLn("call _newLine");
        }
        break;
      case 'L':
        Loop();
        break;
      case 'C':
        CompleteLoop();
        break;
      case '<':
        Match('<');
        ScanVariable();
        if(Look == '|') {
          // shortcut for newline :)
          Match('|');
          EmitLn("call _newLine");
        }
        break;
      case 'R':
        Match('R');
        if(Look == 'e') {
          Match('e');
          Match('a');
          Match('d');
        }
        Match(' ');
        ScanVariable();
        if(Look == '|') {
          // shortcut for newline :)
          Match('|');
          EmitLn("call _newLine");
        }
        break;
      default:
        Other();
        break;
    }
  }
}
// DOIF
void Bridge(char *LF) {
  char L1[MAX_BUF];
  if(Look == '(') {
    strcpy(L1, NewLabel());
    Match('(');
    BoolExpression();
    Match(')');
    EmitLn("test al, al");
    sprintf(tmp, "jz %s", L1);
    EmitLn(tmp);
    Newline();
    Block();
    Match('E');
    // if the condition was true, jump to the END
    sprintf(tmp, "jmp %s", LF);
    EmitLn(tmp);
    PostLabel(L1);
    if(Look == 'L') {
      // Else statement    
      Match('L');
      Newline();
      Bridge(LF);
    }
  } else {
    Block();
  }
}
void DoIf() {
  char L1[MAX_BUF];
  char LF[MAX_BUF];
  // generate a new label
  strcpy(LF, NewLabel());
  strcpy(L1, NewLabel());
  Match('I');
  if(Look == 'f') {
    Match('f');
  }
  Match('(');
  BoolExpression();
  Match(')');
  EmitLn("test al, al");
  sprintf(tmp, "jz %s", L1);
  EmitLn(tmp);
  Newline();
  Block();
  Match('E');  
  // If the condition was true, then just exit to the end
  sprintf(tmp, "jmp %s", LF);
  EmitLn(tmp);
  PostLabel(L1);
  if (Look == 'L') {
    // Else statement    
    Match('L');
    Newline();
    // If the condition failed, we come here
    Bridge(LF);
  }
  PostLabel(LF);
}
// END-DOIF
void Comment() {
  Match('/');
  Match('/');
  while(Look != '\n') {
    GetChar();
  }
}
void While() {
  char L1[MAX_BUF];
  char L2[MAX_BUF];
  // generate a new label
  strcpy(L1, NewLabel());
  strcpy(L2, NewLabel());
  Match('W');
  if(Look == 'h') {
    Match('h');
    Match('i');
    Match('l');
    Match('e');
  }
  EmitLn("push rbx"); // Allow for nesting of loops
  EmitLn("mov rbx, 1"); // Setting the trigger
  Match('(');
  PostLabel(L1);
  EmitLn("push rbx"); // PRESERVE TRIGGER VALUE
  BoolExpression(); // NOTE: Bool Expression evaluation changes the rbx value
  EmitLn("pop rbx"); // RESTORE TRIGGER VALUE
  Match(')');
  Newline();
  EmitLn("test al, al");
  sprintf(tmp, "jz %s", L2); // EXIT ON FAILED CONDITION
  EmitLn(tmp);
  EmitLn("push rbx"); // Save the trigger
  Block();
  Match('E');
  EmitLn("pop rbx"); // a trigger for conditional break statement
  EmitLn("cmp rbx, 0");
  sprintf(tmp, "je %s", L2); // Consider this loop as last
  EmitLn(tmp);
  sprintf(tmp, "jmp %s", L1);
  EmitLn(tmp);
  PostLabel(L2);
  EmitLn("pop rbx"); // Allow for nesting of loops
}
// PRINTVARIABLE
void PrintVariableIntermediate() {
  switch(Look) {
    case '"':
      PrintStatement();
      break;
    default:
      Expression();
      EmitLn("call _printRAX");
  }
}
void PrintStatement() {
  Match('"');
  char c;
  int offset = 0;
  int escape_value = 0;
  EmitLn("mov rcx, printText;");
  while(Look != '"') {
    c = GetNamePrint();
    if(c == 92) {
      c = GetNamePrint();
      switch (c) {
        case 'b': // BS
          escape_value = 8;
          break;
        case 't': // TAB
          escape_value = 9;
          break;
        case 'n': // LF
          escape_value = 10;
          break;
        case 'v': // VT
          escape_value = 11;
          break;
        case 'f': // FF
          escape_value = 12;
          break;
        case 'r': // CR
          escape_value = 13;
          break;
        case 'e': // ESC
          escape_value = 27;
          break;
        case '+': // Heart
          EmitLn("mov bl, 10");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 126");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);
          
          EmitLn("mov bl, 'E'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'N'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'G'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'A'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'G'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'E'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'D'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, ' '");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'T'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);
          
          EmitLn("mov bl, 'O'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, ' '");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'R'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'A'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'T'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);
          
          EmitLn("mov bl, 'A'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'T'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'T'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'A'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'C'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 'K'");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 126");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          EmitLn("mov bl, 10");
          sprintf(tmp, "mov [rcx + %d], bl",offset++);
          EmitLn(tmp);

          escape_value = 0;
          break;
        default:
          Expected("Invalid Escape Sequence");
          break;
      }
      sprintf(tmp, "mov bl, %d", escape_value);
      EmitLn(tmp);
      sprintf(tmp, "mov [rcx + %d], bl",offset++);
      EmitLn(tmp);
      // EmitLn("mov [escape], bl");
      // EmitLn("mov rsi, escape");
      // EmitLn("call _escape");
      // printf("\nEscape Sequence %c\n", c);
    } else {
      sprintf(tmp, "mov bl, '%c'", c);
      EmitLn(tmp);
      sprintf(tmp, "mov [rcx + %d], bl",offset++);
      EmitLn(tmp);
    }
  }
  sprintf(tmp, "mov rdx, %d",offset);
  EmitLn(tmp);
  EmitLn("call _printText");
  Match('"');
  if(Look == '+') {
    Match('+');
    PrintVariableIntermediate();
  } else {
    return;
  }
}
void PrintVariable() {
  switch(Look) {
    case '"':
      PrintStatement();
      break;
    case '.':
      break;
    default:
      Expression();
      EmitLn("call _printRAX");
  }
  Match('.');
}
// END-PRINTVARIABLE
void Loop() {
  char L1[MAX_BUF];
  char L2[MAX_BUF];
  // generate new labels
  strcpy(L1, NewLabel());
  strcpy(L2, NewLabel());
  Match('L');
  if(Look == 'o') {
    Match('o');
    Match('o');
    Match('p');
  }
  EmitLn("push rax"); // PREVENTS, premature closure of parent loop
  EmitLn("push rbx"); // PREVENTS, invalidation of parent trigger value
  // The line above prevents the unwanted loss of data of parent loops
  Match('(');
  Expression(); // At this point rax has the number of times loop has to be executed
  Match(')');
  // FOR TESTING: EmitLn("mov rcx, rax"); // Store this value in a temporary location, circulate in the loop later
  Newline();
  EmitLn("mov rbx, 1"); // Trigger for premature break
  sprintf(tmp, "%s:", L1);
  EmitLn(tmp);
  EmitLn("cmp rax, 0");
  sprintf(tmp, "jle %s", L2);
  EmitLn(tmp);
  EmitLn("push rbx");
  EmitLn("push rax");
  Block();
  EmitLn("pop rax");
  EmitLn("dec rax"); 
  EmitLn("pop rbx"); // Check if there was a premature exit trigger
  EmitLn("cmp rbx, 0");
  sprintf(tmp, "je %s", L2); // Consider this loop as last
  EmitLn(tmp);
  sprintf(tmp, "jmp %s", L1); // Loop Continue
  EmitLn(tmp);
  sprintf(tmp, "%s:", L2);
  EmitLn(tmp);
  EmitLn("pop rbx"); // Allow for nesting of loops
  EmitLn("pop rax"); // Allow for nesting of loops
  Match('E');
}
void CompleteLoop() {
  Match('C');
  if(Look == 'o') {
    Match('o');
    Match('m');
    Match('p');
    Match('l');
    Match('e');
    Match('t');
    Match('e');
  }
  EmitLn("pop rbx");
  EmitLn("mov rbx, 0");
  EmitLn("push rbx");
  Match('.');
}
void ScanVariable() {
  char var = GetNameVar();
  EmitLn("call _getInputInteger");
  EmitLn("mov rcx, variables");
  sprintf(tmp, "mov [rcx+%d], rax", (var - 'a')*8 );
  EmitLn(tmp);
  Match('.');
}
void Other() {
  Assignment();
  if(IsAlpha(Look)) {
    Abort("Expected a valid operation between variables");
  }
  // if(Look == '/') {
  //   Match('/');
  //   while(Look != '\n') {
  //     GetChar();
  //   }
  // }
  Match('.');
}
// ******************************************
// 4) NESTING EXPRESSION
void Assignment() {
  char name = GetNameVar();
  Match('=');
  BoolExpression();
  sprintf(tmp, ";VAR %c", name);
  EmitLn(tmp);
  EmitLn("mov rcx, variables ; pointer to the variables");
  sprintf(tmp, "mov [rcx+%d], rax", (name - 'a')*8 );
  EmitLn(tmp);
  // printf("\n\n Assignment Done %c\n", Look);
}
void BoolExpression() {
  BoolTerm();
  while (IsOrop(Look)) {
    EmitLn("push rax");
    switch (Look) {
      case '|':
        OR();
        break;
      case '~':
        XOR();
        break;
      default:
        break;
    }
  }
}
void BoolTerm() {
  NotFactor();
  while(Look == '&') {
    EmitLn("push rax");
    Match('&');
    NotFactor();
    EmitLn("pop rbx");
    EmitLn("and rax, rbx");
  }
}
void NotFactor() {
  if (Look == '!') {
    Match('!');
    BoolFactor();
    EmitLn("xor rax, -1");
    EmitLn("inc rax");
  } else {
    BoolFactor();
  }
}
void BoolFactor() {
  if (IsBoolean(Look)) {
    if (GetBoolean() == 'T') {
      EmitLn("mov rax, 1");
    } else {
      EmitLn("xor rax, rax");
    }
  } else {
    Relation();
  }
}
void Relation() {
  Expression();
  if (IsRelop(Look)) {
    EmitLn("push rax");
    switch (Look) {
      case '=':
        EQ();
        break;
      case '!':
        NEQ();
        break;
      case '<':
        LTE();
        break;
      case '>':
        GTE();
        break;
    }
  }
}
void Expression() {
  if(IsAddop(Look))
    EmitLn("xor rax, rax");
  else
    Term();

  while (strchr("+-", Look)) {
    EmitLn("push rax");
    switch(Look) {
      case '+':
        Add();
        break;
      case '-':
        Substract();
        break;
      default:
        Expected("Addop");
    }
  }
}
void Term() {
  Factor();
  while (strchr("*/%", Look)) {
    EmitLn("push rax");
    switch(Look) {
      case '*':
        Multiply();
        break;
      case '/':
        Divide();
        break;
      case '%':
        Modulus();
        break;
      default:
        Expected("Mulop");
    }
  }
}
void Factor() {
  if(Look == '(') {
    Match('(');
    Expression();
    Match(')');
  } else if(Look == '-') {
    Match('-');
    sprintf(tmp,"mov rax, %s", GetNum());
    EmitLn(tmp);
    EmitLn("neg rax");
  } else if (IsAlpha(Look)) {
    Ident();
  } else {
    if(Look == '+') { // probably some idiot is going to try this, rather fix it now
      Match('+');
    }
    sprintf(tmp,"mov rax, %s", GetNum());
    EmitLn(tmp);
  }
}
void Ident() {
  char name = GetNameVar();
  if (Look == '(') {
    Match('(');
    Match(')');
    sprintf(tmp, "call %c // TODO, HANDLE FUNCTION CALL", name);
    EmitLn(tmp);
  } else {
      EmitLn("mov rcx, variables ; pointer to the variables");
      sprintf(tmp, "mov rax, [rcx+%d]", (name - 'a')*8 );
      EmitLn(tmp);
  }
}

// ******************************************
// FUNCTION TO GET FILE EXTENSION
const char *get_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main(int argc, char *argv[]) {
  FILE *fp_i, *fp_o;
  char cwd[PATH_MAX];
  char cwd_temp[PATH_MAX];
  char final[PATH_MAX];
  char filename[PATH_MAX];
  int compileOnly = 0;

  if (argc == 1) {
    printf("XOPE COMPILER VERSION %s \n",VERSION);
    printf("Error: No file entered, usage: xope filename.xope [OPTIONS]\n");
    exit(1);
  }

  const char *ext = get_ext(argv[1]);
  // check file extension
  if( strcmp(ext, "meetesh") == 0) {
    printf("Error: File is too awesome to be run xoxoxoxo <3, use .xope instead!\n");
    exit(1);
  }

  if( strcmp(ext, "xope") != 0) {
    printf("Error: Invalid file extension \"%s\", expected .xope file!\n", ext);
    exit(1);
  }
  // getting the filename
  strncpy(filename, argv[1], strlen(argv[1]) - 5);
  
  if(argc == 3) {
    if( strcmp(argv[2], "-d") == 0) {
      debugging=1;
    } else if( strcmp(argv[2], "-c") == 0) {
      compileOnly=1;
    }
  }
  
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    sprintf(cwd_temp,"%s/xope.asm",cwd);
    sprintf(cwd,"%s/%s",cwd,argv[1]);
  } else {
    perror("Error: Could not get the current working directory, check permissions!\n");
    exit(1);
  }

  fp_i = fopen(cwd,"r");
  fp_o = fopen(cwd_temp,"w");
  if(fp_i == NULL || fp_o == NULL) {
    perror("Error in opening file\n");
    return(-1);
  }

  Init(fp_i, fp_o);
  Emit(getHeaderDeclaration(VERSION, CHANGES, COMMENT));
  Emit(header_declaration);

  StartCompiler();

  fclose(fp_i);
  fclose(fp_o);
  printf("\nCOMPILATION COMPLETED SUCCESSFULLY\n");
  if(compileOnly) {
    printf("(Compilation Only mode) Exiting\n");
    printf("Use this command to assemble and link:\nnasm -f elf64 -o xope.o xope.asm && ld xope.o -o FILENAME\n");
    return 0;
  }
  printf("\nASSEMBLING AND LINKING\n");
  printf("\nTASK COMPLETED, STARTING THE PROGRAM\n");
  if(debugging == 0) system("clear");
  if(debugging) {
    sprintf(final,"nasm -f elf64 -o xope.o xope.asm && ld xope.o -o %s && ./%s", filename, filename);
    system(final);
  } else {
    sprintf(final,"nasm -f elf64 -o xope.o xope.asm && rm xope.asm && ld xope.o -o %s && rm xope.o && ./%s", filename, filename);
    system(final);
  }
  return 0;
}
//
// THE END, MY FRIEND
// YOU HAVE WRITTEN A PROGRAMMING LANGUAGE IN C
// Regards,
//   Meetesh Mehta
// Inspired by, Let's Build a Compiler, by Jack Crenshaw