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
void filegrep2(char* fArr, char* fSearch, int option);
int options(int argc, char* argv[]);


int main(int argc, char *argv[])
{
  int option = options(argc, argv);
  if (option == 0) {
      std::string inputText, inputSearch;

      std::cout<<"Give a string from which to search for: "<<std::endl;
      std::getline(std::cin, inputText);
      std::cout<<"Give search string: "<<std::endl;
      std::getline(std::cin, inputSearch);


      stringgrep(&inputText, &inputSearch);

      std::cin.ignore();

      return 0;
  }
  else if (option == 1) {
      char* fileSearch = argv[1];
      std::ifstream inputFile;
      inputFile.open(argv[2], std::ios::ate);


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
  else if (option < 5) {
      char* fileSearch = argv[2];
      std::ifstream inputFile;
      inputFile.open(argv[3], std::ios::ate);


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
      filegrep2(fileArray, fileSearch, option);

      delete[] fileArray;
      inputFile.close();

      return 0;
  }
  else {
      if (option == 5) {
          std::cout<<"Error with cmd line arguments. Try again."<<std::endl;
          return 1;
      }

  }
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
}

void filegrep2(char* fArr, char* fSearch, int option) {
    char* compText = strstr(fArr, fSearch);
    if(compText == nullptr) {
        std::cout<<"Searched string not found in file."<<std::endl;
        return;
    }

    int counterLine = 0, counterContain = 0;
    char* curLine = fArr;
    while (*curLine != '\0') {
        char * nextLine = strchr(curLine, '\n');
        if (nextLine) {
            counterLine++;
            std::size_t lenLine = nextLine - curLine;
            char* line = new char[lenLine+1];
            strncpy(line, curLine, lenLine);
            line[lenLine] = '\0';
            char* compStr = strstr(line, fSearch);
            if (compStr != nullptr) {
                if (option == 2 || option == 4) {
                    std::cout<<counterLine<<":     "<<line<<std::endl;
                    counterContain++;
                } else {
                    std::cout<<line<<std::endl;
                    counterContain++;
                }
            }
            delete[] line;
            curLine = nextLine + 1;
        } else {
            char* compStr = strstr(curLine, fSearch);
            counterLine++;
            if (compStr != nullptr) {
                std::cout<<curLine<<std::endl;
            }
            break;
        }
    }
    if (option == 3 || option == 4) {
        std::cout<<"Occurrences of lines containing \""<<fSearch<<"\": "<<counterContain<<std::endl;
    }
}

//Options for different inputs
//0 = user input text || 1 = simple print line from file || 2 = -ol || 3 = -oo || 4 = -olo || 5 = error
int options(int argc, char* argv[]) {
    const char* ol = "-ol";
    const char* oo = "-oo";
    const char* olo = "-olo";

    if (argc <= 2) return 0;
    else if (argc == 3) return 1;
    else if (strcmp(argv[1], ol)==0) return 2;
    else if (strcmp(argv[1], oo)==0) return 3;
    else if (strcmp(argv[1], olo)==0) return 4;
    else return 5;

}
