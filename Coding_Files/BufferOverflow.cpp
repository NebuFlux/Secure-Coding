// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  variable, and its position in the declaration. It must always be directly before the variable used for input.
  //  You must notify the user if they entered too much data.

  const std::string account_number = "CharlieBrown42";
  char user_input[20];
  // variable to track valid input
  bool valid_input = false;
  // variable to track number of attempts
  int8_t attempts = 1;
  
  while (!valid_input && attempts <= 3)
  {
	  std::cout << "Enter a value: ";
	  // use getline with sizeof user input for buffer size.
	  std::cin.getline(user_input, sizeof(user_input));
	  // count attempts
	  attempts++;

	  // If standard character input is truncated failbit is set
	  if (std::cin.fail())
	  {
		  // clear overflow and flags
		  std::cin.clear();
		  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		  // Notify user too much data was input
		  std::cout << "\n\t***Error: you entered too much data!***\n" << std::endl;
	  }
	  else {
		  // exit loop with valid input if cin is not truncated
		  valid_input = true;
	  }
  }
  // deny output if user makes more than 3 attempts
  if (attempts > 3)
  {
	  std::cout << "\tToo many tries!" << std::endl;
	  return 1;
  }
  
  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
