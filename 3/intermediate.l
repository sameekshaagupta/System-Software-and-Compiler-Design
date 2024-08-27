%{
#include<stdio.h>
int nc =0;
FILE *yyout_comment;
FILE *yyout_code;
int in_comment = 0;
%}
%%
"/"{
in_comment =1
fprint(yyout_comment, "%s" , yytext)
};
"/"{
if(in_comment){
in_comment=0;
fprint(yyout_comment, "%s\n", yytext );

}
nc++;
};
"//".*{
if(in_comment)
fprint(yyout_comment, "%s\n ", yytext);
nc++;

};
.|\n{
if(!in_comment)
fprint(yyout_code, "%s", yytext);
else
fprintf(yyout_comment, "%s",yytext);

}

%%

int main()
{
yyin = fopen("a_ref.txt", "r");
yyout_comment= fopen("program.c","w");
yylex();
fclose(yyin);
fclose(yyout_code);
return 0;

}
int yywrap()
{
return 1;

}



