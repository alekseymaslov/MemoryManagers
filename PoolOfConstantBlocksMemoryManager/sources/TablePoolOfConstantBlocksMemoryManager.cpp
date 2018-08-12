/*
 * Copyright 2018 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include <iostream>
#include <stdexcept>

#include "TablePoolOfConstantBlocksMemoryManager.h"


using namespace std;


inline void* MemoryShiftForward(void* inMemory, uintptr_t shift)
{
    return ((static_cast<uint8_t*>(inMemory)) + shift);
}


TablePoolOfConstantBlocksMemoryManager::TablePoolOfConstantBlocksMemoryManager(void* inMemoryPool, size_t inSizeOfPool, 
size_t inBlockSize):
PoolOfConstantBlocksMemoryManager(inMemoryPool, inSizeOfPool, inBlockSize)
{
    if(nullptr == inMemoryPool)
    {
        throw invalid_argument("nullptr recived as a memory pointer.");
    }
   
    if(0 == blockSize)
    {
        throw invalid_argument("0 block size recived.");
    }
    
    if((tableNodeSize + blockSize) > sizeOfPool)
    {
        throw invalid_argument("given insufficient amount of memory.");
    }
   
    maxBlockCount = (sizeOfPool/(blockSize + tableNodeSize));
    memoryStartOffset =  maxBlockCount * tableNodeSize;
    memoryStartPointer = MemoryShiftForward(memoryPool, memoryStartOffset);
    memoryEndPointer   = MemoryShiftForward(memoryPool, sizeOfPool);
}

TablePoolOfConstantBlocksMemoryManager::~TablePoolOfConstantBlocksMemoryManager()
{
#ifdef DEBUG
    if(0 != blockCounter)
    {
        cout<<"WARNING: not all memory was freed."<<endl;
    }
#endif
}

void* TablePoolOfConstantBlocksMemoryManager::Allocate()
{
    void* pointerToPool = nullptr;
    if(0 != tableCounter)
    {
        tableCounter--;
        void* tableNode = MemoryShiftForward(memoryPool, tableCounter * tableNodeSize);
        uintptr_t* freeFragment = static_cast<uintptr_t*>(tableNode);
        pointerToPool = MemoryShiftForward(memoryPool, (*freeFragment));
    }
    else
    {
        if(blockCounter >= maxBlockCount)   
        {
            throw bad_alloc();
        }
        uintptr_t newBlockSift = (blockCounter * blockSize) + memoryStartOffset;
        pointerToPool = MemoryShiftForward(memoryPool, newBlockSift);
        blockCounter++;
    }
#ifdef DEBUG
    cout<<"allocate:"<<(size_t)(pointerToPool)<<std::endl;
#endif
    return pointerToPool;
}

void TablePoolOfConstantBlocksMemoryManager::Free(void* inPointer)
{
    if(nullptr == inPointer)
    {
        throw invalid_argument("attempt to free nullptr.");
    }
  

    size_t currentOffset = (static_cast<uint8_t*>(inPointer) - static_cast<uint8_t*>(memoryStartPointer));
    if((inPointer < memoryStartPointer) || (inPointer > memoryEndPointer) ||
       (0 == blockCounter) || (0 != (currentOffset % blockSize)))
    {
        throw invalid_argument("attempt to free memory that was not allocated.");
    }
#ifdef DEBUG
    cout<<"free    :"<<(size_t)(inPointer)<<std::endl;
#endif 
    uintptr_t memoryCursor = ((blockCounter - 1) * blockSize) + memoryStartOffset;
    void* lastTakenMemory = MemoryShiftForward(memoryPool, memoryCursor);
    if(inPointer == lastTakenMemory)
    {
        blockCounter--;
        if(tableCounter == blockCounter)
        {
            /* NOTE: reset table for case when last block in sequance is freed last */
            tableCounter = blockCounter = 0;
        }
    }
    else
    {
        uintptr_t* freeFragment  = new(MemoryShiftForward(memoryPool, tableCounter * tableNodeSize)) uintptr_t;
        /*NOTE: store memory shift instead of pointer itself of to avoid reinterpret_cast*/
        uint8_t*   uptrMemory    = static_cast<uint8_t*>(memoryPool);
        uint8_t*   uptrInPointer = static_cast<uint8_t*>(inPointer);
        (*freeFragment) = (uptrInPointer - uptrMemory);
        tableCounter++;
    }
}


