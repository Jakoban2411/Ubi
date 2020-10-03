#include<iostream>
#include<vector>
#include<algorithm>
#include<Windows.h>
#define N 3
using namespace std;
vector<vector<int>>MatrixA(N, vector<int>(N, 0));
vector<vector<int>>MatrixB(N, vector<int>(N, 0));
struct MatrixCoordinates
{
	int mA_i;
	int mB_j;
	MatrixCoordinates(int _Row, int _Column) :mA_i(_Row), mB_j(_Column)
	{
	}
};
int MultiThreadmatrixMultiplication(LPVOID MultiplyRowColumn)
{
	MatrixCoordinates _MultiplyRowColumn = *(MatrixCoordinates*)MultiplyRowColumn;
	int result = 0;
	for (size_t columnIndex = 0, rowIndex = 0;rowIndex<N && columnIndex < N;rowIndex++, columnIndex++)
	{
		//cout << "\n MUltiplying " << _MultiplyRowColumn.mA_i << " and " << _MultiplyRowColumn.mB_j;
		result += MatrixA[_MultiplyRowColumn.mA_i][columnIndex] * MatrixB[rowIndex][_MultiplyRowColumn.mB_j];
	}
	return result;
}
int main()
{
	
	cout << "\n MatrixA:\n";
	for (size_t rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < N; columnIndex++)
			cin >> MatrixA[rowIndex][columnIndex];
	}
	cout << "\n MatrixB:\n";
	for (size_t rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < N; columnIndex++)
			cin >> MatrixB[rowIndex][columnIndex];
	}
	vector<vector<int>>MatrixC(N, vector<int>(N, 0));
	vector<DWORD> myThreadIDs;
	vector<HANDLE> myThreadHandles;
	vector<MatrixCoordinates> Coords;
	for (int rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < N; columnIndex++)
		{
			Coords.push_back(MatrixCoordinates(rowIndex, columnIndex));
		}
	}
	int index = 0;
	for (int rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < N; columnIndex++)
		{
			DWORD myThreadID;
			HANDLE myHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MultiThreadmatrixMultiplication, &Coords[index], 0, &myThreadID);
			myThreadHandles.push_back( myHandle);
			myThreadIDs.push_back(myThreadID);
			index++;
		}
	}
	HANDLE* myHandles = new HANDLE[myThreadHandles.size()]();
	std::copy(myThreadHandles.begin(), myThreadHandles.end(), myHandles);
	int WaitRes = WaitForMultipleObjects(myThreadHandles.size(), myHandles, true, INFINITE);
	index = 0;
	for (size_t rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < N; columnIndex++)
		{
			DWORD retValue ;
			GetExitCodeThread(myThreadHandles[index], &retValue);
			MatrixC[rowIndex][columnIndex] = (int)retValue;
			index++;
		}
	}
	cout << "\n";
	for (size_t rowIndex = 0; rowIndex < N; rowIndex++)
	{
		for (size_t columnIndex = 0; columnIndex < N; columnIndex++)
		{
			cout <<"\t"<< MatrixC[rowIndex][columnIndex];
		}
		cout << "\n";
	}
	for (size_t index = 0; index < myThreadHandles.size(); index++)
		CloseHandle(myThreadHandles[index]);
}