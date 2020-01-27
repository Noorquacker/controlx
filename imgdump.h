unsigned int getword(char** p);
unsigned int decompress(unsigned int comp_size, char** p, char** outp);
int decompressFiles(char* buf, int size, char* outbuf);
int getFieldData(char* buf, int cfield, int num, int dsize, char** pptr, char** fptr);
void copyFieldData(char* buf, int cfield, int num, int dsize, char* outbuf, int bufsize);
int getTotalFieldsSize(char* buf, int dsize, unsigned int* attachsize);