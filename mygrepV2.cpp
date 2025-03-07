// Mygrep project for school
// Created by Reetta Ketola
//

#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

//Function prototypes
void stringgrep(std::string* text, std::string* search);
void filegrep(char* fArr, char* fSearch);

int main(int argc, char *argv[])
{
  if (argc < 2) {
      std::string inputText, inputSearch;

      std::cout<<"Give a string from which to search for: "<<std::endl;
      std::getline(std::cin, inputText);
      std::cout<<"Give search string: "<<std::endl;
      std::getline(std::cin, inputSearch);


      stringgrep(&inputText, &inputSearch);

      std::cin.ignore();

      return 0;
  }

  char* fileSearch = argv[1];
  std::ifstream inputFile;
  inputFile.open(argv[2], std::ios::ate);

  std::cout << argv[2] << std::endl;

  if (!inputFile.is_open()) {
      std::cout << "File not found. Try again." << std::endl;
      return 1;
  }

  std::streampos fileSize = inputFile.tellg();
  fileSize += 1;
  char* fileArray = new char[fileSize];
  fileArray[fileSize] = '\0';

  inputFile.seekg(0, std::ios::beg);

  inputFile.read(fileArray, fileSize);
  filegrep(fileArray, fileSearch);

  delete[] fileArray;
  inputFile.close();

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

void filegrep(char* fArr, char* fSearch) {
  char* compText = strstr(fArr, fSearch);
  if(compText == nullptr) {
        std::cout<<"Search string not found in file."<<std::endl;
  }
  char* curLine = fArr;
  while (*curLine != '\0') {
      char * nextLine = strchr(curLine, '\n');
      if (nextLine) {
          std::size_t lenLine = nextLine - curLine;
          char* line = new char[lenLine+1];
          strncpy(line, curLine, lenLine);
          line[lenLine] = '\0';
          char* compStr = strstr(line, fSearch);
          if (compStr != nullptr) {
            std::cout<<line<<std::endl;
          }
          delete[] line;
          curLine = nextLine + 1;
      } else {
          char* compStr = strstr(curLine, fSearch);
          if (compStr != nullptr) {
              std::cout<<curLine<<std::endl;
          }
          break;
      }
  }
  return;
}
