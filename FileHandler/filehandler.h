struct prot_t {
    char ** contents;
    int line_number;
};

char ** read_file(char * file_path, int * ln);
void free_read_file(char ** read_file, int line_num);
