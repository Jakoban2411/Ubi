#include<iostream>
#include<thread>
using namespace std;
static int referenceCount=0;
template<typename T>
struct SharedPtr
{
	T* m_data;
	SharedPtr( T* _data)
	{
		m_data = _data;
		::referenceCount++;
	}
	SharedPtr<T>(const SharedPtr<T> &_Copy)
	{
		m_data = _Copy.m_data;
		::referenceCount++;
	}
	~SharedPtr()
	{
		::referenceCount--;
		cout << "\n Reference count decrement";
		if (::referenceCount == 0)
		{
			cout << "\n Deleting";
			delete m_data;
		}
	}
	SharedPtr<T> next;
};
void threadfunc(SharedPtr<int>_ptr)
{
	int x= *(_ptr.m_data);
	cout << "\n I am not gonna do nothing with "<<x;
	cout <<"\n Ref:"<< ::referenceCount;
}
int main()
{
	int j = 10;
	int* pj = new int(j);
	SharedPtr<int> mysmrtptr(pj);
	SharedPtr<int> mysmrtptr1(pj);
	SharedPtr<int> mysmrtptr2(pj);
	mysmrtptr.next = mysmrtptr1;
	mysmrtptr1.next = mysmrtptr2;
	mysmrtptr2.next = mysmrtptr;
	cout << "\n Reference:" << ::referenceCount;
	/*thread t1(threadfunc, mysmrtptr);
	thread t2(threadfunc, mysmrtptr);
	thread t3(threadfunc, mysmrtptr);
	cout << "\n Reference:" << ::referenceCount;
	t1.join();
	t2.join();
	t3.join();*/
}