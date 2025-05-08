#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include <string>
/*
|    Parses .l files given as input
|    can be called multiple times and will store the different parts of each file in a single string:
|    part1[], part2[], part3[]  
*/

class FileParser {

public:

    FileParser(int argc, char **argv);
    ~FileParser();

    // Returns parts from all input files concatenated
    std::string GetFullPartOne();
    std::string GetFullPartTwo();
    std::string GetFullPartThree();

    double GetTimeToParse();
    size_t GetNumOfFiles();
    size_t GetNumOfLines();

private:

    std::string part_one;
    std::string part_two;
    std::string part_three;

    // Stats values
    size_t num_of_file_parsed;
    size_t num_of_lines_parsed;
    double time_to_parse;

    bool ParseFileAndExtractParts(char *filename);

};


#endif