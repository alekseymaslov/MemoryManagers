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

#ifndef POOLOFBLOCKSMEMORYMANAGERTABLE_H
#define POOLOFBLOCKSMEMORYMANAGERTABLE_H

#include "PoolOfConstantBlocksMemoryManager.h"


/** 
 *  @brief   This class provides with memory management for constant size
 *  blocks allocation 
 *  @details This class use table management approach with is means that
 *  in start of given pool will be placed table for memory management  with
 *  is store shifts to free fragment of memory pool. The table size can be
 *  calculated by a formula: pool/(block size + sizeof(size_t)).
 *  Witch means that minimal size for usage of the class is equal to a
 *  (block size + sizeof(size_t)). 
 *  -----------------------------------------------------------------
 *  |                 |           |           |         |           |
 *  | Table of shifts | Block one | Block two |   ...   | Block   N |
 *  |                 |           |           |         |           |
 *  -----------------------------------------------------------------
 *  Advantages of the approach is quick memory allocation and free. 
 *  Disadvantages is usage of memory for table of shifts witch is proves to
 *  be inefficient, from memory usage standpoint, when block size less sizeof(size_t).
 */
class TablePoolOfConstantBlocksMemoryManager : public PoolOfConstantBlocksMemoryManager
{
    void*     memoryStartPointer = nullptr;       /*!< a memory point in a pool with allocation is start */
    void*     memoryEndPointer   = nullptr;       /*!< a memory point in a pool with allocation is end */
    size_t    tableNodeSize      = sizeof(size_t);/*!< a size of node in a table */
    size_t    tableCounter       = 0;             /*!< a counter for table nodes */
    size_t    blockCounter       = 0;             /*!< a counter for allocated blocks */
    size_t    maxBlockCount      = 0;             /*!< a maximum possible allocated blocks */
    uintptr_t memoryStartOffset  = 0;             /*!< a memory offset in a pool with allocation is start */
public:

    //! A constructor.
    /**
       @brief a base constructor for table memory management.
       @details   constructor for table memory management approach.
       Constructor can throw exception if given data if no valid
       @param[in] inMemoryPool a given memory pool
       @param[in] inSizeOfPool a given size of pool
       @param[in] inBlockSize  a given block of memory to allocate size
    */
    TablePoolOfConstantBlocksMemoryManager(void* inMemoryPool, size_t inSizeOfPool, size_t inBlockSize);
    
    //! A Destructor copy constructor.
    ~TablePoolOfConstantBlocksMemoryManager();
    
    /**
     * @brief a fucntion allocator 
     * @details the function returns pointer for a new block of constant size
     * @return pointer to the memory in a pool throw exception if memory could
     * not be allocated
     */
    void* Allocate() override;

    /**
     * @brief a fucntion free memory 
     * @details the function free previosly allocated memory block, can throw
     * exception if given pointer equal to nullptr or out of range memoryStartPointer 
     * and memoryEndPointer or if none previos block where allocated.
     * WARNING: do not try to free previosly freed memory
     */
    void Free(void* inPointer) override;
};

#endif // POOLOFBLOCKSMEMORYMANAGERTABLE_H
