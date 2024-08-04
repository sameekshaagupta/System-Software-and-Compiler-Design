%{

%}
%%
"while"|"if"|"else"|"const"|"final"|"break"|"for" {printf("keyword \n", yytext);}

[a-zA-Z]+[a-zA-Z0-9]* {printf(" identifier\n",yytext);}
">"|"<"|"<="|">="|"=="|"!="|"=" {printf ("Relational operator\n");}
[0-9]+ {printf("Number \n");}
","|"("|")"|";"|"{"|"}" {printf ("seprator \n");}

%%

int main(){
 printf("Enter a lexeme\n");
 yylex();
}

int yywrap(){
	return 1;
}