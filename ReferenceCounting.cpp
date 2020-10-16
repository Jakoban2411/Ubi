#include<iostream>
using namespace std;
struct Datae
{
	int* Data;
	size_t refcount;
	Datae(int _Data)
	{
		Data = new int(_Data);
		refcount = 0;
	}
	void AddRef()
	{
		refcount++;
	}
	void Release()
	{
		refcount--;
		if (refcount == 0)
			delete Data;
	}
};
struct ContainerHandle
{
	Datae* Obj = nullptr;
	ContainerHandle(int _Data)
	{
		if (Obj == nullptr)
		{
			Obj = new Datae(_Data);
			Obj->AddRef();
		}
	}
	ContainerHandle(const ContainerHandle& Handle)
	{
		Obj = Handle.Obj;
		Obj->AddRef();
	}
	~ContainerHandle()
	{
		Obj->Release();
	}
};
int main()
{
	ContainerHandle* H1=new ContainerHandle(17);
	ContainerHandle* H2=new ContainerHandle(*H1);
	cout <<"\n"<< (H2->Obj->refcount);
	cout <<"\n"<< H2->Obj->Data;
	cout << "\n" << H1->Obj->Data;
	cout << "\n" << H2->Obj->refcount;
	delete(H1);
	cout << "\n" << H2->Obj->refcount;
	cout << "\n" << H2->Obj->Data;
}