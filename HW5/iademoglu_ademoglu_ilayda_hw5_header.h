class Matrix{
private:
	int rowNumber;
	int columnNumber;
	int ** elements;

	/* Elements of the matrix must be stored in a dynamic matrix of integers with rowNumber rows and columnNumber elements per row. 
	Since the matrix is dynamic one, as elements, you will need to use a pointer to pointer. */
public:
	Matrix();
	Matrix(int rowNum, int columnNum, int init);
	Matrix(const Matrix & copy);
	~Matrix();
	int getRowNumber() const;
	int getColumnNumber() const;
	int getElementAt(int row, int column) const;
	void setElementAt(int row,int column, int value);
	void print();
	void deletematrix();
	const Matrix & operator =(const Matrix & rhs);
	bool equals(const Matrix & a, const Matrix & b);
	bool operator==(const Matrix& b);





};