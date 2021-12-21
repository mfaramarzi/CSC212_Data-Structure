#include<iostream>
#include<cmath>
#include<stack>//Using stack library
using namespace std;  

using namespace std;

int scanNum(char ch); //A func returning int from each char

int isOperator(char ch);//Check char is an operator

int isOperand(char ch);//check char is an operand

int operation(int a, int b, char op);//doing operation

int postfixEval(string postfix);//Find the result of postfix

//Is seg fault due to spaces or?? This program should consider spaces

int main(int argc, char *argv[]) {

   string post = argv[1];

   cout << postfixEval(post);
}

int scanNum(char ch){

   int num = int(ch)-int('0');
   
   return num; }


int isOperator(char ch){

   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^'){

      return 1;    //character is an operator
   }
   return -1;   //not an operator
}


int isOperand(char ch) {

   if(ch >= '0' && ch <= '9'){

      return 1;//character is an operand
      }   
      
   return -1;   //not an operand
}


int operation(int a, int b, char op) {
   //Perform operation
   if(op == '+'){

       return b+a;
   }
      
   else if(op == '-'){

      return b-a;
      }
      
   else if(op == '*'){

      return b*a;
      }

   else if(op == '/'){

      return b/a;
      }

   else if(op == '^'){

      return pow(b,a);//find b^a
      } 

   else{

      return 1;//return negative infinity
      } 
}


int postfixEval(string postfix) {

   int a, b;
   

   stack<int> stk;

   string::iterator it;

   for(it=postfix.begin(); it!=postfix.end(); it++) {

      string num = "";

      if(isOperand(*it) == 1 && isOperand(*(it + 1)) == 1 && isOperand(*(it +2) == 1 )) {//a three digit
//program doesnt run this if statement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         num += *it;

         num += *(it +1);

         num += *(it +2);


         // std::cout<<stoi(num);// printed -10
         // std::cout<<"test";

         stk.push(stoi(num));

         it = it + 2;//skip the next 2 i
      }

      else if(*it == '-' && isOperand(*(it + 1)) == 1 && isOperand(*(it + 2)) == 1 && isOperand(*(it +3) == 1 )) {//a '-' three digit
//program doesnt run this if statement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         num += *it;

         num += *(it +1);

         num += *(it +2);

         num += *(it +3);

         // std::cout<<stoi(num);// printed -10
         // std::cout<<"test";

         stk.push(stoi(num));

         it = it + 3;//skip the next 2 i
      }

      else if(*it == '-' && isOperand(*(it + 1)) == 1 && isOperand(*(it +2) == 1 )) {//a '-' two digit
//program doesnt run this if statement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         num += *it;

         num += *(it +1);

         num += *(it +2);

         

         // std::cout<<stoi(num);// printed -10
         // std::cout<<"test";

         stk.push(stoi(num));

         it = it + 2;//skip the next 2 i
      }

      else if(*it == '-' && isOperand(*(it +1) == 1 ) && *(it +2) == ' ' ) {//a '-' and one digit

         num += *it;

         num += *(it +1);

         // std::cout<<stoi(num);
         // std::cout<<"test";

         stk.push(stoi(num));

         it = it + 2;//skip the next i
      }

      else if(isOperand(*it) == 1 && isOperand(*(it +1)) == 1 && *(it +2) == ' ' ) {//two digit 

         num += *it ;
         num += *(it +1);

         // std::cout<<stoi(num); it prints 20 and 30 and 2. 2 is extra

         stk.push(stoi(num));

          it = it + 2;//skip the next 2 i
         }

      else if(isOperand(*it) == 1 && *(it +1) == ' ' ) {//one digit 

         num += *it ;

         // std::cout<<stoi(num); 
         stk.push(stoi(num));

         it = it + 1;//skip the next i
      }

      

      else if( isOperand(*(it) ) == 1 ) {//one digit space both sides *it == ' '  &&  

         stk.push(scanNum(*it));
      }

      // else if(isOperand(*it) == 1 && isOperand(*(it +1) == 1 && *(it + 2) == ' ')) {//two digit space both sides && *(it -1) == ' '

      //    num += *it;

      //    num += *(it +1);

      //    stk.push(stoi(num));

      //    it++;//skip the next i
      // }

      

      //read elements and perform postfix evaluation
      else if(isOperator(*it) == 1) {// && *it++ == ' ' && *it-- == ' '

         a = stk.top();

         stk.pop();//pop first element from stack,

         b = stk.top();

         stk.pop();//pop second element from the stack

         stk.push(operation(a, b, *it));

         if (*(it + 1) == ' '){

            it = it + 1;
         }
          
      }
   }
   // make a string  of output
   // while(true){
      return stk.top();
      // stk.pop();

   // }
   
   }
   