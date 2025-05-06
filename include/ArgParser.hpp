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

private:

    bool option_n;
    bool option_t;
    bool option_v;

    bool defined_n;
    bool defined_t;
    bool defined_v;

    bool    check_syntax(char *arg);
    bool    extract_options(char *arg);

};


#endif