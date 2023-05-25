/*
Joseph Calise
ID#: 2380565
calise@chapman.edu
CPSC-350 Section 03
PA2: Not So Super Mario Bros.

Rory Sullivan
ID#: 2401103
rosullivan@chapman.edu
CPSC-350 Section 03
PA2 Not So Super Mario Bros.
*/
#ifndef WRITER_H
#define WRITER_H
#include <string>

class Writer{
    public:
    Writer();
    ~Writer();
    void addLineToFile(std::string outputFile, std::string contentToAdd);
    void addLineToFileNoEnter(std::string outputFile, std::string contentToAdd);
};






#endif