// HomeworkP1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>

//P2 Section**
using std::string;
using std::cout;
//2End*******


//1******
    void numbersDivisibleByTwo(int num1, int num2)
    {
        for (int i = 0; i <= 1000; i++)
        {
            if (i % num1 == 0 && i % num2 == 0) 
            {
                std::cout << i << " ";
            }
        }

        std::cout << std::endl;
    }
//1End*****

// P2 Section ****
    static string process(const string& s)
    {
        string result;

        for (int i = 0; i < s.size(); i++)
            result = s[i] + result;

        return(result);
    }


    static void show(const string& s)
    {
        cout << s << " -> " << process(s) << "\n";
    }
    //2End*******



int main()
{
    //P1***
    int firstNumber, secondNumber;
    
    std::cout << "Enter First Number: ";
    std::cin >> firstNumber;

    std::cout << "Enter Second Number: ";
    std::cin >> secondNumber;

    std::cout << "Number Divisable by " << firstNumber << "& " << secondNumber << "from 0 to 1000 are " << std::endl;
    numbersDivisibleByTwo(firstNumber, secondNumber);
    //1End*****

    //P2Start***
    show("hello world");
   
    //2End***


    //P3Start***
    std::string input = "the cake is a lie";
    std::string output = "";

    auto isVowel = [](char c) {
        c = std::tolower(c); 
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    for (char c : input) {
        if (!isVowel(c)) {
            output += c;
        }
    }

    std::cout << "Input: " << input << std::endl;
    std::cout << "Output: " << output << std::endl;

    return 0;
}




