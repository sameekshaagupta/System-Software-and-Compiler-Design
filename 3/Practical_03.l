%{
#include<stdio.h>
int sc=0, wc=0, lc=0, cc=0;
%}
%%
[\n] { lc++; cc+= yyleng; }
[ \t] { sc++; cc+= yyleng; }
[^\t\n ]+ { wc++; cc+= yyleng; }
%%
int main(int argc, char* argv[])
{
FILE *inputFile= fopen("source.txt", "r");
if (inputFile == NULL){
perror("Error opening file");
return 1;
}
yyin= inputFile;
yylex();
fclose(inputFile);
printf("The number of lines=%d\n", lc);
printf("The number of spaces=%d\n", sc);
printf("The number of words=%d\n",  wc);
printf("The number of charcters=%d\n", cc);
}
int yywrap()
{
return 1;
}