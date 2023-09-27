#include <iostream>
#include <stdarg.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include<iomanip>
using namespace std;

//prototype declaration for write function
void  write(string edit...);

int main()
{
    //string example
    string edit = "The number {0} is greater than {1}";

    //calling function to example string
    write(edit, 3.0, -3.0);

    //initializing number 
    double num = 1.62;

    write("Default: {0}", num);
    write("Currency: {0:c}", num);
    write("Scientific: {0:e}", num);
    write("Fixed point: {0:f}", num);
    write("Fixed point: {0:f8}", num);
    write("Round to int: {0:i}", num);
    write("Hello world \n");

    system("pause>0");

}

void write(string edit...)

{
    //creating vector where arguments get stored and pulled from
    vector<double> args;

    va_list vargs;
    va_start(vargs, edit);

    vector<char> specifier;
    //int n = 16;
    //for (int i = 0; i < n - 1; i++)
    while (1)
    {
        double xarg = va_arg(vargs, double);
        if (xarg == NULL)
        {
            break;
        }
        args.push_back(xarg);
    }
    va_end(vargs);


    bool find = false;
    //starting loop through string
    for (int i = 0; i < edit.length(); i++)
    {
        //i represents index of the string, up until '}'
        if (edit[i] == '{')
        {
            double close = edit.find("}");
            //using  .find() method in order to find the first occurance of the curly bracket within the string
            string str = edit.substr(i, close - i + 1);
            //i is the index of opening bracket; +1 to include closed bracket, since we subtract the index of {

            int x = str.find(":");
            //subtracting zero in order to convert string argument number to an integer
            int ind = str[1] - '0';

            if (x == -1)//if x=-1 it will output the integer 
            {
                cout << args[ind] << " ";
            }
            //else if x != -1 continue to scan through string
            else
            {
                int len = str.length();
                string specifier = str.substr(x + 1, 1);
                //currency
                if (specifier == "c")
                {
                    cout << "$" << args[ind] << " ";
                }
                //scientific
                else if (specifier == "e")
                {
                    cout << args[ind];

                }
                //fixed point
                else if (specifier == "f")
                {

                    string specifier = str.substr(x + 1, 2);
                    int digit = 5;
                    if (specifier[1] != '}')
                    {
                        //using atoi to turn string to int in order to allow for set amount of decimal places in fixed point 
                        digit = atoi(str.substr(x + 2, 1).c_str());
                    }
                    cout << fixed << setprecision(digit) << args[ind] << " ";

                }
                //rounding to integer
                else if (specifier == "i")
                {
                    cout << (int)args[ind] << " ";

                }
            }
            //using .erase() method in order to erase bracketed portion 
            edit.erase(i, close - i + 1);
            find = true;
        }
        else
        {
            cout << edit[i];
        }
    }

    if (!find) //find = true 
    {
        cout << "^^ There are no format specifiers here ^^" << endl;
    }
    else
    {
        cout << endl;
    }

}