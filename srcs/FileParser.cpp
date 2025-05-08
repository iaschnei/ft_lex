#include "../include/FileParser.hpp"
#include "../include/colors.hpp"

#include <cstddef>
# include <iostream>
# include <fstream>
# include <ctime>


FileParser::FileParser(int argc, char **argv) {

    this->num_of_file_parsed = 0;
    this->num_of_lines_parsed = 0;
    this->time_to_parse = 0.0;

    time_t now;
    time(&now);

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] && argv[i][0] != '-') {

            this->num_of_file_parsed ++;

            if (!ParseFileAndExtractParts(argv[i])) {
                std::cerr << RED << "Error parsing '" << argv[i] << "'" << std::endl;
                std::cerr << "-- Skipping to the next file --" << RESET << std::endl;
            }
        }
    }

    time_t after;
    time(&after);

    this->time_to_parse = difftime(now, after);

    return ;
}

FileParser::~FileParser(void) {

    return ;
}

std::string FileParser::GetFullPartOne(void) {
    return(this->part_one);
}

std::string FileParser::GetFullPartTwo(void) {
    return(this->part_two);
}

std::string FileParser::GetFullPartThree(void) {
    return(this->part_three);
}

double FileParser::GetTimeToParse() {
    return (this->time_to_parse);
}

size_t FileParser::GetNumOfFiles() {
    return (this->num_of_file_parsed);
}

size_t FileParser::GetNumOfLines() {
    return (this->num_of_lines_parsed);
}

bool FileParser::ParseFileAndExtractParts(char *filename) {

    std::fstream *file_stream = new std::fstream(filename);
    std::string line_buffer;
    std::string file_buffer;

    size_t line_num = 1;

    // Store the file's content, skipping empty lines
    while (std::getline(*file_stream, line_buffer)) {

        this->num_of_file_parsed++;
        line_num++;

        if (line_buffer.empty()) {
            continue;
        }

        file_buffer.append(line_buffer);
    }

    file_stream->close();
    delete (file_stream);

    if (file_buffer.empty()) {
        std::cerr << YELLOW << "Empty file" << RESET << std::endl;
        return (false);
    }

    std::string delimiter = "%%";

    size_t delimiter_pos = file_buffer.find(delimiter);

    if (delimiter_pos == std::string::npos) {
        std::cerr << YELLOW << "Cannot find delimiter, please follow this format:" << std::endl;
        std::cerr << "Definitions (optional)\n%%\nRules\n%% (optional)\nSubroutines (optional)." << RESET << std::endl;
        return (false);
    }

    if (delimiter_pos > 0) {
        this->part_one.append(file_buffer.substr(0, delimiter_pos));
    }

    delimiter_pos = file_buffer.find(delimiter, delimiter_pos + delimiter.length());

    if (delimiter_pos != std::string::npos) {
        this->part_two.append(file_buffer.substr(this->part_one.length() + delimiter.length(), delimiter_pos - this->part_one.length() - delimiter.length()));
    } else {
        this->part_two.append(file_buffer.substr(this->part_one.length() + delimiter.length()));
        return (true);
    }

    delimiter_pos = file_buffer.find(delimiter, delimiter_pos + delimiter.length());
    if (delimiter_pos != std::string::npos) {
        std::cerr << YELLOW << "Too many delimiters, please follow this format:" << std::endl;
        std::cerr << "Definitions (optional)\n%%\nRules\n%% (optional)\nSubroutines (optional)." << RESET << std::endl;
        std::cerr << BLUE << "Definitions and Rules have been saved, behaviour is undefined." << RESET << std::endl;
        return (false);
    }

    this->part_three.append(file_buffer.substr(this->part_one.length() + delimiter.length() + this->part_two.length() + delimiter.length()));

    return (true);
}
