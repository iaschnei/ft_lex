#ifndef ARGPARSER_HPP
# define ARGPARSER_HPP

# define NONE 0
# define STDOUT 1
# define STDERR 2
# define DEFAULT 3

class ArgParser {

public: 

    ArgParser(int argc, char **argv);
    ~ArgParser();

    int getProgramOutputLocation();
    int getStatsOutputLocation();

    int getStdinInputStatus();

private:

    int option_n;
    int option_t;
    int option_v;

    int stdin_input;

    int defined_n;
    int defined_t;
    int defined_v;

    bool    check_syntax(const char *arg);
    bool    extract_options(const char *arg);

};


#endif