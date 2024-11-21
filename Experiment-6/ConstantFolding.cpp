// #include <iostream>
// #include <string>
// #include <unordered_map>

// using namespace std;

// int main() {
//     unordered_map<string, int> variables;
//     int result;

//     cout << "Enter initial values for variables (e.g., a = 5, x = 3, etc.). Type 'done' to finish:\n";

//     while (true) {
//         string var;
//         int value;
//         cout << "Variable name (or 'done' to finish): ";
//         cin >> var;
//         if (var == "done") break;
        
//         cout << "Enter value for " << var << ": ";
//         cin >> value;
//         variables[var] = value;
//     }

//     cout << "\nEnter Three-Address Code operations (e.g., t1 = a + x). Type 'done' to finish:\n";

//     while (true) {
//         string resultVar, op1, op, op2;
//         cout << "Enter operation (or 'done' to finish): ";
//         cin >> resultVar;

//         if (resultVar == "done") break;

//         cin.ignore();
//         cout << "Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': ";
//         cin >> op1 >> op >> op2;

//         if (op == "+") {
//             variables[resultVar] = variables[op1] + variables[op2];
//         } else if (op == "-") {
//             variables[resultVar] = variables[op1] - variables[op2];
//         } else if (op == "*") {
//             variables[resultVar] = variables[op1] * variables[op2];
//         } else if (op == "/") {
//             if (variables[op2] == 0) {
//                 cerr << "Error: Division by zero." << endl;
//                 continue;
//             }
//             variables[resultVar] = variables[op1] / variables[op2];
//         } else {
//             cerr << "Invalid operator. Only +, -, *, / are supported." << endl;
//             continue;
//         }

//         cout << "Result of " << resultVar << " = " << variables[resultVar] << endl;
//     }

//     cout << "\nFinal variable values:\n";
//     for (const auto& [key, value] : variables) {
//         cout << key << " = " << value << endl;
//     }

//     return 0;
// }

#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

int main(){
    unordered_map<string, int> variables;
    int result;

    cout<<"Enter the variables and valued type done to finish: "<<endl;

    while(true){
        string var;
        int value;
        cout<<"Enter the var name: "<<endl;
        cin>>var;
        if(var=="done") break;

        cout<<"Enter value for var "<< var <<endl;
        cin>>value;

        variables[var] = value;
    }

    cout<<"Enter 3A code: " <<endl;

    while(true){
        string op1, op, op2, resultVar;
        cout<<"Enter the operation: " <<endl;
        cin>>resultVar;
        if(resultVar == "done") break;
        cout<<"Enter the op1 op and op2: "<<endl;
        cin>> op1 >> op >> op2;

        if(op == "+"){
            variables[resultVar] = variables[op1] + variables[op2];
        }
        else if(op == "-"){
            variables[resultVar] = variables[op1] - variables[op2];
        }
        else if(op == "*"){
            variables[resultVar] = variables[op1] * variables[op2]; 
        }
        else if(op == "/"){
            if(variables[op2] != 0){
                variables[resultVar] = variables[op1] / variables[op2];
            }
            else{
                cerr <<"OP2 cannot be 0"<<endl;
                continue;
            }
        }
        else{
            cerr<<"Invalid operation"<<endl;
            continue;
        }
        cout << "Result of " << resultVar << " = " << variables[resultVar] << endl;
    }
    cout<<"Final: "<<endl;
    for(const auto&[key, value] : variables){
        cout<<key<<" = "<<value<<endl;
    }
}



// Variable name (or 'done' to finish): a
// Enter value for a: 5
// Variable name (or 'done' to finish): x
// Enter value for x: 3
// Variable name (or 'done' to finish): done

// Enter operation (or 'done' to finish): t1
// Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': a + x
// Result of t1 = 8

// Enter operation (or 'done' to finish): t2
// Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': t1 * x
// Result of t2 = 24

// Enter operation (or 'done' to finish): done



