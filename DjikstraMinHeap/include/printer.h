#ifndef PRINTER_H
#define PRINTER_H

typedef struct printer Printer;

//======================= MEMORY FUNCTIONS =======================
Printer **printer_vector_create(int src, float *dist, int nodeAmount);
Printer *printer_init(int dest, float dist);
void printer_free(Printer **printer, int nodeAmount);

//======================= GETTERS =======================
int printer_compare(const void *a, const void *b);

//======================= SPECIAL PRINTER FUNCTIONS =======================
void printer_print_path(Printer **p_vector, int src, int nodeAmount, int *path, char *file_path);

#endif