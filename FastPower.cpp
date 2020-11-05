#include<iostream>
using namespace std;
uint64_t FastPower(uint64_t base, uint64_t exponent,uint64_t square=0)
{
	if (square == 0)
		square = base * base;
	if (exponent ==1)
		return base;
	if (exponent == 0)
		return 1;
	if (exponent & 1)
		return base * FastPower(square, exponent >>1, square*square);
	else
		return FastPower(square, exponent >>1, square*square);
}
int main()
{
	uint64_t base = 19;
	uint64_t exponent = 2;
	for(int i=exponent;i<15;i++)
	cout <<"\nExponent: "<<i<<" "<< FastPower(base, i);
}