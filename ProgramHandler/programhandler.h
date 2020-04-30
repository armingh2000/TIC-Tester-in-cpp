typedef enum {
    C,
    CPP,
    CS,
    PYTHON,
    JAVA,
    EXE,
    NOT_SUPPORTED
} prog_extn;

prog_extn find_file_extension(char * file_name);
