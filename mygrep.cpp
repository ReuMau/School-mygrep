//Mygrep project for school.
// Created by Reu.
//

#include <iostream>
#include <string>

void stringgrep(std::string* text, std::string* search);

int main()
{

  std::string inputText, inputSearch;

  std::cout<<"Give a string from which to search for: "<<std::endl;
  std::getline(std::cin, inputText);
  std::cout<<"Give search string: "<<std::endl;
  std::getline(std::cin, inputSearch);

  stringgrep(&inputText, &inputSearch);


  return 0;
}

void stringgrep(std::string* text, std::string* search)
{
  size_t pos = text->find(*search);
  if(pos == std::string::npos){
   std::cout<<"\""<<*search<<"\" NOT found in \""<<*text<<"\""<<std::endl;
  } else {
      std::cout<<"\""<<*search<<"\"  found in  \""<<*text<<"\""<<" in position "<<pos<<std::endl;
  }
}
