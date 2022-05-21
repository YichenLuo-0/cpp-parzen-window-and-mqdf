/********************************************************************
 * @File name:		Controller.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-26
 * @Description:	Use to read the dataset and load it as a list
 ********************************************************************/

 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include "Matrix.h"

#include <math.h>


//-------------------------------------------------------------------
// Constants and Typedefine
//-------------------------------------------------------------------

// If the value is less than this value, it is judged to be 0.
const double epsilon = 1e-12;


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	Matrix
 * @brief	Constructor. Create a matrix with an initial value of 0.
 * @param	row - Matrix rows
 * @param	column - Matrix columns
 * */
Matrix::Matrix(int row, int column)
{
	this->row = row;
	this->column = column;
	for (int i = 0; i < row; i++)
	{
		vector<double> aRow(column, 0);
		this->mat.push_back(aRow);
	}
}


/********************************************************************
 * @name	Matrix
 * @brief	Constructor. Create a matrix with an input initial value.
 * @param	row - Matrix rows
 * @param	column - Matrix columns
 * @param	mat - Input initial value
 * */
Matrix::Matrix(int row, int column, double* mat)
{
	this->row = row;
	this->column = column;
	for (int i = 0; i < row; i++)
	{
		vector<double> aRow;
		for (int j = 0; j < column; j++)
		{
			aRow.push_back(*mat++);
		}
		this->mat.push_back(aRow);
	}
}


/********************************************************************
 * @name	~Matrix
 * @brief	The destructor
 * @param	none
 * */
Matrix::~Matrix()
{
}


/********************************************************************
 * @name	print
 * @brief	Output matrix to console
 * @param	none
 * @return	none
 * */
void Matrix::print()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << mat[i][j] << "\t\t";
		}
		cout << endl;
	}
}


/********************************************************************
 * @name	get
 * @brief	Gets the value of a location.
 * @param	row - Matrix rows
 * @param	column - Matrix columns
 * @return	The value in the position
 * */
double Matrix::get(int row, int column)
{
	return mat.at(row).at(column);
}


/********************************************************************
 * @name	set
 * @brief	Set the value of a location.
 * @param	row - Matrix rows
 * @param	column - Matrix columns
 * @param	value - The new value that need to be set
 * @return	none
 * */
void Matrix::set(int row, int column, double value)
{

	mat[row][column] = value;
}


/********************************************************************
 * @name	operator+
 * @brief	Implement matrix addition
 * @param	B - Another matrix
 * @return	Matrix plus result
 * */
Matrix Matrix::operator+(const Matrix B)
{
	Matrix* C = new Matrix(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			C->mat[i][j] = mat[i][j] + B.mat[i][j];
			if (abs(C->mat[i][j]) < epsilon)
			{
				C->mat[i][j] = 0.0;
			}
		}
	}
	return *C;
}


/********************************************************************
 * @name	operator-
 * @brief	Implement matrix minus
 * @param	B - Another matrix
 * @return	Matrix minus result
 * */
Matrix Matrix::operator-(const Matrix B)
{
	Matrix* C = new Matrix(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			C->mat[i][j] = mat[i][j] - B.mat[i][j];
			if (abs(C->mat[i][j]) < epsilon)
			{
				C->mat[i][j] = 0.0;
			}
		}
	}
	return *C;
}


/********************************************************************
 * @name	operator*
 * @brief	Implement matrix multiplication
 * @param	B - Another matrix
 * @return	Matrix multiplication result
 * */
Matrix Matrix::operator*(const Matrix B)
{
	int A_row = row;
	int A_column = column;
	int B_row = B.row;
	int B_column = B.column;
	if (A_column != B_row)
	{
		cout << "Invalid matrix dimension!" << endl;
		exit(0);
	}
	Matrix* C = new Matrix(A_row, B_column);
	for (int i = 0; i < A_row; i++)
	{
		for (int j = 0; j < B_column; j++)
		{
			C->mat[i][j] = 0;
			for (int k = 0; k < A_column; k++)
			{
				C->mat[i][j] += mat[i][k] * B.mat[k][j];
			}
			if (abs(C->mat[i][j]) < epsilon)
			{
				C->mat[i][j] = 0.0;
			}
		}
	}
	return *C;
}


/********************************************************************
 * @name	operator*
 * @brief	Implement matrix multiplication with a constant
 * @param	B - A constant
 * @return	Matrix multiplication result
 * */
Matrix Matrix::operator*(const double B)
{
	Matrix* C = new Matrix(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			C->mat[i][j] = B * mat[i][j];
		}
	}
	return *C;
}


/********************************************************************
 * @name	trans
 * @brief	Compute the transpose of the matrix
 * @param	matrix - A matrix
 * @return	Transpose of the matrix
 * */
Matrix Matrix::trans(const Matrix matrix)
{
	int row = matrix.column;
	int column = matrix.row;
	Matrix* AT = new Matrix(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			AT->mat[i][j] = matrix.mat[j][i];
		}
	}
	return *AT;
}


/********************************************************************
 * @name	inverse
 * @brief	Compute the inverse of the matrix
 * @param	matrix - A matrix
 * @return	Inverse of the matrix
 * */
Matrix Matrix::inverse(const Matrix matrix)
{
	if (matrix.row != matrix.column)
	{
		cout << "Invalid matrix dimension!" << endl;
		exit(0);
	}
	int n = matrix.row;
	Matrix* inv_A = new Matrix(n, n);
	Matrix L(n, n);
	Matrix U(n, n);
	Matrix inv_L(n, n);
	Matrix inv_U(n, n);
	// Factor L and U
	for (int i = 0; i < n; i++)
	{
		L.mat[i][i] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		U.mat[0][i] = matrix.mat[0][i];
	}
	for (int i = 1; i < n; i++)
	{
		L.mat[i][0] = 1.0 * matrix.mat[i][0] / matrix.mat[0][0];
	}
	// Compute the L and U triangles
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			double tem = 0;
			for (int k = 0; k < i; k++)
			{
				tem += L.mat[i][k] * U.mat[k][j];
			}
			U.mat[i][j] = matrix.mat[i][j] - tem;
			if (abs(U.mat[i][j]) < epsilon)
			{
				U.mat[i][j] = 0.0;
			}
		}
		// Compute L (row J, column I)
		for (int j = i; j < n; j++)
		{
			double tem = 0;
			for (int k = 0; k < i; k++)
			{
				tem += L.mat[j][k] * U.mat[k][i];
			}
			L.mat[j][i] = 1.0 * (matrix.mat[j][i] - tem) / U.mat[i][i];
			if (abs(L.mat[i][j]) < epsilon)
			{
				L.mat[i][j] = 0.0;
			}
		}
	}
	// The rest of L and U is set to 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i > j)
			{
				U.mat[i][j] = 0.0;
			}
			else if (i < j)
			{
				L.mat[i][j] = 0.0;
			}
		}
	}
	// The inverse of the matrix U
	for (int i = 0; i < n; i++)
	{
		// Take the value of the diagonal element of U, and just take the inverse
		inv_U.mat[i][i] = 1 / U.mat[i][i];
		for (int k = i - 1; k >= 0; k--)
		{
			double s = 0;
			for (int j = k + 1; j <= i; j++)
			{
				s = s + U.mat[k][j] * inv_U.mat[j][i];
			}
			// Iterating, getting each value in reverse order.
			inv_U.mat[k][i] = -s / U.mat[k][k];
			if (abs(inv_U.mat[k][i]) < epsilon)
			{
				inv_U.mat[k][i] = 0.0;
			}
		}
	}
	// Take the inverse of L
	for (int i = 0; i < n; i++)
	{
		inv_L.mat[i][i] = 1;
		for (int k = i + 1; k < n; k++)
		{
			for (int j = i; j <= k - 1; j++)
			{
				inv_L.mat[k][i] = inv_L.mat[k][i] - L.mat[k][j] * inv_L.mat[j][i];
				if (abs(inv_L.mat[k][i]) < epsilon)
				{
					inv_L.mat[k][i] = 0.0;
				}
			}
		}
	}
	*inv_A = inv_U * inv_L;
	return *inv_A;
}


/********************************************************************
 * @name	det
 * @brief	Compute the determinant of the matrix
 * @param	matrix - A matrix
 * @return	Determinant of the matrix
 * */
double Matrix::det(const Matrix matrix)
{
	if (matrix.row != matrix.column)
	{
		cout << "Invalid matrix dimension!" << endl;
		exit(0);
	}
	else if (matrix.row == 1)
	{
		return matrix.mat[0][0];
	}
	int n = matrix.row;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		Matrix complement = Matrix::cofactor(matrix, i, 0);
		sum += pow(-1, (i + 1) + 1) * matrix.mat[i][0] * Matrix::det(complement);
	}
	return sum;
}


/********************************************************************
 * @name	cofactor
 * @brief	Compute the cofactor of the matrix
 * @param	matrix - A matrix
 * @param	row - Rows that need to be deleted
 * @param	column - Columns that need to be deleted
 * @return	Cofactor of the matrix
 * */
Matrix Matrix::cofactor(const Matrix matrix, const int row, const int column)
{
	int n = matrix.row;
	Matrix* cofactor = new Matrix(n - 1, n - 1);
	int rowIndex = 0;
	for (int i = 0; i < n; i++)
	{
		int columnIndex = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != row && j != column) {
				cofactor->mat[rowIndex][columnIndex] = matrix.mat[i][j];
				columnIndex++;
			}
		}
		if (i != row)
		{
			rowIndex++;
		}
	}
	return *cofactor;
}