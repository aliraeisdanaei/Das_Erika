#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>



std::vector <std::string> key_tokens={
    "if", "elif", "else",
    "while", "return", "output",
    "{", "}",
    "(", ")",
    ";", ",",
    "=", "-", "+", "*", "/",
    "==", "&", "|",
    "i32", "bit", "char",
    "funktion", "haupt",
    "anfang", "end"
};
std::vector <std::string> identifier_tokens;

void print_vector(std::vector <std::string> vec){
    for (int i=0; i<vec.size(); i++){
        std::cout << vec[i] << '\t';
    }

    std::cout << "\n";
}

std::vector<std::string>  preprocesser (std::ifstream source_file){
    //removes the comments
    //splits the semicolons
    //splits () into each parenthesis
    //puts everything onto a vector of potential tokens
    std::vector <std::string> potential_tokens;
   
    std::string word; 
    bool comment = false;       //this boolean will be true when there has been a comment openned

    while (source_file >> word){
        if (word.compare("/*") == 0){
            // start of comment
            comment = true;
        }else if (word.compare("*/") == 0){
            comment =  false;
        }else if(! comment){
            if(word.find(';') != -1){
                //a semicolon was found push semi colon and word seperately
                potential_tokens.push_back(word.substr(0, word.find(';')));
                potential_tokens.push_back(";");
            }else if(word.compare("()" )== 0){
                //special case for the empty parenthesis
                //they each need to be individual characters
                potential_tokens.push_back("(");
                potential_tokens.push_back(")");
            }else{
                potential_tokens.push_back(word);
            }

            
        }
    }
    return potential_tokens;
}


bool check_VarDeclaration(std::string word){
    if (word.compare("i32") == 0){
        return true;
    }
    if (word.compare("bit") == 0){
        return true;
    }
    if (word.compare("compare") == 0){
        return true;
    }
    return false;
}

void pushVarDecl(std::vector<std::string> potential_tokens, std::vector<std::string> & tokens, int  & i){
    //new variable declarations
    if(check_VarDeclaration(potential_tokens[i])){
        //check if an identifier is available after this word
        if(i == potential_tokens.size() -1){
            std::cout << "Invalid variable declaratation. Decleration cannot be at the end of file.\n";
            exit(4);
        } else if (std::find(key_tokens.begin(), key_tokens.end(), potential_tokens[i + 1]) != key_tokens.end()){
            //used an already valid key token as a variable declaration
            //the distinction is made between key tokens and identifier tokens
            //in arguments of a function the name of a previously defined variable can be used
            std::cout << "Invalid variable declaration. Key word: " << potential_tokens[i+1] << " used as identifier.\n";

            exit(4);
        }else{
            // std::cout << potential_tokens[i+1] << " adding this variable\n";
            //add the identifier/ variable name to the vector of valid identifier tokens
            identifier_tokens.push_back(potential_tokens[i+1]);
            //push it onto to the tokens and increment i
            tokens.push_back(potential_tokens[i+1]);
            i++;
        } 

    }
}

bool pushLiterals(std::string word, std::vector<std::string> & tokens){
    //checks for any integer literals
    for(char c : word){
        if( ! isdigit(c)){
            return false;
        }
    }
    // std::cout << "This string is a digit: " << word << '\n';
    tokens.push_back(word);
    return true;

}

std::vector<std::string> tokenizer(std::vector<std::string> potential_tokens){
    //checks for valid tokens
    //adds new tokens for identifiers
    //allows for int literals

    std::vector<std::string> tokens;
    for (int i=0; i < potential_tokens.size(); i++){
        //checks if the given potential token is part of the valid tokens
        
        if(std::find(key_tokens.begin(), key_tokens.end(), potential_tokens[i]) != key_tokens.end()){
            //valid token
            tokens.push_back(potential_tokens[i]);

            pushVarDecl(potential_tokens, tokens, i);


        }else if(std::find(identifier_tokens.begin(), identifier_tokens.end(), potential_tokens[i]) != identifier_tokens.end()){
            //valid identifier token
            tokens.push_back(potential_tokens[i]);
        }
        else if (! pushLiterals(potential_tokens[i], tokens)){
            // invalid token
            std::cout << "Syntax Error. Not a keyword: " << potential_tokens[i] << "\n";
            exit (5);
        }

    }
    return tokens;
}

std::ifstream open_source(std::string filename){
    std::ifstream source_file;
    source_file.open(filename);

    if (! source_file.is_open()){
        std::cout << "Lexer could not open source file. \n";
        exit(2);
    }
    return source_file;
}


int main(int argc, char *argv[]){

    if (argc < 2 ){
        std::cout << "No file was given to Lexer. \n";
        exit(1);
    }

    std::string filename = argv[1];
    
    std::vector <std::string> tokens= tokenizer(preprocesser(open_source(filename)));
   
    
    print_vector(tokens);

    std::cout << "IDENTIFIER TOKENS:\n";
    print_vector(identifier_tokens);


    return 0;
}


