#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include <math.h>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

string trimWhiteSpace(string& input){
    string trimmed = "";
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' '){
            continue;
        }
        trimmed += input[i];
    }
    return trimmed;
}

stack<string> turingMachine(string& trimmed){
    stack<string> value;
    stack<string> operand;
    
    string temporaryVal = "";
    string temporaryOp = "";
    int parenthesisCount = 0;
    for (int i = 0; trimmed[i] != '\0'; i++) {

        //Sets up value stacks
        if (trimmed[i] != '(' && trimmed[i] != ')' && trimmed[i] != '*' && trimmed[i] != '/' && trimmed[i] != '+' && trimmed[i] != '-'){
            temporaryVal += trimmed[i];
        }
        else{
            if(temporaryVal != ""){
                value.push(temporaryVal);
                temporaryVal = "";
            }
        }
        

        //Sets up operand stacks and logic for moving operand stack data to value stack
        if (trimmed[i] == '(' || trimmed[i] == ')' || trimmed[i] == '*' || trimmed[i] == '/' || trimmed[i] == '+' || trimmed[i] == '-'){
            temporaryOp = trimmed[i];
            //((3+3*4)+3)
            if (trimmed[i] == '('){
                operand.push(temporaryOp);
            }
            else{
                if (trimmed[i] == '-' || trimmed[i] == '+'){
                    //Logic for precedence
                    if (operand.top() == "*" || operand.top() == "/"){
                        while(operand.top() == "*" || operand.top() == "/")
                            value.push(operand.top());
                            operand.pop();
                        operand.push(temporaryOp);
                    }
                    //pushes +, - operands to stack
                    else{
                        operand.push(temporaryOp);
                    }
                }

                //pushes *, / operands to stack
                if (trimmed[i] == '*' || trimmed[i] == '/'){
                    operand.push(temporaryOp);
                }

                //logic if ending of parenthesis is found
                if (trimmed[i] == ')'){
                    while(operand.top() != "("){
                        value.push(operand.top());
                        operand.pop();
                    }
                    operand.pop();
                }
            }
        }

    }

    while(!operand.empty()){
        if(temporaryVal!= ""){
            value.push(temporaryVal);
        }
        value.push(operand.top());
        operand.pop();
    }

    
    return value;
}

//Reverses the postfix stack
stack<string> recursion(stack<string>& postFixStack){
    stack<string> postFixRecursion;
    while (!postFixStack.empty()){
        postFixRecursion.push(postFixStack.top());
        postFixStack.pop();
    }
    return postFixRecursion;
}

float evaluatePostFix(stack<string>& postfix){
    string postfixString = "";
    string temp = "";
    stack<float> evaluation;
    float conversion, answer, float1, float2;
    
    while(!postfix.empty()){
        postfixString += postfix.top();
        postfix.pop();
    }
    cout << "string: " << postfixString << endl;
    for (int i = 0; postfixString[i] != '\0'; i++) {
        if (postfixString[i] == '*' || postfixString[i] == '/' || postfixString[i] == '+' || postfixString[i] == '-'){
            //gets top 2 of evaluation stack if an operator is scanned
            float1 = evaluation.top();
            evaluation.pop();
            float2 = evaluation.top();
            evaluation.pop();

            //Does the evaluation for the top 2 floats in stack
            //Proceeds to push the evaluation back into the stack for further evaluation
            if (postfixString[i] = '*'){
                answer = float1 * float2;
                evaluation.push(answer);
            }
            if (postfixString[i] = '/'){
                answer = float1 / float2;
                evaluation.push(answer);
            }
            if (postfixString[i] = '+'){
                answer = float1 + float2;
                evaluation.push(answer);
            }
            if (postfixString[i] = '-'){
                answer = float1 - float2;
                evaluation.push(answer);
            }
            continue;
        }
        //adds to the temp string for conversion, should not allow *,/,+, and - to be inside
        temp += postfixString[i];
        //Uses project 1 to convert an f literal then pushes to float stack
        if(postfixString[i] == 'f' || postfixString[i] == 'F'){
            //Use project 1 dfa to convert, INPUT NEEDS TO BE EDITED IN PROJECT 1
            //conversion = "Proj1(temp)"
            evaluation.push(conversion);
            temp = "";

        }
    
    }
    return answer;
}

//unit testing
int main(){
    string input;
    float answer;
    cout << "Enter an expression with valid f literals: " << endl;
    //TEMPORARY TEST CASE
    input = "((1.2f + 4.5f * 3.4e3f)* 2.34f - 2.3f)*6.5f";
    //cin.getline(input, 100); WE ALSO NEED TEST CASES FOR INVALID INPUTS
    cout<< input<<endl;
    //Trims whitespace from input
    string trimmed = trimWhiteSpace(input);
    //creates a postfix expression within a stack
    stack<string> postfix = turingMachine(trimmed);
    //Uses recursion to make it easier to apply postfix expression into the evaluation process.
    postfix = recursion(postfix);
    answer = evaluatePostFix(postfix);
    cout << answer << endl;
    return 0;
}

