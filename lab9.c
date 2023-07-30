#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;

};





// Fill out this structure
struct HashType
{
    struct RecordType* pRecord;
    struct HashType* next;

};




// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz;

    
}






// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, " %c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;

    printf("\nRecords:\n");
        for (i = 0; i < dataSz; ++i)
        {
            
            printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);

        }
    printf("\n\n");
}

// Hashmap insertion function
void insertRecord(struct HashType* hashArray[], struct RecordType* record, int hashSz)
{
    int index = hash(record->id, hashSz);

    // Allocate memory
    struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));

    newNode->pRecord = record;
    newNode->next = NULL;

    // If empty index add the node
    if (hashArray[index] == NULL)
    {
        hashArray[index] = newNode;
    }
    else
    {
        // If the index is not empty still add a node
        struct HashType* current = hashArray[index];
            while (current->next != NULL)
            {
                current = current->next;


            }
            
            current->next = newNode;

    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* hashArray[], int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        struct HashType* current = hashArray[i];
        if (current != NULL)
        {
            printf("index %d -> ", i);

                    while (current != NULL)
                    {
                        struct RecordType* record = current->pRecord;
                        printf("%d, %c, %d -> ", record->id, record->name, record->order);
                        current = current->next;
                    }

            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;
    int hashSz = 31;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hashArray to NULL
    struct HashType* hashArray[hashSz];
    for (int i = 0; i < hashSz; ++i)
    {
        hashArray[i] = NULL;
    }

    // Insert records into the hashmap
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashArray, &pRecords[i], hashSz);

    }

    // Display records in the hash structure
    displayRecordsInHash(hashArray, hashSz);

    // Free the memory for the records and the hashmap
    free(pRecords);

    // Free the hashmap
    for (int i = 0; i < hashSz; ++i)
    {
        struct HashType* current = hashArray[i];
        while (current != NULL)
        {
            struct HashType* temp = current;
            current = current->next;
            free(temp);

        }



    }

    return 0;
}
