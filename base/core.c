#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 26
int LCount = 0;
char labelName[MAX_BUF];
char token_buf[MAX_BUF];
// int Table[TABLE_SIZE];
int LineNo;

FILE *opened_file;
FILE *output_file;

char tmp[MAX_BUF];
char Look;

/* Helper Functions */

char uppercase(char c) {
  return (c & 0xDF);
}

void GetChar() {
  // Look = getchar();
  Look = fgetc(opened_file);
  /* printf("Getchar: %c\n", Look); */
}

void Error(char *s) {
  printf("\nError at line: %d\n", LineNo);
  printf("Error: %s.\n\n", s);
}

void Abort(char *s) {
  Error(s);
  fclose(output_file);
  fclose(opened_file);
  exit(1);
}


void Expected(char *s) {
  sprintf(tmp, "%s Expected", s);
  Abort(tmp);
}


void Match(char x) {
  if(Look == x) {
    GetChar();
  } else {
    sprintf(tmp, "' %c ' ",  x);
    Expected(tmp);
  }
}



void Newline() {
  while(Look == '\n') {
    GetChar();
  }
}

void SkipTab() {
  while(Look == '\t' || Look == 9) {
    GetChar();
  }
}

void SkipSpaces() {
  while(Look == ' ') {
    GetChar();
  }
}

int IsAlNum(char c)
{
    return IsAlpha(c) || IsDigit(c);
}

int IsAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
} 

int IsDigit(char c) {
  return (c >= '0') && (c <= '9');
}

int IsWhite(char c) {
    return (c == ' ') || (c == '\t');
}

int IsAddop(char c) {
  return (c == '+') || (c == '-');
}

int IsOrop(char c) {
  return strchr("|~", c) != NULL;
}

int IsRelop(char c) {
  return strchr("=!<>", c) != NULL; 
}

int IsBoolean(char c) {
  c = uppercase(c);
  return (c == 'T' || c == 'F' );
}

void SkipWhite() {
  while (IsWhite(Look)) {
    GetChar();
  }
}

int GetBoolean() {
  char c = Look;
  if( !IsBoolean(Look)) {
    sprintf(tmp, "Boolean");
    Expected(tmp);
  }
  GetChar();
  return uppercase(c);
}

char GetName() {
  char c = Look;
  if( !IsAlpha(Look)) {
    sprintf(tmp, "Name");
    Expected(tmp);
  }
  GetChar();
  return uppercase(c);
}

char GetNamePrint() {
  char c = Look;
  //if( !IsAlpha(Look) && Look != 92 ) {
  //  sprintf(tmp, "Name");
  //  Expected(tmp);
  //}
  GetChar();
  return c;
}

char GetNameVar() {
  char c = Look;
  if( !(Look >= 'a' && Look <= 'z')) {
    Expected("Invalid variable name man!");
  }
  GetChar();
  return c;
}

char* GetNum() {
  char *value = token_buf;

  if( !IsAlNum(Look)) {
    Expected("Integer");
  }
  while (IsDigit(Look)) {
    *value = Look;
    value++;

    GetChar();
  }

  SkipWhite();

  *value = '\0';
  return token_buf;
}

void Emit(char *s) {
  fprintf(output_file, "\t%s", s);
  // printf("\t%s", s);
}

void EmitLn(char *s) {
  Emit(s);
  fprintf(output_file, "\n");
}

void Init(FILE *fp_in, FILE *fp_out) {
  opened_file = fp_in;
  output_file = fp_out;
  LineNo = 0;
  LCount = 0;
  // InitTable();
  GetChar();
}

// void InitTable() {
//   int i;
//   for (i = 0; i < TABLE_SIZE; i++) {
//       Table[i] = 0;
//   }
// }

char *NewLabel() {
  sprintf(labelName, "L%02d", LCount);
  LCount ++;
  return labelName;
}

void PostLabel(char *label) {
  Emit(label);
  EmitLn(":");
  // printf("%s:\n", label);
}

