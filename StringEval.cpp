#include<iostream>
#include<string>
#include<sstream>
using namespace std;
double Evaluate(string Expression)
{
	/*if(Expression.size() == 1)
	{
		return Expression[0] - '0';
	}*/
	size_t index = 0;
	while (Expression[index] != '+' && Expression[index] != '-' && index < Expression.size())
	{
		//if ((Expression[index] != '+' || Expression[index] != '-') ) cout << "true\n";
		index++;
		//cout << " " << Expression[index];
	}
	if (index >= Expression.size())
	{
		index = 0;
		while (Expression[index] != '*' && Expression[index] != '/' && index < Expression.size())
		{
			index++;
		}
	}
	if (index >= Expression.size())
	{
		stringstream jako(Expression);
		double number;
		jako >> number;
		return number;
	}
	//cout << index;
	string lstring = Expression.substr(0, index);
	string rstring = Expression.substr(index+1);
	
	//cout << "\n"<<lstring;
	//cout << "\n"<<rstring;
	//cout << "\n"<<Expression[index];
	//return 0;
	switch (Expression[index])
	{
	case '+':
		//cout << "\n" << Expression[index];
		return Evaluate(lstring) + Evaluate(rstring);
	case '-':
		return Evaluate(lstring) - Evaluate(rstring);
	case '*':
		return Evaluate(lstring) * Evaluate(rstring);
	case'/':
		return Evaluate(lstring) / Evaluate(rstring);
	}
}
int main()
{
	string Expression = "2+3*4/3";
	cout<<"\n"<<Evaluate(Expression);
}