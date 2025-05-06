#include "../include/ArgParser.hpp"
#include <stdexcept>
#include <string>


ArgParser::ArgParser(int argc, char **argv) {

    this->option_n = 1;
    this->option_v = 0;
    this->option_t = 0;

    this->defined_n = 0;
    this->defined_t = 0;
    this->defined_v = 0;

    if (argc < 2) {
        return ;
    }

    if (argc > 4) {
        throw std::invalid_argument("Error : too many arguments");
    }

    for (int i = 1; i < argc; i ++) {
        if (!this->check_syntax(argv[i])) {
            throw std::invalid_argument("Error : invalid option");
        }
        if (!this->extract_options(argv[i])) {
            throw std::invalid_argument("Error : option already defined");
        }
    }

    return ;
}

ArgParser::~ArgParser(void) {
    return ;
}


// This can be stdout or default (lex.yy.c)
int ArgParser::getProgramOutputLocation(void) {

    if (this->option_t == 1) {
        return (STDOUT);
    }

    return (DEFAULT);
}

// This can be stderr, stdout or none
int ArgParser::getStatsOutputLocation(void) {

    if (option_n == 1 && defined_n == 1) {
        return (NONE);
    }

    if (option_t == 1 && option_v == 1) {
        return (STDERR);
    }

    if (option_v == 1) {
        return (STDOUT);
    }

    return (NONE);
}


bool ArgParser::check_syntax(const char *arg) {
    
    std::string str_arg (arg);

    size_t arg_len = str_arg.length();

    if (arg_len > 4 || arg_len < 2) {
        return (false);
    }

    if (str_arg[0] != '-') {
        return (false);
    }

    for (size_t i = 1; i < arg_len; i++) {
        if (str_arg[i] != 't' && str_arg[i] != 'n' && str_arg[i] != 'v') {
            return (false);
        }
    }

    return (true);
}

bool ArgParser::extract_options(const char *arg) {

    std::string str_arg (arg);

    size_t arg_len = str_arg.length();

    for (size_t i = 1; i < arg_len; i ++) {

        if (str_arg[i] == 'n') {
            if (this->defined_n == 1) {
                return (false);
            }
            this->option_n = 1;
            this->defined_n = 1;
        }
        else if (str_arg[i] == 't') {
            if (this->defined_t == 1) {
                return (false);
            }
            this->option_t = 1;
            this->defined_t = 1;
        }
        else if (str_arg[i] == 'v') {
            if (this->defined_v == 1) {
                return (false);
            }
            this->option_v = 1;
            this->defined_v = 1;
        }
    }

    return (true);
}