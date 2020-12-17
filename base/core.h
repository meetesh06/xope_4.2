#include <stdio.h>
#ifndef _CORE_H
#define _CORE_H

#define MAX_BUF 100
extern char tmp[MAX_BUF];
extern char token_buf[MAX_BUF];
extern char Look;
extern FILE *opened_file;
extern FILE *output_file;
extern int LineNo;

void GetChar();

void Error(char *s);
void Abort(char *s);
void Expected(char *s);
void Match(char x);

void Newline();
void SkipTab();
void SkipSpaces();

int IsAlpha(char c);
int IsDigit(char c);
int IsAddop(char c);
int IsBoolean(char c);
int IsOrop(char c);
int IsRelop(char c);

char GetName();
char GetNameVar();
char GetNamePrint();
char *GetNum();
int GetBoolean();

void Emit(char *);
void EmitLn(char *);

void Init(FILE *, FILE *);
// void InitTable();

char *NewLabel();
void PostLabel(char *);

#endif
