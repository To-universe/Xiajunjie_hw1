#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}
/**
 * @brief 矩阵加法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a + b, 如果a和b的行数或列数不相等，会给出错误提示"Error: Matrix a and b must have the same rows and cols.\n"并返回一个空矩阵
 * 加和减不需要解释思路，就是同一行同一列的值相加即可。
*/
Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows == b.rows && a.cols == b.cols)
    {
        /* code */
        Matrix result = create_matrix(a.rows,a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                result.data[i][j] = a.data[i][j] + b.data[i][j]; 
            }
        }
        return result;
    }
    else
    {
        /* code */
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0,0);
    }
    
}

/**
 * @brief 矩阵减法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a-b,如果a和b的行数或列数不相等，会给出错误提示"Error: Matrix a and b must have the same rows and cols.\n"并返回一个空矩阵
 *  
*/
Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix result = create_matrix(a.rows,a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                result.data[i][j] = a.data[i][j] - b.data[i][j]; 
            }
        }
        return result;
    }
    else
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
}

/**
 * @brief 矩阵乘法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a * b，如果a的列数不等于b的行数，会给出错误提示"Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n"并返回一个空矩阵
 * 根据定义，result矩阵第i行第j列的数等于a的第i行与b的第j列分别相乘求和的结果
*/
Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols == b.rows)
    {
        Matrix result = create_matrix(a.rows,b.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                result.data[i][j] = 0;
                for (int p = 0; p < a.cols; p++)
                {
                    result.data[i][j] += a.data[i][p] * b.data[p][j];
                }
                
            }
            
        }
        return result;
    }
    else
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    
}

/**
 * @brief 矩阵数乘
 * @param a 矩阵a
 * @param k 数k
 * @return a * k
 * 
*/
Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows,a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = k * a.data[i][j];
        }
        
    }
    
    return result;
}

/**
 * @brief 矩阵转置
 * @param a 矩阵a
 * @return a的转置矩阵
 * 
*/
Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols,a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[j][i] = a.data[i][j];
        }
        
    }
    
    return result;
}

/**
 * @brief 矩阵的行列式
 * @param a 矩阵a
 * @return a的行列式, 如果a不是方阵，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回0
 * 递归需要生成将第i行和第j列删除的子矩阵a_ij，对a_ij调用det_matrix函数；对a中元素逐个处理
*/
double det_matrix(Matrix a)
{
    if (a.rows == a.cols)
    {
        double det=0;
        if (a.rows == 1)
        {
            det = a.data[0][0];
        }
        else if (a.rows == 2)
        {
            det = a.data[0][0]*a.data[1][1] - a.data[0][1]*a.data[1][0];
        }
        else
        {
            for (int j = 0; j < a.cols; j++)
            {
                Matrix a_ij = create_matrix(a.rows-1,a.cols-1);
                for (int m = 1; m < a.rows; m++)                                        //生成子矩阵
                {
                    for (int n = 0; n < a.cols; n++)
                    {
                        if(n < j)
                        {
                            a_ij.data[m-1][n] = a.data[m][n];
                        }else if(n > j)
                        {
                            a_ij.data[m-1][n-1] = a.data[m][n];
                        }
                        
                    }
                        
                }

                if ((0+j)%2==0)
                {
                    det = det + a.data[0][j] * det_matrix(a_ij);
                }
                else
                {
                    det = det - a.data[0][j] * det_matrix(a_ij);
                }
                
            }
            
        }
        return det;
    }
    else
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    
}

/**
 * @brief 矩阵的逆
 * @param a 矩阵a
 * @return a的逆矩阵, 如果a不是方阵或a的行列式为0，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回一个空矩阵，如果a的逆矩阵不存在，会给出错误提示"Error: The matrix is singular.\n"并返回一个空矩阵。
 * 行列式的值已知，只要再求出伴随矩阵，就可以使用数乘函数来计算
*/
Matrix inv_matrix(Matrix a)
{
    if (a.rows == a.cols && det_matrix(a) != 0)
    {
        Matrix a_adj = create_matrix(a.rows,a.cols);                                    //伴随矩阵
        Matrix result = create_matrix(a.rows,a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                Matrix a_ji = create_matrix(a.rows-1,a.rows-1);                         //Aji,即将第j行和第i列删除后得到的子矩阵
                for (int m = 0; m < a.rows; m++)
                {
                    for (int n = 0; n < a.cols; n++)
                    {
                        if (m<j && n<i)
                        {
                            a_ji.data[m][n] = a.data[m][n];
                        }
                        else if (m<j && n>i)
                        {
                            a_ji.data[m][n-1] = a.data[m][n];
                        }
                        else if (m>j && n<i)
                        {
                            a_ji.data[m-1][n] = a.data[m][n];
                        }else if (m>j && n>i)
                        {
                            a_ji.data[m-1][n-1] = a.data[m][n];
                        }
                        
                        
                    }
                    
                }
                if ((i+j)%2 ==0)
                {
                    a_adj.data[i][j] = det_matrix(a_ji);
                }
                else
                {
                    a_adj.data[i][j] = -det_matrix(a_ji);
                }
                
            }
            
        }
        result = scale_matrix(a_adj,1.0/det_matrix(a));
        return result;
    }
    else
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    
}

/**
 * @brief 矩阵的秩
 * @param a 矩阵a
 * @return a的秩
 * 
*/
int rank_matrix(Matrix a)
{
    int rank,n0_row,n0_matrix=0;
    double temp;
    Matrix a_ope = a;
    if (a.rows < a.cols)
    {
        rank = a.rows;
    }
    else
    {
        rank = a.cols;
    }
    if (rank == 1)
    {
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                if (a.data[i][j] != 0)
                {
                    n0_matrix=1;
                    break;
                }
                
            }
            if(n0_matrix){
                break;
            }
        }
        if (n0_matrix)
        {
            rank=1;
        }
        else
        {
            rank=0;
        }
        
    }
    else
    {
        for (int i = 0; i < a.cols; i++)
        {
            if(a_ope.data[i][i]==0){
                n0_row = a.rows;
                for(int p=i+1 ; p<a.rows ; p++){
                    if (a_ope.data[p][i] != 0)
                    {
                        n0_row = p;
                        break;
                    }
                
                }
                if (n0_row==a.rows)
                {
                    rank -= 1;
                    continue;
                }
                else
                {
                    for (int n = i; n < a_ope.rows; n++)
                    {
                        temp = a_ope.data[i][n];
                        a_ope.data[i][n] = a_ope.data[n0_row][n];
                        a_ope.data[n0_row][n]=temp;

                    }
                
                }
            
            }

            for (int j = i+1; j < a.rows; j++)
            {
                for (int k = a.cols-1; k >=  i; k--)
                {
                    a_ope.data[j][k]=a_ope.data[j][k]-a_ope.data[j][i]*a_ope.data[i][k]/a_ope.data[i][i];
                }
            
            }

        }
    }
    
    return rank;
}

/**
 * @brief 矩阵的迹
 * @param a 矩阵a
 * @return a的迹，如果a不是方阵，会给出错误提示"Error: The matrix must be a square matrix.\n"并返回0
*/
double trace_matrix(Matrix a)
{
    if (a.rows == a.cols)
    {
        double trace=0;
        for (int i = 0; i < a.rows; i++)
        {
            trace += a.data[i][i];
        }
        return trace;
    }
    else
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
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