#define MaxRequest 64
#define MaxMemory  1024

void* MyMalloc(int Size);
void  Myfree(void*);

char MemBuff[MaxMemory];

typedef struct _FreeList {
	void* Start
		int   Size;
	bool  InUse;
}FreeListTyp;

typedef struct _Metadata {
	FreeListTyp FreeList[MaxRequest];
}MetadataTyp;

MetadataTyp* Metadata = MemBuff;
void* BuffStart = Metadata + sizeof(Metadata);

void StartUp();
{
	//initialize all slots with default.
	for (i = 1; i < MaxRequest; i++)
	{
		Metadata->FreeList[i].InUse = FALSE;
		Metadata->FreeList[i].Size = 0;
		Metadata->FreeList[i].Start = NULL;
	}

	//initialize first Slot with full avalible chunk 
	Metadata->FreeList[0].Size = MaxMemory - sizeof(Metadata);
	Metadata->FreeList[0].Start = BuffStart;
	Metadata->FreeList[0].InUse = FALSE;

}
void* FindChunk(int Size, int* Slot)
{
	int i = 0;
	void* RetPtr = NULL;
	for (i = 0; i < MaxRequest; i++)
		if ((Metadata->FreeList[i].Size <= Size) && (Metadata->FreeList[i].InUse == FALSE))
		{
			Metadata->FreeList[i].InUse = TRUE;
			Metadata->FreeList[i].Size -= Size;
			RetPtr = Metadata->FreeList[i].Start;
			Metadata->FreeList[i].Start += Size;
			*Slot = i;
		}
	return RetPtr;
}

void findAndFreeChunk(int Slot)
{

	Metadata->FreeList[Slot].InUse = FALSE;

	//Check if next availble Slot is not inuse if so then merge
	if (Metadata->FreeList[Slot + 1].InUse == FASLE)
	{
		Metadata->FreeList[Slot].Size = Metadata->FreeList[Slot + 1].Size
	}

	//Check if previous availble Slot is not inuse if so then merge
	if (Metadata->FreeList[Slot - 1].InUse == FASLE)
	{
		Metadata->FreeList[Slot - 1].Size = Metadata->FreeList[Slot].Size
	}

}

void* MyMalloc(int Size)
{
	void* Chunk;
	int    Slot;

	//Find bing enough Chunk
	Chunk = FindChunk(Size + sizeof(slot), &Slot
}
if (!Chunk)
return NULL; //Error
else
{
	*((int*)Chunk) = Slot;
	((int*)Chunk)++;
}
return Chunk;
}

void Myfree(void* AddrIn)
{

	int* SlotVal = (int*)AddrIn;
	SlotVal--;

	findAndFreeChunk(*SlotVal);

}