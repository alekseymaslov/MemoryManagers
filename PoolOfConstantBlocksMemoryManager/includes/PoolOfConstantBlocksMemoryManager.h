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

#ifndef POOLOFCONSTANTBLOCKSMEMORYMANAGER_H
#define POOLOFCONSTANTBLOCKSMEMORYMANAGER_H

/** 
 *  @brief   this is a base class interface for a memory management 
 *  @details this class provides with a base interface for memory 
 *  management classes that derived from it and forbids copy constructor
 *  to prevent ownership of given pool of memory
 */
class PoolOfConstantBlocksMemoryManager
{
protected:
    void*  memoryPool = nullptr;  /*!< a given memory pool */
    size_t sizeOfPool = 0;        /*!< a given size of pool */
    size_t blockSize  = 0;        /*!< a given block of memory to allocate size */
public:
    //! A constructor.
    /**
       @brief a base constructor for memory management.
       @param[in] inMemoryPool a given memory pool
       @param[in] inSizeOfPool a given size of pool
       @param[in] inBlockSize  a given block of memory to allocate size
    */
    PoolOfConstantBlocksMemoryManager(void* inMemoryPool, size_t inSizeOfPool, size_t inBlockSize) : 
    memoryPool(inMemoryPool), sizeOfPool(inSizeOfPool), blockSize(inBlockSize) {};
    
    //! Removing copy constructor.
    PoolOfConstantBlocksMemoryManager(const PoolOfConstantBlocksMemoryManager&) = delete;
    
    //! A Destructor copy constructor.
    virtual ~PoolOfConstantBlocksMemoryManager(){};
    
    /**
     * @brief a fucntion allocator 
     * @details the function returns pointer for a new block of constant size
     * @return pointer to the memory in a pool
     */
    virtual void* Allocate() = 0;
    
    /**
     * @brief a fucntion free memory 
     * @details the function free previosly allocated memory block
     */
    virtual void Free(void* inPointer) = 0;
};

#endif // POOLOFCONSTANTBLOCKSMEMORYMANAGER_H
