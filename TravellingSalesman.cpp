#include<iostream>
#include<cmath>
#include<vector>
#define MIN(A,B) (A>B)?B:A
#define M_PI   3.14159
using namespace std;
double toRadians(const double degree)
{
    double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

double distance(double lat1, double long1,
    double lat2, double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    double dlong = long2 - long1;
    double dlat = lat2 - lat1;

    double ans = pow(sin(dlat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));
    double R = 6378.137;
    ans = ans * R;

    return ans;
}
int MinNotVisited(vector<double> Cities, vector<bool> visited, int currCityIndex)
{
    int MinDistance = 999999;
    int MinIndex=0;
    for (uint32_t index = 0; index < Cities.size(); index++)
    {
        if (index != currCityIndex && visited[index] == false)
        {
            if (Cities[index] < MinDistance)
            {
                MinDistance = Cities[index];
                MinIndex = index;
            }
        }
        //cout << "\n" <<Cities[MinIndex] <<" "<<MinIndex<<" "<<MinDistance;
    }
    return MinIndex;
}
double TravellingSalesman(vector<vector<double>> Displacement,vector<int>&MinCityPath, int numCities)
{
    double CurrMin = 0;
    double AbsoluteMin = 999999;
    for (int i = 0; i < numCities; i++)
    {
        vector<int>LocalMinPath;
        vector<bool> visited(numCities, false);
        visited[i] = true;
        CurrMin = 0;
        int visitedcities = 1;
        int indexNotVisitedMinimum = i;
        LocalMinPath.push_back(i);
        int currcity;
        while (visitedcities != numCities)
        {
            currcity = indexNotVisitedMinimum;
            indexNotVisitedMinimum = MinNotVisited(Displacement[indexNotVisitedMinimum], visited, currcity);
            visitedcities++;
            visited[indexNotVisitedMinimum] = true;
            LocalMinPath.push_back(indexNotVisitedMinimum);
            CurrMin += Displacement[currcity][indexNotVisitedMinimum];
        }
        if (AbsoluteMin > CurrMin)
        {
            AbsoluteMin = CurrMin;
            MinCityPath = LocalMinPath;
        }
    }
    return AbsoluteMin;
}
int main()
{
    unsigned int citiesnum = 4;
    vector<vector<double>>Coordinates(citiesnum, vector<double>(2, 0));
    for (uint32_t i = 0; i < citiesnum; i++)
    {
        cout << "Enter Latitude and Longitude: ";
        cin >> Coordinates[i][0];
        cin >> Coordinates[i][1];
        cout << "\n";
    }
    vector<vector<double>> Displacement(citiesnum, vector<double>(citiesnum, 0));
    int currcitydistance = 0;
    for (uint32_t i = 0; i < citiesnum; i++)
    {
        Displacement[i][i] = 0;
        for (int j = i + 1; j < citiesnum; j++)
        {
            double currcitydistance = distance(Coordinates[i][0], Coordinates[i][1], Coordinates[j][0], Coordinates[j][1]);
            Displacement[i][j] = currcitydistance;
            Displacement[j][i] = currcitydistance;
        }
    }
    //vector<vector<double>> Dis = { {0,180,3,50,17},{5.0,0,2,19,20},{23,5,0,71,100},{1,9,150,0,80},{12,60,20,40,0} };
    /*vector<vector<double>> Dis = { {0,180,3},
        {5.0,0,2},
        {23,5,0} };*/
   // cout << "\n " << TravellingSalesman(Dis, 3);
    vector<int>MinCityPath;
    cout << "\n Min Distance: " << TravellingSalesman(Displacement, MinCityPath,citiesnum);
    cout << "\n Travel Path ";
    for (int i = 0; i < MinCityPath.size(); i++)
        cout <<"\n"<< Coordinates[MinCityPath[i]][0]<<" "<<Coordinates[MinCityPath[i]][1];
    return 0;
}