// Mygrep project for school
// Created by Reetta Ketola
//

#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <strings.h>
#include <cctype>


//Function prototypes
void stringgrep(std::string* text, std::string* search);
void filegrep(char* fArr, char* fSearch);
void filegrep2(char* fArr, char* fSearch, int option);
void casegrep(char* fArr, char* fTemp, char* fSearch, char* ftSearch, int option);
int options(int argc, char* argv[]);
void lowerCase(char* str);

int main(int argc, char *argv[])
{
  int option = options(argc, argv);
//starts going through every possible option
//1st increment
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
  //2nd increment
  else if (option == 1) {
      char* fileSearch = argv[1];
      std::ifstream inputFile;
      inputFile.open(argv[2], std::ios::ate);
      //checks if file is openable
      if (!inputFile.is_open()) {
          std::cout << "File not found. Try again." << std::endl;
          return 1;
      }

      std::streampos fileSize = inputFile.tellg();
      auto fileSizeInt = static_cast<long long int>(fileSize);
      char* fileArray = new char[fileSizeInt + 1];
      fileArray[fileSize] = '\0';

      inputFile.seekg(0, std::ios::beg);

      inputFile.read(fileArray, fileSize);
      filegrep(fileArray, fileSearch);

      //dynamic memory allocation/remembering to close open files
      delete[] fileArray;
      inputFile.close();

      return 0;
  }
  //3rd/4th increments
  else if (option < 8) {
      char* fileSearch = argv[2];
      std::ifstream inputFile;
      inputFile.open(argv[3], std::ios::ate);
      //more file managing
      if (!inputFile.is_open()) {
          std::cout << "File not found. Try again." << std::endl;
          return 1;
      }
      //passes the entire file as an c string
      std::streampos fileSize = inputFile.tellg();
      auto fileSizeInt = static_cast<long long int>(fileSize);
      char* fileArray = new char[fileSizeInt + 1];
      fileArray[fileSize] = '\0';

      inputFile.seekg(0, std::ios::beg);
      inputFile.read(fileArray, fileSize);
      //special case for the case-sensitivity options
      if (option == 6 || option == 7) {
          char* tempFile = new char[fileSizeInt + 1];
          char* tempSearch = new char[strlen(fileSearch)];
          std::strcpy(tempFile, fileArray);
          std::strcpy(tempSearch, fileSearch);
          lowerCase(tempFile);
          lowerCase(tempSearch);
          casegrep(fileArray, tempFile,fileSearch, tempSearch, option);
          delete[] tempFile;
          delete[] tempSearch;
      } else filegrep2(fileArray, fileSearch, option);
      //For every other option

      //Remembering to close things before exiting the program.
      delete[] fileArray;
      inputFile.close();

      return 0;
  } else {  //error handling to make sure you can see if your option choice wasn't correctly formatted
      std::cout<<"Error with cmd line arguments. Try again."<<std::endl;
      return 1;
  }

}

//First increment function that just checks if a string is contained within another
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

//Second/third increment function that includes the printer and takes user cmd line arguments into account
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

            //First we check the reverse searches
            if (option == 5 && compStr == nullptr) {
                    std::cout<<line<<std::endl;
            }
            //Then we go over the normal searches
            else if (compStr != nullptr) {
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
            if (option == 5 && compStr == nullptr) {
                std::cout<<curLine<<std::endl;
            } else if (option == 4 && compStr != nullptr) {
                std::cout<<counterLine<<":     "<<curLine<<std::endl;
                counterContain++;
            } else if (option == 3 && compStr != nullptr) {
                std::cout<<counterLine<<":     "<<curLine<<std::endl;
                counterContain++;
            } else if (compStr != nullptr) {
                std::cout<<curLine<<std::endl;
            } else {
                break;
            }
        }
    }
    if (option == 3 || option == 4) {
        std::cout<<"Occurrences of lines containing \""<<fSearch<<"\": "<<counterContain<<std::endl;
    }
}
//Fourth increment function that adds the ability to compare without case-sensitivity
void casegrep(char* fArr, char* fTemp, char* fSearch, char* ftSearch, int option) {
    int counterLine = 0, counterContain = 0;
    char* curLine = fArr;
    char* curTemp = fTemp;

    while (*curLine != '\0') {
        char * nextLine = strchr(curLine, '\n');
        char* nextTemp = strchr(curTemp, '\n');
        if (nextLine) {
            counterLine++;
            std::size_t lenLine = nextLine - curLine;
            char* line = new char[lenLine + 1];
            char* tempLine = new char[lenLine + 1];

            strncpy(line, curLine, lenLine);
            strncpy(tempLine, curTemp, lenLine);

            line[lenLine] = '\0';
            tempLine[lenLine] = '\0';

            char* compStr = strstr(tempLine, ftSearch);

            if (option == 6 && compStr != nullptr) {  // -oi option (case-insensitive match)
                std::cout << line << std::endl;
            }
            else if (option == 7) {
                if (compStr == nullptr) {
                    std::cout<<counterLine<<":     "<<line<<std::endl;
                    counterContain++;
                }
            }

            delete[] line;
            delete[] tempLine;
            curLine = nextLine + 1;
            curTemp = nextTemp + 1;
        } else {
            char* compStr = strstr(curTemp, ftSearch);
            counterLine++;
            if (option == 7 && compStr == nullptr) {  // -olori option (lines without match)
                std::cout << counterLine << ":     " << curLine << std::endl;
                counterContain++;
            } else if (option == 6 && compStr != nullptr) {  // -oi option (case-insensitive match)
                std::cout << curLine << std::endl;
            } else {
                break;
            }
        }
    }
    if (option == 7) {
        std::cout << "Occurrences of lines not containing \"" << fSearch << "\": " << counterContain << std::endl;
    }
}

//Third/fourth increment function that adds options for different user inputs. List below.
//0 = user input text || 1 = simple print line from file || 2 = Line count || 3 = nro of occurrences || 4 = combined 2/3
//5 = reverse search || 6 = NOT case-sensitive || 7 = Combo deal with everything
int options(int argc, char* argv[]) {
    const char* ol = "-ol";
    const char* oo = "-oo";
    const char* olo = "-olo";
    const char* reverse = "-or";
    const char* oi = "-oi";
    const char* olori = "-olori";

    if (argc <= 2) return 0;
    else if (argc == 3) return 1;
    else if (strcmp(argv[1], ol)==0) return 2;
    else if (strcmp(argv[1], oo)==0) return 3;
    else if (strcmp(argv[1], olo)==0) return 4;
    else if (strcmp(argv[1], reverse)==0) return 5;
    else if (strcmp(argv[1], oi)==0) return 6;
    else if (strcmp(argv[1], olori)==0) return 7;
    else return 8;
}
//Function that takes an array as an argument and outputs in lowercase to aid the case-sensitivity option to work.
//Used static cast to help it play nice with signed chars.
void lowerCase(char *str) {
    for (int i = 0; str[i]; ++i) {
        str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
    }
}
