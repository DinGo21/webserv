#include <iostream>
#include <string>

int main ()
{
  int         n;
  std::string str1 ("apple {};");
  std::string str2 ("apple");

  n = str1.find_first_of("};", 0);
  if (n != std::string::npos)
    std::cout << n << std::endl;
  return 0;
}