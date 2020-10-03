
#include <iostream>
#include<vector>
#include "Islands.h"
#define MIN(A, B) ((A > B) ? (B) : (A))
#define MAX 99999999
using namespace std;

vector<string> split_string(string);

// Complete the jumpingOnClouds function below.
int jumpingOnClouds(vector<int> c) {
    int* jumps = new int[c.size()]();
    int index = 0;
    for (; index < 2; index++)
    {
        if (c[index] == 0)
            jumps[index] = 0;
        else
            jumps[index] = MAX;
    }
    for (index = 2; index < c.size(); index++)
    {
        if (c[index] == 0)
        {
            int minjump = MIN(jumps[index - 1], jumps[index - 2]);
            cout << "\n" << index << " Jumps:" << jumps[index];
            jumps[index] = minjump + 1;     //{ 0 ,0, 1, 0, 0, 1 ,0 }
        }
        else
            jumps[index] = MAX;
    }
    cout << "\n";
    for (int i = 0; i < c.size(); i++)
        cout << jumps[i] << " ";
    return jumps[c.size() - 1];
}

void DetectEdges(vector<vector<int> > Grid, vector<vector<bool> >& visited, int i, int j)
{
    if (i >= 3 || j >= 3||i<=-1||j<=-1)
        return;
    if (Grid[i][j] == 1)
    {
        if (visited[i][j] == false)
            visited[i][j] = true;
        else
            if (visited[i][j])
                return;
        /*DetectEdges(Grid, visited, i, j + 1);
        DetectEdges(Grid, visited, i+1, j );
        DetectEdges(Grid, visited, i - 1, j);
        DetectEdges(Grid, visited, i , j - 1);
        DetectEdges(Grid, visited, i+1, j + 1);
        DetectEdges(Grid, visited, i -1 , j + 1);
        DetectEdges(Grid, visited, i + 1, j - 1);
        DetectEdges(Grid, visited, i -1, j - 1);*/
        DetectEdges(Grid, visited, i, j + 1);
        DetectEdges(Grid, visited, i+1, j );
        DetectEdges(Grid, visited, i-1, j );
        DetectEdges(Grid, visited, i, j -1);
     
    }
    return;
}
/*int NumIslands(vector<vector<int> > Grid, vector<vector<bool> >& visited)
{
    int islands = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Grid[i][j] == 1 && visited[i][j] == false)
            {
                islands++;
                DetectEdges(Grid, visited, i, j);
            }
        }
    }
    return islands;
}*/
int main()
{
    /*vector<vector<int> > Grid{ { 1, 0, 0 },
                              { 1, 1, 0},
                              { 0, 0, 1} };
    vector<vector<bool> > Visited{ { false,false,false },
                              { false,false,false },
                              { false,false,false } };
    int islands = NumIslands(Grid, Visited);
    cout << "\n " << islands;*/
    vector<int> Arr = { 0 ,0, 1, 0, 0, 1 ,0 };
    cout << jumpingOnClouds(Arr);
}   

