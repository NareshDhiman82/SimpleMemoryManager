#include <stdio.h> 

#define MaxRequest 8
#define MaxMemory  1024

void* MyMalloc(int Size);
void  Myfree(void*);
char MemBuff[MaxMemory];

typedef struct _FreeList {
	void* Start;  //Corrected typo, missing ';'
	int   Size;
	bool  InUse;
}FreeListTyp;

typedef struct _Metadata {
	FreeListTyp FreeList[MaxRequest + 1]; //Need one extra slot.
}MetadataTyp;

MetadataTyp* Metadata = (MetadataTyp*)MemBuff; //type casting was missing.
void* BuffStart = (char*)Metadata + sizeof(MetadataTyp);

void StartUp()
{
	//initialize all slots with default.
	for (int i = 1; i < MaxRequest; i++) //int missing for i
	{
		Metadata->FreeList[i].InUse = false;
		Metadata->FreeList[i].Size = 0;
		Metadata->FreeList[i].Start = NULL;
	}

	//Iinitialize first Slot with full available chunk 
	Metadata->FreeList[0].Size = MaxMemory - sizeof(Metadata);
	Metadata->FreeList[0].Start = BuffStart;
	Metadata->FreeList[0].InUse = false;
}
void* FindChunk(int Size, int* Slot)
{
	int i = 0;
	void* RetPtr = NULL;
	for (i = 0; i < MaxRequest; i++)
		if ((Metadata->FreeList[i].Size >= Size) && (Metadata->FreeList[i].InUse == false)) //corrected typo in operator
		{
			//Modify next Slot info
			Metadata->FreeList[i + 1].InUse = false;
			Metadata->FreeList[i + 1].Size = Metadata->FreeList[i].Size - Size;
			Metadata->FreeList[i + 1].Start = ((char*)(Metadata->FreeList[i].Start)) + Size;
			Metadata->FreeList[i].InUse = true;
			Metadata->FreeList[i].Size = Size;
			RetPtr = Metadata->FreeList[i].Start;
			//Metadata->FreeList[i].Start += Size; // Commented, This was left in error (Typo)
			*Slot = i;
			break;
		}
	return RetPtr;
}

void findAndFreeChunk(int Slot)
{
	//Mark the slot as free, and perfrom garbage collection.
	Metadata->FreeList[Slot].InUse = false;
	//Mergs consicutive smaller memoery block to single bigger memory block
    //going reverese, Starting from one slot next form the curretn.
	for (int i = (Slot + 1); i > 0; i--)
	{
		if ((Metadata->FreeList[i].InUse == false) &&
			(Metadata->FreeList[i - 1].InUse == false))
		{
			Metadata->FreeList[i - 1].Size += Metadata->FreeList[i].Size;
			Metadata->FreeList[i].Size = 0;
		}
	}
}

void* MyMalloc(int Size)
{
	void* Chunk;
	int    Slot;

	//Find big enough Chunk
	Chunk = FindChunk(Size + sizeof(Slot), &Slot); //Updated to correct typo

	if (!Chunk)
		return NULL; //Error
	else
	{
		//Add Slot index, this will help in quick free operation.
		*((int*)Chunk) = Slot;
	}
	return ((int*)Chunk) + 1; //Updated
}

void Myfree(void* AddrIn)
{

	int* SlotVal = (int*)AddrIn;
	if (SlotVal == NULL) return;  //Updated: Handled the case of NULL pointer 
	SlotVal--;

	findAndFreeChunk(*SlotVal);
}

