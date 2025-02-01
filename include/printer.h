#ifndef PRINTER_H
#define PRINTER_H

typedef struct printer Printer;

Printer **printer_vector_create(int src, float *dist, int nodeAmount);
Printer *printer_init(int dest, float dist);
int printer_compare(const void *a, const void *b);
void printer_print_path(Printer **p_vector, int src, int nodeAmount, int *path);
void printer_free(Printer **printer, int nodeAmount);

#endif