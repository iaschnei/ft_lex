#include <iostream>
#include "../include/ArgParser.hpp"
#include "../include/FileParser.hpp"
#include "../include/colors.hpp"

int main(int ac, char **av) {

    try {
    
    ArgParser arg_parser(ac, av);

    int program_output = arg_parser.getProgramOutputLocation();
    int stats_output = arg_parser.getStatsOutputLocation();

    if (stats_output != 0) {
        std::cout << "Printing stats in " << stats_output << std::endl;
    }

    std::cout << "Printing program in " << program_output << std::endl;

    FileParser file_parser(ac, av);

    std::cout << "Part 1 :\n" << file_parser.GetFullPartOne() << std::endl;
    std::cout << "Part 2 :\n" << file_parser.GetFullPartTwo() << std::endl;
    std::cout << "Part 3 :\n" << file_parser.GetFullPartThree() << std::endl; 

    }
    catch (const std::exception& e) {

        std::cerr << RED << e.what() << RESET << std::endl;
        return(1);
    }
}