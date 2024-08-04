%{
 int n = 0;
%}
%%

"while"|"for"|"else"|"const"|"final"|"break"|"if" {n++;printf("keyword \n",yytext); printf("The length of token is: %d \n",yyleng);}

[a-zA-Z]+[a-zA-Z0-9]* { n++;printf("identifier \n",yytext);printf("The length of token is: %d \n",yyleng);}

">"|"<"|"<="|"|"|">="|"=="|"!="|"=" { n++;printf("Relatonal Operator \n");printf("The length of token is: %d \n",yyleng);}

[0-9]+ {n++;printf("numbers \n");printf("The length of token is: %d \n",yyleng);}

","|"("|")"|";"|"{"|"}" {n++;printf ("seprator \n");printf("The length of token is: %d \n",yyleng);}
%%

int main(){
	printf("Enter the Lexeme \n");
	yylex();
	printf("Total tokens are: %d \n",n);
}
int yywrap(){
return 1;
}