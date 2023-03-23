#include <iostream>
using namespace std;


//the input should be in format of 2 + 3 = 5 and only addition and subtraction are allowed

int exp(int x, int y) {
    int h = 0;
    int result = 1;
    if (y == 0) {
        return result;
    }
    else {
        while (h < y) {
            h++;
            result *= x;
        }
        return result;
    }
}

int str_to_int(string g) {
    int sum_int = 0;
    string numbers = "0123456789";
    for (int i = 0; i <= int(g.length() - 1); i++) {
        if ((g.at(i) == '+' ) || (g.at(i) == '-')) {
            continue;
        }
        else {
            for (int p = 0; p <= 9; p++) {
                if ((g.at(i) == '+') || (g.at(i) == '-')) {
                    if (g.at(i) == numbers.at(p)) {
                        sum_int += p * exp(10, (g.length() - i ));
                    }
                }
                else {
                    if (g.at(i) == numbers.at(p)) {
                        sum_int += p * exp(10, (g.length() - i - 1));
                    }
                }

            }
        }
    }
    if (g.at(0) == '-') {
        sum_int *= -1;
    }
    return sum_int;
}

bool inputcheck(string y) {
    int count_oper = 0, count_equal = 0;
    for (int i = 0; i <= int(y.length() - 1); i++) {
        if ((y.at(i) != '0' && y.at(i) != '1' && y.at(i) != '2' && y.at(i) != '3' &&
            y.at(i) != '4' && y.at(i) != '5' && y.at(i) != '6' && y.at(i) != '7' &&
            y.at(i) != '8' && y.at(i) != '9' && y.at(i) != '+' && y.at(i) != '-' &&
            y.at(i) != '=')) {
            return false; //wrong character check
        }
        if (y.at(i) == '=') {
            count_equal += 1;
        }
        else if ((y.at(i) == '+') || (y.at(i) == '-')) {
            int u = y.find("=") + 1;
            if (u < i) {
                return false; //wrong number/spot of +- at rhs
            }
            else if (u > i) {
                count_oper++;
            }
        }
    }

    if (count_equal != 1) {
        return false; //wrong number of  =
    }

    string oper, sig;
    int u;

    if (count_oper > 4) {
        return false;  //wrong number of +- in whole equation
    }

    else if(count_oper <= 4) {
        if ((y.at(0) == '+') || (y.at(0) == '-')) {
            for (int i = 1; i <= int(y.length() - 1); i++) {
                if ((y.at(i) == '+') || (y.at(i) == '-')) {
                    oper = y.at(i);
                    u = i;
                    break;
                }
            }
        }
        else {
            for (int i = 0; i <= int(y.length() - 1); i++) {
                if ((y.at(i) == '+') || (y.at(i) == '-')) {
                    oper = y.at(i);
                    u = i;
                    break;
                }
            }
        }
        string num2check = y.substr(u+1, int((y.find("=") - u-1)));
        int b = str_to_int(num2check);
        if ((b == 0) && (num2check != "0")) {
            return false;
        }
        else {
            return true;
        }
    }
    return true;
}


string parse(string y, string & num1, string & num2, string & num3, string & sign) {
    int i;
    string lhs, rhs, v;
    for (i = 0; i <= (int (y.length() - 1)); i++) {
        if (y.at(i) == '=') {
            lhs = y.substr(0, i);
            rhs = y.substr(i + 1); //separating lhs && rhs
            break;
        }
    }
    int index_op;
    for (int i = 1; i <= int (y.length() - 1); i++) {
        if (y.at(i) == '+') {
            index_op = i;
            sign = "+";
            break; //finding the loc of the op
        }
        else if (y.at(i) == '-') {
            index_op = i;
            sign = "-";
            break; //finding the loc of the op
        }
    }
    int index_eq = lhs.find("=");
    num1 = lhs.substr(0, index_op);
    num2 = lhs.substr(index_op + 1, (index_eq - index_op - 1));
    num3 = rhs; //sep the numbers
    return num1, num2, num3, sign;
}

bool result(string number1, string number2, string number3, string operation) {
    int n1 = str_to_int(number1);
    int n2 = str_to_int(number2);
    int n3 = str_to_int(number3);
    if ((operation == "+") && (n1 + n2 == n3)) {
        return true;
    }
    else if ((operation == "-") && (n1 - n2 == n3)) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    string num1 = "", num2 ="", num3="", sign="";
    int count = 1;
    int joker = 1;
    int total = 0;
    string op;
    while (count <= 4) {
        cout << "Please enter question #" << count << " and its answer: ";
        cin >> op;
        bool x = inputcheck(op);
        if (x == true) {
            parse(op, num1, num2, num3, sign);
            bool c = result(num1, num2, num3, sign);
            if (c == true) {
                cout << "Correct answer! You got 25 points for this math expression." << endl;
                cout << endl;
                total += 25;
            }
            else {
                string answer;
                if (joker == 1) {
                    cout << "Wrong!" << endl;
                    cout << "Would you like to use your joker option to correct the answer? ";
                    cin >> answer;
                    string answer_lower = "";
                    for (int f = 0; f < answer.length(); f++) {
                        answer_lower += tolower(answer.at(f));
                    }
                    if (answer_lower == "yes") {
                        joker = 0;
                        string neweq;
                        cout << "Please enter the expression again: ";
                        cin >> neweq;
                        bool l = inputcheck(neweq);
                        if (l == true) {
                            parse(neweq, num1, num2, num3, sign);
                            bool c = result(num1, num2, num3, sign);
                            if (c == true) {
                                cout << "Correct answer! You got 25 points for this joker option." << endl;
                                cout << endl;
                                total += 25;
                            }
                            else if (c == false) {
                                if (sign == "+") {
                                    int trueres = str_to_int(num1) + str_to_int(num2);
                                    cout << "Sorry! The answer should have been: " << trueres << ". You got -10 penalty points for this joker option." << endl;
                                    cout << endl;
                                    total -= 10;
                                }
                                if (sign == "-") {
                                    int trueres = str_to_int(num1) - str_to_int(num2);
                                    cout << "Sorry! The answer should have been: " << trueres << ". You got -10 penalty points for this joker option." << endl;
                                    cout << endl;
                                    total -= 10;
                                }
                            }
                        }
                        else if (l == false) {
                            cout << "Wrong input format! You got -10 penalty points for this joker option." << endl;
                            total -= 10;
                            cout << endl;
                        }
                    }
                    else if (answer_lower == "no") {
                        if (sign == "+") {
                            int trueres = str_to_int(num1) + str_to_int(num2);
                            cout << "Sorry! The answer should have been: " << trueres << ". You got 0 points for this math expression." << endl;
                            cout << endl;
                        }
                        else if (sign == "-") {
                            int trueres = str_to_int(num1) - str_to_int(num2);
                            cout << "Sorry! The answer should have been: " << trueres << ". You got 0 points for this math expression." << endl;
                            cout << endl;
                        }
                    }
                }
                else if (joker == 0) {
                    if (sign == "+") {
                        int trueres = str_to_int(num1) + str_to_int(num2);
                        cout << "Sorry! The answer should have been: " << trueres << ". You got 0 points for this math expression." << endl;
                        cout << endl;
                    }
                    else if (sign == "-") {
                        int trueres = str_to_int(num1) - str_to_int(num2);
                        cout << "Sorry! The answer should have been: " << trueres << ". You got 0 points for this math expression." << endl;
                        cout << endl;
                    }
                }
            }
        }

        else if (x == false) {
            cout << "Wrong input format! You got -10 penalty points for this math expression." << endl;
            cout << endl;
            total -= 10;
        }
        count++;
    }
    if (total < 0) {
        total = 0;
    }
    cout << "End of the program. You got " << total << " points in total." << endl;
}
