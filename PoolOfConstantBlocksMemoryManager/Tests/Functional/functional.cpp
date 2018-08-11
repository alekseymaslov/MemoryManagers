#include <iostream>
#include <stdexcept>
#include "TablePoolOfConstantBlocksMemoryManager.h"

using namespace std;

const size_t uinttCount = 17;
const size_t blockSize = sizeof(uint64_t) * uinttCount;
const size_t poolSize = 1024;
uint8_t memoryPool[poolSize] = {0};
const size_t blocksCount = 7; 
uint64_t* arrayOfMemory[blocksCount] = {nullptr};

void SimpleAllocationFree(TablePoolOfConstantBlocksMemoryManager& manager)
{
    for(size_t i = 0; i < blocksCount; i++ )
    {
        arrayOfMemory[i] = new(manager.Allocate()) uint64_t[uinttCount];
    }
    
    for(size_t i = 0; i < blocksCount; i++ )
    {
        manager.Free(arrayOfMemory[i]);
    }
    
    std::cout << "SimpleAllocationFree: Ok!" << std::endl;
}

void CheckSumAllocation(TablePoolOfConstantBlocksMemoryManager& manager)
{
    for(size_t i = 0; i < blocksCount; i++ )
    {
        arrayOfMemory[i] = new(manager.Allocate()) uint64_t[uinttCount];
        for(size_t j = 0; j < uinttCount; j++ )
        {
            uint64_t* currentPtr = arrayOfMemory[i];
            currentPtr[j] = i + 1;
        }
    }
    
    for(size_t i = 0; i < blocksCount; i++)
    {
        const size_t toCheck = i + 1;  
        for(size_t j = 0; j < uinttCount; j++ )
        {
            uint64_t* currentPtr = arrayOfMemory[i];
            if(toCheck != currentPtr[j])
            {
                throw std::runtime_error("CheckSumAllocation: block compare fails.");
            }
        }
    }
    std::cout << "CheckSumAllocation: Ok!" << std::endl;
}

void CheckSumAllocationFree(TablePoolOfConstantBlocksMemoryManager& manager)
{
    const size_t firstArrayToFree = 2;
    const size_t secondArrayToFree = 5;
    manager.Free(arrayOfMemory[firstArrayToFree]);
    manager.Free(arrayOfMemory[secondArrayToFree]);
    
    for(size_t i = 0; i < blocksCount; i++)
    {
        if((firstArrayToFree == i) || (firstArrayToFree == i))
        {
            continue;
        }
        
        const size_t toCheck = i + 1;  
        for(size_t j = 0; j < uinttCount; j++ )
        {
            uint64_t* currentPtr = arrayOfMemory[i];
            if(toCheck != currentPtr[j])
            {
                throw std::runtime_error("CheckSumAllocation: block compare fails.");
            }
        }
        manager.Free(arrayOfMemory[i]);
    }
    std::cout << "CheckSumAllocationFree: Ok!" << std::endl;
}

int main()
{
    TablePoolOfConstantBlocksMemoryManager manager(memoryPool, poolSize, blockSize);
    try
    {
        SimpleAllocationFree(manager);
        CheckSumAllocation(manager);
        CheckSumAllocationFree(manager);
    }
    catch(std::runtime_error exep)
    {
        std::cout<<exep.what()<<endl;
    }
    
    std::cout << "End!" << std::endl;
    return 0;
}