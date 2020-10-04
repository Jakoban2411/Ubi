#include<iostream>
#define MAX 20
using namespace std;
struct CustomMatrix
{
	int Matrix[MAX][MAX];
	int row;
	int column;
	CustomMatrix(int r = 3, int c = 3)
	{
		row = r;
		column = c;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				Matrix[i][j] = 0;
	}
	CustomMatrix Transpose()
	{
		CustomMatrix Transpose(row,column);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0  ; j < column; j++)
			{
				Transpose.Matrix[i][j] = Matrix[j][i];
			}
		}
		return Transpose;
	}
	void DeleteRow(int r)
	{
		if (row == 1)
		{
			cout << "\n Only 1 row left. Cannot Delete";
			return;
		}
		if (r >= row)
		{
			cout << "\n No such row\n";
		}
		for (int i = r; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				Matrix[i][j] = Matrix[i + 1][j];
			}
		}
		row--;
	}
	void DeleteCol(int c)
	{
		if (column == 1)
		{
			cout << "\n Only 1 column left. Cannot Delete";
			return;
		}
		if (c >= column)
		{
			cout << "\n No such column\n";
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = c; j < column; j++)
			{
				Matrix[i][j] = Matrix[i][j+1];
			}
		}
		column--;
	}
	void InsertRow()
	{
		if (row >= MAX)
		{
			cout << "\n Max possible limit. Make a new Object";
			return;
		}
		cout << "Enter the new row of " << column << " elements\n";
		for (int j = 0; j < column; j++)
			cin >> Matrix[row][j];
		row++;
		DisplayMatrix();
	}
	void InsertCol()
	{
		if (column >= MAX)
		{
			cout << "\n Max possible limit. Make a new Object";
			return;
		}
		cout << "Enter the new column of " << row << " elements\n";
		for (int i = 0; i < row; i++)
			cin >> Matrix[i][column];
		column++;
		DisplayMatrix();
	}
	void InsertatRow(int r)
	{
		if (r >= row)
		{
			cout << "\n Please use Normal Insert";
			return;
		}
		for (int i = row; i >= r; i--)
		{
			for (int j = 0; j < column; j++)
				Matrix[i][j] = Matrix[i - 1][j];
		}
		cout << "Enter the new row of " << column << " elements\n";
		for (int j = 0; j < column; j++)
			cin >> Matrix[r][j];
		row++;
		DisplayMatrix();
	}
	void InsertatCol(int c)
	{
		if (c >= column)
		{
			cout << "\n Please use Normal Insert";
			return;
		}
		for (int j = column; j >=c ; j--)
		{
			for (int i = 0; i < row; i++)
				Matrix[i][j] = Matrix[i][j-1];
		}
		for (int i = 0; i < row; i++)
			cin >> Matrix[i][c];
		column++;
		DisplayMatrix();
	}
	void DisplayMatrix()
	{
		cout << "\n Mat: \n";
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
				cout << Matrix[i][j] << "	";
			cout << "\n";
		}
	}
};
int main()
{
	CustomMatrix Mat,TMat;
	for (int i = 0; i < Mat.row; i++)
	{
		for (int j = 0; j < Mat.column; j++)
			Mat.Matrix[i][j] = i + j;
	}
	cout << "\n Current Mat: \n";
	Mat.DisplayMatrix();
	cout << "\n Select 1.Insert Row at end 2.Insert Col at end 3.Delete indexed Column 4.Delete indexed Row 5.Insert at indexed column 6.Insert at indexed row 7.Transpose 8.Exit Any other for display\n";
	int choice;
	bool loop = true;
	int index;
	while (loop)
	{
		cin >> choice;
		switch (choice)
		{
		case 1:
			Mat.InsertRow();
			break;
		case 2:
			Mat.InsertCol();
			break;
		case 3:
			cout << "\n Index: ";
			cin >> index;
			Mat.DeleteCol(index);
			Mat.DisplayMatrix();
			break;
		case 4:
				cout << "\n Index: ";
				cin >> index;
				Mat.DeleteRow(index);
				Mat.DisplayMatrix();
				break;
		case 5:
				cout << "\n Index: ";
				cin >> index;
				Mat.InsertatCol(index);
				Mat.DisplayMatrix();
				break;
		case 6:
			cout << "\n Index: ";
			cin >> index;
			Mat.InsertatRow(index);
			Mat.DisplayMatrix();
			break;
		case 7:
				TMat = Mat.Transpose();
				cout << "\n Here be the transpose:\n";
				TMat.DisplayMatrix();
				break;
		case 8:
			loop = false;
			break;
		default:
			Mat.DisplayMatrix();
			break;
		}
	}
}