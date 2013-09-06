/* function for matirx operation */

#include <stdio.h>
#include "fmatrix.h"

/* read elements of matrix from keyboard */
int readmatrix(struct matrix *mt, int nrows, int ncols)
{
	int ith, jth;
	mt->nrows = nrows;
	mt->ncols = ncols;
	for (ith = 0; ith < nrows; ++ith)
		for (jth =0; jth < ncols; ++jth){
			printf("(%d, %d):", ith, jth);
			scanf("%lf",&(mt->a)[ith*ncols+jth]);
		}
	return 0;
}

/* obtain submatrix mt1 by deleting rowth row and colth column of matrix mt2 */
int submatrix(struct matrix *mt1, struct matrix mt2, int rowth, int colth)
{
	int ith, jth, kth;

	mt1->nrows = mt2.nrows - 1;
	mt1->ncols = mt2.ncols - 1;
	
	kth = 0;
	for (ith = 0; ith < mt2.nrows; ++ith) {
		if (ith == rowth) /* delete rowth row */
			;
		else {
			for (jth = 0; jth < mt2.ncols; ++jth) {
				if (jth == colth) /* delete colth column */
					;
				else {
					(mt1->a)[kth] = (mt2.a)[ith*mt2.ncols+jth];
					++kth;
				}
			}
		}
	} 
	return 0;
}

/* print matrix on the screen */
int printmatrix(struct matrix mt)
{
	int ith, jth, kth;
	kth = 0;
	for (ith = 0; ith < mt.nrows; ++ith) {
		for (jth =0; jth < mt.ncols; ++jth) {
			printf("%.2lf ", (mt.a)[kth]);
			++kth;
		}
		printf("\n");
	}

	return 0;
}

/* determinant of matrix */
int detmatrix(struct matrix mt, double *det)
{
	struct matrix submt;
	int jth;
	double subdet;
	double temp1 = 0;

	if (mt.nrows != mt.ncols) {
		printf("Please enter square matrix!\n");
		return -1;
	}
	else if (mt.nrows == 1) {
		*det = (mt.a)[0];
		return 0;
	}
	else if (mt.nrows == 2) {
		*det = (mt.a)[0] * (mt.a)[3] - (mt.a)[1] * (mt.a)[2];
		return 0;
	}
	/* det = mt[0][0]*cof00 -mt[0][1]*cof01 + ...*/
	else if (mt.nrows > 2) {
		for (jth = 0; jth < mt.ncols; ++jth) {
			submatrix(&submt, mt, 0, jth);
			detmatrix(submt, &subdet);
			if (jth % 2 == 0)
				temp1 = temp1 + (mt.a)[jth] * subdet;
			else
				temp1 = temp1 - (mt.a)[jth] * subdet;
		}
		*det = temp1;
		return 0;
	}
}

int detmatrix2(struct matrix mt, double *det)
{
	int ith, jth;
	double product1 = 1;
	double product2 = 1;
	double temp1 = 0;
	if (mt.nrows != mt.ncols) {
		printf("Please enter square matrix!\n");
		return -1;
	}
	else if (mt.nrows == 1) {
		*det = (mt.a)[0];
		return 0;
	}
	else if (mt.nrows == 2) {
		*det = (mt.a)[0] * (mt.a)[3] - (mt.a)[1] * (mt.a)[2];
		return 0;
	}
	/* a00*a11*a22-a02*a11*a20+a10*a21*a03-a12*a21*a00+... */
	else if (mt.nrows > 2) {
		for (ith = 0; ith < mt.nrows; ++ith) {
			for (jth = 0; jth < mt.ncols; ++jth) {
				printf("(%d, %d)\n", (ith+jth)%mt.nrows, jth);
				product1 *= (mt.a)[((ith+jth)%mt.nrows)*mt.ncols+jth];
				printf("(%d, %d)\n", (ith+jth)%mt.nrows, (mt.ncols-1-jth));
				product2 *= (mt.a)[((ith+jth)%mt.nrows)*mt.ncols+(mt.ncols-1-jth)];
			}
			temp1 = temp1 + product1 - product2;
			product1 = 1; /* */
			product2 = 1; /* */
		}
		*det = temp1;
		return 0;
	}
}

/* matrix mt1 is an iversion of matrix mt2 */
int inversematrix(struct matrix *mt1, struct matrix mt2)
{
	double det;
	double subdet;
	int ith, jth;
	struct matrix mt3;

	if (mt2.nrows != mt2.ncols){
		printf("Matrix is not square.\n");
		return -1;
	}

	detmatrix(mt2, &det); /* calculate determinant of mt2 */

	if (det == 0) {
		printf("Matrix can't be inversed.\n");
		return -1;
	}

	mt1->nrows = mt2.nrows;
	mt1->ncols = mt2.ncols;
	for (ith = 0; ith < mt2.nrows; ++ith) {
		for (jth = 0; jth < mt2.ncols; ++jth) {
			submatrix(&mt3, mt2, ith, jth);	
			detmatrix(mt3, &subdet);
			if ((ith+jth) % 2 == 0)
				(mt1->a)[jth*mt1->ncols+ith] = subdet/det;
			else
				(mt1->a)[jth*mt1->ncols+ith] = (-1) * subdet/det;
		}
	}
	return 0;
}

