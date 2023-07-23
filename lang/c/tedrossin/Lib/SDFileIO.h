#define fclose(x)   fclose2(x)  // ugly work-around for fclose not being able to be overridden
int fclose2(FILE *fp);