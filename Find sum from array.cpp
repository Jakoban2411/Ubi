#include<iostream>
#include<vector>
using namespace std;
bool sum(vector<int> set1,vector<int> set2)
{
	int sum1 = 0;
	int sum2 = 0;
	for (size_t i = 0; i < set1.size(); i++)
		sum1 += set1[i];
	for (size_t i = 0; i < set2.size(); i++)
		sum2 += set2[i];
	if (sum1 == sum2)
		return true;
	return false;
}
void permutation(vector<int>set, vector<int>set2,bool &display)
{
	if (set.size() == 0)
		return;
	if (display == true)
		return;
	auto temp = set;
	for (size_t i = 0; i < set.size(); i++)
	{
		
		set2.push_back(set[i]);
		set.erase(set.begin()+i);
		if (sum(set, set2) && display==false)
		{
			for (size_t i = 0; i < set.size(); i++)
				cout << "	" << set[i];
			cout << "		";
			for (size_t i = 0; i < set2.size(); i++)
				cout << " " << set2[i];
			display = true;
			return;
		}
		else
		{
			permutation(set, set2,display);
		}
		set = temp;
	}
}
int main()
{
	vector<int> set = {4,4,2,2,2,2};
	vector<int> set2;
	bool display = false;
	permutation(set,set2,display);
}