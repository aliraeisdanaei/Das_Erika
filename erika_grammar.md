# Erika Grammar 

This is the grammar for the erika language. 

## Parser Tokens

<pre>
"if"    "elif"  "else"
"while" "return" 
"{"     "}"
"("     ")"
";"     ","
"="     "-"     "+"     "*"     "/"
"=="    "&"     "|"
"i32"   "bit"   "char" 
"funktion"      "haupt"
"anfang"        "end"

IDENTIFIER      INT_LITERAL     STR_LITERAL
</pre>


## Grammar

**S** -> anfang FUNKTION end

**FUNKTION** -> MAINFUNKTION
**MAINFUNKTION** -> funktion haupt (ARGUMENTS) { STATEMENT }

**ARGUMENTS** -> 
e 
| VAR_DECLARATION, ARGUMENTS

**VAR_DECLARATION** -> 
i32 IDENTIFIER 
| bit IDENTIFIER 
| char IDENTIFIER

**STATEMENT** -> 
if ( EXPRESSION ) { STATEMENTS } 
| while ( EXPRESSION ) { STATEMENTS }
| return EXPRESSION;
| VAR_DECLARATION; 
| EXPRESSION;
| STATEMENT STATEMENT

**EXPRESSION** ->
INT_LITERAL
| STR_LITERAL
| IDENTIFIER
| ( EXPRESSION )
| EXPRESSION = EXPRESSION
| EXPRESSION + EXPRESSION
| EXPRESSION - EXPRESSION
| EXPRESSION * EXPRESSION
| EXPRESSION / EXPRESSION
| EXPRESSION & EXPRESSION
| EXPRESSION | EXPRESSION





