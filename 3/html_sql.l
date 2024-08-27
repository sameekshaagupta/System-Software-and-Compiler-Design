%{
#include<stdio.h>
int html_tags;
int sql_tags=0;
int start_tags=0;
int end_tags=0;
%}

%%
"<"[a-zA-Z]+">" {
   start_tags++;
   printf("the start tag is %n",yytext);}
"</"[a-zA-Z]+">";
  {end_tags++;
  printf("the end tag is %n",yytext); }
"INSERT"|"SELECT"|"UPDATE"|"ALTER"|"DROP"
{
  sql_tags++;
  printf("the SQL tag is: %s\n",yytext);
}
%%

int main(int argc, char* argv[]){
	FILE *input=fopen("sql_html.txt","r");
	if(!input){
           person("Error opening file");
	   return 1;
   	}
	yyin= input;//Set the input file for the Flex
	yylex();
	fclose(input);
	printf("The total number of SQL tags are: %d\n", sql_tags);
	printf("The total number of HTML tags aare: %d\n", html_tags);
	return 0;

}


int yywrap(){
    return 1;
}



