// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>

// Simple custom Exception inheriting from std::exception
class MyException : public std::exception
{
// private data string
private:
	std::string message;

// public data constructor and what method
public:
    // Constructor
	MyException(const std::string& msg) : message(msg) {}

    // Override what() method from std::exception
    const char* what() const noexcept override
    {
        return message.c_str();
	}
};

bool do_even_more_custom_application_logic()
{
    // throw logic_error derived from standard exception with descriptive message.
    throw std::logic_error("do_even_more_logic has experienced a logic_error!");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    // Wrap the call to do_even_more_custom_application_logic()
    std::cout << "\nRunning Custom Application Logic." << std::endl;

    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    // Catch standard exception from method call.
    catch (std::exception const& e)
    {
        // Give descriptive location of catch and show exception message
        std::cout << "\n\t Cought standard exception in do_custom_application_logic: " << std::endl;
        std::cout <<"\t***" << e.what() <<"***" << std::endl;
    }

    // Throw custom exception with discriptive message
	throw MyException("do_custom_application_logic has encountered a custom exception");

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
	// detect division by zero and throw std::domain_error with descriptive message
    if (den == 0)
    {
        throw std::domain_error("Division by zero is not allowed.");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  Use try/catch to handle exceptions from divide().
    try
    {
        float numerator = 10.0f;
        float denominator = 0;

        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::domain_error const& e)
    {
		// Give location of where exception was caught and exception message
        std::cout << "\tCaught exception in do_division: " << std::endl;
        std::cout << "\t***" << e.what() << "***" << std::endl;
	}
}

int main()
{
    std::cout << "\nExceptions Tests!" << std::endl;

    // Encapsulate main method with try/catch block for exception handling.
    // give descriptive location where exception is cought with exception message
    // for each cought exception.
    try
    {
        do_division();
        do_custom_application_logic();
    }
    //  Catch custom exception
    catch (MyException const& e)
    {
        std::cout << "\n\tCaught MyException in main: " << std::endl;
        std::cout << "\t***"<< e.what() << "***" << std::endl;
    }
    // Catch std::exception
    catch (std::exception const& e)
    {
        std::cout << "\n\tCaught standard exception in main:" << std::endl;
        std::cout << "\t***" << e.what() << "***" << std::endl;
    }
    //  Catch unknown exception 
    catch (...)
    {
        std::cout << "\n\tCaught unkown exception in main:" << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu