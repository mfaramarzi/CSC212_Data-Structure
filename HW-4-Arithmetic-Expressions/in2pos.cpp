// I need minus behind number and also space between operands and operatrs

#include<iostream>
#include<stack>  
using namespace std;  


// defines the Boolean function for operator, operand, equalOrhigher precedence and the string conversion function.  
bool IsOperator(char);  //func to check if it is a operator
bool IsOperand(char);  
bool eqlOrhigher(char, char);  //func to check if it has a higher or equal precedence??
string convert(string);  //converting a infix to postfix string

int main(int argc, char *argv[]){

    
string infix_expression, postfix_expression; //Initiate two string variables for infix and postfix??

infix_expression = argv[1];  //I can input using argument instead of cin (infix_expression = argv[1];)

postfix_expression = convert(infix_expression);  

cout<<postfix_expression;

} 



// define the IsOperator() function to validate whether any symbol is operator.  
/* If the symbol is operator, it returns true, otherwise false. */  
bool IsOperator(char c){  
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){

        return true;  
    } 
      
return false;  
}  


// IsOperand() function is used to validate whether the character is operand.  
bool IsOperand(char c){  
    
    if(c >= '0' && c <= '9'){   // Define the character in between 0 to 9. If not, it returns False. */  
        
        return true;  
    }

    else{

    return false;
    }  
    }  

// here, precedence() function is used to define the precedence to the operator.  
int precedence(char op){

if(op == '+' || op == '-'){                  /* it defines the lowest precedence */  

    return 1;  
}

else if (op == '*' || op == '/'){

    return 2;
} 
 
else if(op == '^'){/* exponent operator has the highest precedence */

    return 3;  
}                                 
else{

    return 0; 
}    
} 


// ?????????????????????????????????????????????????????????
/* The eqlOrhigher() function is used to check the higher or equal precedence of the two operators in infix expression. */  
bool eqlOrhigher (char op1, char op2){

    int p1 = precedence(op1);  //output could be 1, 2, or 3

    int p2 = precedence(op2);  //output could be 1, 2, or 3

    if (p1 == p2){ 

        if (op1 == '^' ){//if operator1 is a power

            return false;//meaning two operators are not equal or higher?????
            }
        return true; //what does it mean??? 
    }  
    return  (p1>p2 ? true : false); //if precedence 1 is higher than precedence 2, return true, else, return fals 
}  



/* string convert() function is used to convert the infix expression to the postfix expression of the Stack */  
string convert(string infix){//It return postfix string

    stack <char> S;  //A stack object (s) of type char

    string postfix ="";   //An empty string obj (postfix)

    char ch;  //A character 
    
    S.push( '(' ); //Pushing the openning paranthesis to the stack.Why?????

    infix += ')';  //Adding the closing pranthesis to the infix string.Why?????
    
    for(int i = 0; i<infix.length(); i++){// Iterate i from th efirst to the last char of string infix

        ch = infix[i];  //assing the char
        
        if(ch == ' '){  //if the char is a white space

            continue; //do nothing
        } 

        else if(ch == '('){ //else if it is a openning pranthesis

            S.push(ch); //push it to the stack (s)
        }

        else if(IsOperand(ch) && infix[i-1] == '-' && infix[i+1] == ' '){// else if character is an operand

            postfix += '-';

            postfix += ch;// add it to the postfix string

            postfix += ' ';
        }

        else if(IsOperand(ch) && infix[i-1] == '-' ){// else if character is an operand

            postfix += '-';

            postfix += ch;// add it to the postfix string

        }

        else if(IsOperand(ch) && infix[i+1] == ' '){// else if character is an operand

            postfix += ch;// add it to the postfix string

            postfix += ' ';
        }

        else if(IsOperand(ch) && !IsOperand(infix[i+1])){// else if character is an operand

            postfix += ch;// add it to the postfix string

            postfix += ' ';
        }

        else if(IsOperand(ch)){// else if character is an operand

            postfix += ch;// add it to the postfix string
        }

        else if(IsOperator(ch) && infix[i-1] == ' ' && infix[i+1] == ' '){  //If it is a negative sign, with no space between than and operand, I want it before operand not after!!!!!!!

            while(!S.empty() && eqlOrhigher(S.top(), ch)){

                postfix += S.top();  

                postfix += ' ';

                S.pop();
                }

            S.push(ch);
            }  

        else if(ch == ')'){

            while(!S.empty() && S.top() != '('){

                postfix += S.top();//Assigning the element at the top of stack and put into postfix

                postfix += ' ';

                S.pop(); //Deleting the element atthe top of stack 
                }  
            S.pop();  //Deleting the element atthe top of stack 
            }  
            
        }  
        // postfix.pop_back();
    return postfix;  
}  