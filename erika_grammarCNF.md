# Erika Grammar in Chomsky Normal Form

This is used to optimize the work of the parser.

## Single Terminal Rules
IF -> "if"
ELIF -> "elif"
ELSE -> "else"
WHILE -> "while"
RETURN -> "return"
OUTPUT -> "output"
BSO -> "{"
BSC -> "}"
BRO -> "("
BRC -> ")"
SEMIC -> ";"
COMMA -> ","
EQ -> "="
MINUS -> "-"
PLUS -> "+"
MUL -> "*"
DIV -> "/"
DEQ -> "=="
AND -> "&"
OR -> "|"
I32 -> "i32"
BIT -> "bit"
CHAR -> "char"
FUNKTION -> "funktion"
HAUPT -> "haupt"
ANFANG -> "anfang"
END -> "end"

## Other Rules
**S** -> ANFANG REST1
REST1 -> FUNKTION REST2
REST2 -> MAINFUNKTION END

**FUNKTION** -> FUNKTION FUNK_REST1
FUNK_REST1 -> IDENTIFIER FUNK_REST2
FUNK_REST2 -> BRO FUNK_REST3
FUNK_REST3 -> ARGUMENTS FUNK_REST4

**MAINFUNKTION** -> FUNKTION MFUNK_REST1
MFUNK_REST1 -> HAUPT MFUNK_REST2
MFUNK_REST2 -> FUNK_REST2
