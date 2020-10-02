// SimpleMemoryManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

extern void StartUp();
extern void* MyMalloc(int SizeIn);
extern void  Myfree(void* AddrIn);

#define MAXRETVAL 10
void* Ret[MAXRETVAL];

void PrepareTest()
{
	for (int i = 0; i < MAXRETVAL ; i++)
		Ret[i] = NULL;
}

void DiaplayRetVal()
{
	for (int i = 0; i < MAXRETVAL; i++)
		printf("Ret[%d] = %#x\n", i, (int)Ret[i]);
}

int main(void)
{
	

	//Setup the Mem Manager
	StartUp();

	//Test1:  1 Allocation and 1 Free ; Free is in order.
	PrepareTest();
	Ret[0] = MyMalloc(2);
	Myfree(Ret[0]);
	DiaplayRetVal();

	//Test2:  2 Allocation and 2 Free ; Free is in order.
	PrepareTest(); 
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(2);
	Myfree(Ret[0]);
	Myfree(Ret[1]);
	DiaplayRetVal();

	//Test3:  4 Allocation and 4 Free ; Free is in order.
	PrepareTest(); 
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Myfree(Ret[0]);
	Myfree(Ret[1]);
	Myfree(Ret[2]);
	Myfree(Ret[3]);
	DiaplayRetVal();

	//Test4:  8 Allocation and 8 Free ; Free is in order.
	PrepareTest(); 
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Ret[4] = MyMalloc(4);
	Ret[5] = MyMalloc(8);
	Ret[6] = MyMalloc(4);
	Ret[7] = MyMalloc(8);
	Myfree(Ret[0]);
	Myfree(Ret[1]);
	Myfree(Ret[2]);
	Myfree(Ret[3]);
	Myfree(Ret[4]);
	Myfree(Ret[5]);
	Myfree(Ret[6]);
	Myfree(Ret[7]);
	DiaplayRetVal();


	//Test4:  10 Allocation and 10 Free ; Free is in order.
	//Expected: 9th, and 10th Allocation return NULL (Failed)
	PrepareTest(); 
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Ret[4] = MyMalloc(4);
	Ret[5] = MyMalloc(8);
	Ret[6] = MyMalloc(4);
	Ret[7] = MyMalloc(8);
	Ret[8] = MyMalloc(8);
	Ret[9] = MyMalloc(8);
	Myfree(Ret[0]);
	Myfree(Ret[1]);
	Myfree(Ret[2]);
	Myfree(Ret[3]);
	Myfree(Ret[4]);
	Myfree(Ret[5]);
	Myfree(Ret[6]);
	Myfree(Ret[7]);
	Myfree(Ret[8]);
	Myfree(Ret[9]);
	DiaplayRetVal();

	//Test5:  8 Allocation and 8 Free ; Free is in Reverse order.
	PrepareTest();
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Ret[4] = MyMalloc(4);
	Ret[5] = MyMalloc(8);
	Ret[6] = MyMalloc(4);
	Ret[7] = MyMalloc(8);
	Myfree(Ret[7]);
	Myfree(Ret[6]);
	Myfree(Ret[5]);
	Myfree(Ret[4]);
	Myfree(Ret[3]);
	Myfree(Ret[2]);
	Myfree(Ret[1]);
	Myfree(Ret[0]);
	DiaplayRetVal();

	//Test6:  8 Allocation and 8 Free ; Free is out of order.
	PrepareTest();
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Ret[4] = MyMalloc(4);
	Ret[5] = MyMalloc(8);
	Ret[6] = MyMalloc(4);
	Ret[7] = MyMalloc(10);
	Myfree(Ret[7]);
	Myfree(Ret[6]);
	Myfree(Ret[5]);
	Myfree(Ret[2]);
	Myfree(Ret[1]);
	Myfree(Ret[0]);
	Myfree(Ret[3]);
	Myfree(Ret[4]);
	DiaplayRetVal();

	//Test7:  8 Allocation and 8 Free ; Last request consumes all remaing memory to cover corner case
	//        Free is out of order.
	PrepareTest();
	Ret[0] = MyMalloc(4);
	Ret[1] = MyMalloc(8);
	Ret[2] = MyMalloc(4);
	Ret[3] = MyMalloc(8);
	Ret[4] = MyMalloc(4);
	Ret[5] = MyMalloc(8);
	Ret[6] = MyMalloc(4);
	Ret[7] = MyMalloc(944);
	Myfree(Ret[7]);
	Myfree(Ret[6]);
	Myfree(Ret[5]);
	Myfree(Ret[2]);
	Myfree(Ret[1]);
	Myfree(Ret[0]);
	Myfree(Ret[3]);
	Myfree(Ret[4]);
	DiaplayRetVal();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
