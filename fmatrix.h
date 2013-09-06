/* header file for fmatrix.c */
#ifndef FMATRIX
#define FMATRIX

#define MAXLEN 2500
struct matrix {
	int nrows; /* the number of rows */
	int ncols; /* the number of columns */
	double a[MAXLEN]; /* array containing elements of 2 dimensions matrix */
};

int readmatrix(struct matrix *mt, int nrows, int ncols);
int submatrix(struct matrix *mt1, struct matrix mt2, int rowth, int colth);
int printmatrix(struct matrix mt);
int detmatrix(struct matrix mt, double *det);
int detmatrix2(struct matrix mt, double *det);
int inversematrix(struct matrix *mt1, struct matrix mt2);

#endif
