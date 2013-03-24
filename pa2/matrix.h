/*
 *	Robert Perlstein
 *	101130094
 *	Advanced Programming
 *	Spring 2013
 *	HW2 - Matrices, Template Specialization, and Shortest Path 
 *	
 *	This program computes the shortest path on a graph G=(V,U),
 *	from vertices u to v using the properties of an
 *	adjacency matrix and matrix multiplication.
 *	The user provides a specifically formatted input
 *	file that represents the graph by its vertex set,
 *	and edge set. Using this data, a specialized
 *	template class, Matrix<int> is initialized, and the
 *	operations required to determine the shortest path
 *	are performeed on this object.
 */

/******** PRE/POST CONDITIONS *************************************************
Matrix(		const size_type&	rows,
			const size_type&	cols );
PRE: None
POST: A matrix object is initialized to dimensions rows x cols

Matrix(		const Matrix<Type>&	matrix );
PRE: None
POST: A matrix object is initialized to dimensions rows x cols

virtual ~Matrix();

const size_type				getRowSize() const;
const size_type				getColSize() const;

Matrix<Type>				operator *	(const Matrix<Type>& matrix) const;
Type*						operator []	(const int& index) const;
Matrix<Type>&				operator =	(const Matrix<Type>& matrix);

template<Type>
friend std::ostream&		operator <<	(	std::ostream& out,
											const Matrix<Type>& matrix);

******************************************************************************/

#ifndef _matrixTem
#define _matrixTem

#include <iostream>
#include <iomanip>

// General Matrix template
template <typename Type>
class Matrix {
	typedef unsigned			size_type;

public:
	Matrix( const size_type&	rows,
			const size_type&	cols );
	Matrix( const Matrix<Type>&	matrix );
	virtual ~Matrix();

	const size_type				getRowSize() const;
	const size_type				getColSize() const;

	Matrix<Type>				operator *	(const Matrix<Type>& matrix) const;
	Type*						operator []	(unsigned size_type) const;
	Matrix<Type>&				operator =	(const Matrix<Type>& matrix);

	template<Type>
	friend std::ostream&		operator <<	(std::ostream& out,
											 const Matrix<Type>& matrix);

private:
	Matrix();
	size_type					rowSize;
	size_type					colSize;
	Type**						matrix;
};



// Specialized int Matrix template
template <>
class Matrix<int> {
	typedef unsigned			size_type;

public:
	Matrix( const size_type&	rows,
			const size_type&	cols );
	Matrix( const Matrix<int>&	matrix );
	virtual ~Matrix();

	const size_type				getRowSize() const;
	const size_type				getColSize() const;

	Matrix<int>					operator *	(const Matrix<int>& matrix) const;
	int*						operator []	(unsigned size_type) const;
	Matrix<int>&				operator =	(const Matrix<int>& matrix);

	template<int>
	friend std::ostream&		operator <<	(std::ostream& out,
											 const Matrix<int>& matrix);

private:
	Matrix();
	size_type					rowSize;
	size_type					colSize;
	int**						matrix;
};

#include "matrix.tem"


#endif
