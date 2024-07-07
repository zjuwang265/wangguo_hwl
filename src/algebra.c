#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    m.data = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        m.data[i] = (double *)malloc(col * sizeof(double));
    }
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
     Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return create_matrix(0, 0);
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return create_matrix(0, 0);
}

Matrix mul_matrix(Matrix a, Matrix b)
{
     if (a.cols != b.rows) {
        fprintf(stderr, "Matrix dimensions do not conform for multiplication.\n");
        exit(EXIT_FAILURE);
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return create_matrix(0, 0);
}

Matrix scale_matrix(Matrix a, double k)
{
     Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return create_matrix(0, 0);
}

Matrix transpose_matrix(Matrix a)
{
     Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return create_matrix(0, 0);
}

double det_matrix(Matrix a)
{
     if (a.rows != 2 || a.cols != 2) {
        fprintf(stderr, "Determinant calculation only supported for 2x2 matrices.\n");
        exit(EXIT_FAILURE);
    }
    return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
}


Matrix inv_matrix(Matrix a)
{
    if (a.rows != 2 || a.cols != 2) {
        fprintf(stderr, "Inverse matrix calculation only supported for 2x2 matrices.\n");
        exit(EXIT_FAILURE);
    }
    double det = det_matrix(a);
    if (det == 0) {
        fprintf(stderr, "Matrix is not invertible.\n");
        exit(EXIT_FAILURE);
    }
    Matrix result = create_matrix(2, 2);
    result.data[0][0] = a.data[1][1] / det;
    result.data[0][1] = -a.data[0][1] / det;
    result.data[1][0] = -a.data[1][0] / det;
    result.data[1][1] = a.data[0][0] / det;
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
     if (a.rows != a.cols) {
        fprintf(stderr, "Rank calculation only supported for square matrices.\n");
        exit(EXIT_FAILURE);
    }
    int rank = 0;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (a.data[i][j] != 0) {
                rank++;
                break;
            }
        }
    }
    return rank;
}

double trace_matrix(Matrix a)
{
      if (a.rows != a.cols) {
        fprintf(stderr, "Trace calculation only supported for square matrices.\n");
        exit(EXIT_FAILURE);
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}
