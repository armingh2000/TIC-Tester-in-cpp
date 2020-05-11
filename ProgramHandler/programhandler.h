typedef enum {
    PYTHON,
    JAVA,
    EXECUTABLE,
    NOT_SUPPORTED
} prog_extn;

prog_extn find_file_extension(char * file_name);
char * get_program_stdout(char * program_path, prog_extn ext, char * input);
char * handle_program(char * path_variable, char * program_path, char * input);
