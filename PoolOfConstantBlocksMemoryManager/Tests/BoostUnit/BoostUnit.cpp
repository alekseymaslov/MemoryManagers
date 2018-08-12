
#define BOOST_TEST_MODULE TablePoolOfConstantBlocksMemoryManager_test TableManager

#include <iostream>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <TablePoolOfConstantBlocksMemoryManager.h>


const size_t uinttCount = 64;
const size_t blockSize = sizeof(uint64_t) * uinttCount;
const size_t poolSize = 1024 * 1024 * 2;
uint8_t memoryPool[poolSize] = {0};
    
BOOST_AUTO_TEST_SUITE(TableManager)

BOOST_AUTO_TEST_CASE( TestConstructor_give_nullptr )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(nullptr, 0, 0);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestConstructor_give_zeroPoolSize )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, 0, blockSize);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestConstructor_give_zeroBlockSize )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, 0);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestConstructor_give_blockSizeMoreThanPool )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, 24, 30);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestConstructor_give_poolSizeLessThanSizeT )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, sizeof(size_t) - 1, 1);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestAllocate_request_checkSimpleAllocationMemory)
{
    bool isExcep = true;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        auto pointer = mManager.Allocate();
    }
    catch(std::exception excep)
    {
        isExcep = false;
    }
    
    BOOST_CHECK( isExcep );
}


BOOST_AUTO_TEST_CASE( TestAllocate_request_moreMemoryThatIsEnbleToProvide )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, 30, 1);
        mManager.Allocate();
        mManager.Allocate();
        mManager.Allocate();
        mManager.Allocate();
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestFree_request_freeNullptr )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        mManager.Free(nullptr);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestFree_request_freeIfNoAllocationCall )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        mManager.Free(memoryPool);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestFree_request_freeOutOfRangeOfPool )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        mManager.Free((uint8_t*)memoryPool + poolSize + 1);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_CASE( TestAllocateFree_check_freeMemoryWithShift )
{
    bool isExcep = false;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        auto pointer = mManager.Allocate();
        mManager.Free((uint8_t*)pointer + 1);
    }
    catch(std::exception excep)
    {
        isExcep = true;
    }
    
    BOOST_CHECK( isExcep );
}


BOOST_AUTO_TEST_CASE( TestAllocateFree_check_normalBehavior )
{
    bool isExcep = true;
    try
    {
        TablePoolOfConstantBlocksMemoryManager mManager(memoryPool, poolSize, blockSize);
        auto pointer = mManager.Allocate();
        mManager.Free(pointer);
    }
    catch(std::exception excep)
    {
        isExcep = false;
    }
    
    BOOST_CHECK( isExcep );
}

BOOST_AUTO_TEST_SUITE_END()
