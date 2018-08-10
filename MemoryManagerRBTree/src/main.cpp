#include <memorymanagerrbtree_facilities.h>

#include <map>
#include <functional>

function <void*(size_t)>mapAllocateExternal;
function <void(void* ptr)>mapFreeExternal;


template <class T>
struct MapAllocator 
{
    typedef T value_type;
    MapAllocator() = default;
    template <class U> constexpr MapAllocator(const MapAllocator<U>&) noexcept {}
    [[nodiscard]] T* allocate(std::size_t n) {
        if(n > std::size_t(-1) / sizeof(T))
        {
            throw std::bad_alloc();
        }
        if(auto p = static_cast<T*>(mapAllocateExternal(n*sizeof(T))))
        {
            return p;
        }
        throw std::bad_alloc();
    }
    void deallocate(T* p, std::size_t) noexcept { mapFreeExternal(p); }
};

template <class T, class U>
bool operator==(const MapAllocator<T>&, const MapAllocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const MapAllocator<T>&, const MapAllocator<U>&) { return false; }

class MemoryManagerRBTree
{
    void* memory = nullptr;
    const uint64_t memSize = 0;
    uint64_t mapMemCursor = 0;
    size_t   memAllocationSize = 0;

    void* mapAllocate(size_t allocationSize)
    {
        cout<<"memory allocation request:"<<allocationSize<<endl;
        if( 0 == mapNodeSize )
        {
            mapNodeSize = allocationSize;
            memAllocationSize = allocationSize - (sizeof(memNodeKey) + sizeof(memNode));
        }
        void* ptrNewMem = ((uint8_t*)memory) + mapMemCursor;
         cout<<"get  memory request:"<<(uint64_t)ptrNewMem - (uint64_t)memory<<endl;
        return ptrNewMem;
    }

    void mapFree(void* inMemory)
    {
        cout<<"memory free request:"<<(uint64_t)inMemory - (uint64_t)memory<<endl;
    }

    struct memNodeKey
    {
        uint64_t blockSize = 0;
        bool isFree = true;
        bool operator < (const memNodeKey& inNode) const
        {
            if((!this->isFree) && (inNode.isFree) )
            {
                return true;
            }

            if((this->isFree) && (!inNode.isFree) )
            {
                return false;
            }

            return this->blockSize < inNode.blockSize;
        }
    };

    struct memNode
    {
        memNode(const memNode* inNode)
        {
            currentBlockPosition = inNode->currentBlockPosition;
            nextBlockPosition = inNode->nextBlockPosition;
            previosBlockPosition = inNode->previosBlockPosition;
        }
        memNode(uint64_t inPreviosBlockPosition, uint64_t inCurrentBlockPosition, uint64_t inNextBlockPosition) :
        previosBlockPosition(inPreviosBlockPosition), currentBlockPosition(inCurrentBlockPosition), nextBlockPosition(inNextBlockPosition)
        {}
        uint64_t previosBlockPosition = 0;
        uint64_t currentBlockPosition = 0;
        uint64_t nextBlockPosition = 0;
        multimap<memNodeKey,memNode>::iterator current;
    };

    size_t mapNodeSize = 0;

    multimap< memNodeKey, memNode, std::less<memNodeKey>, MapAllocator<std::pair<memNodeKey, memNode> > > memoryMultimap;
public:

    MemoryManagerRBTree(void* inMemory, uint64_t inMemSize) : memory(inMemory), memSize(inMemSize)
    {
        mapAllocateExternal = std::bind(&MemoryManagerRBTree::mapAllocate, this, std::placeholders::_1);
        mapFreeExternal = std::bind(&MemoryManagerRBTree::mapFree, this, std::placeholders::_1);
        memNode firstNode({0, 0, memSize});
        memNodeKey firstKey({memSize, true});
        memoryMultimap.insert(std::make_pair(firstKey, firstNode));
    };
    ~MemoryManagerRBTree(){};


    void* allocate(uint64_t inSize)
    {
        uint64_t memPositionToAllocate = 0;
        uint64_t nextBlockPosition = 0;
        memNodeKey key({inSize, true});
        auto it = memoryMultimap.upper_bound(key);
        if(memoryMultimap.end() != it)
        {
            memPositionToAllocate = it->second.currentBlockPosition + mapNodeSize;
            nextBlockPosition = memPositionToAllocate + inSize;
            auto restMemory = it->first.blockSize - inSize;
            memNodeKey replaceKey({inSize, false});
            memNode    replaceNode(it->second.previosBlockPosition, it->second.currentBlockPosition, nextBlockPosition);
            memNodeKey newKey({restMemory, true});
            memNode    newNode(it->second.currentBlockPosition, nextBlockPosition, restMemory);

            mapMemCursor = it->second.currentBlockPosition;
            memoryMultimap.erase(it);

            auto replaceIterator = memoryMultimap.insert(make_pair(replaceKey, replaceNode));
            replaceIterator->second.current = replaceIterator;

            mapMemCursor = newNode.currentBlockPosition;
            auto newIterator = memoryMultimap.insert(make_pair(newKey, newNode));
            newIterator->second.current = newIterator;
        }
        return ((uint8_t*)(memory)) + memPositionToAllocate;
    }

    void free(void* inMemory)
    {
        void* currentNode = (((uint8_t*)inMemory) - mapNodeSize + memAllocationSize + sizeof(memNodeKey));
        memNode* node = static_cast<memNode*>(currentNode);
        auto nodeIterator = node->current;
        memNode newNode = node;
        auto newKey = nodeIterator->first;
        newKey.isFree = true;
        memoryMultimap.erase(nodeIterator);
        if(memSize > newNode.nextBlockPosition)
        {
            void* nextNodeMemory = (((uint8_t*)memory) + newNode.nextBlockPosition + memAllocationSize + sizeof(memNodeKey));
            memNode* nextNode = static_cast<memNode*>(nextNodeMemory);
            auto nextNodeIterator = nextNode->current;
            if(nextNodeIterator->first.isFree)
            {
                newKey.blockSize += nextNodeIterator->first.blockSize;
                newNode.nextBlockPosition = nextNode->nextBlockPosition;
                memoryMultimap.erase(nextNodeIterator);
            }
        }
        if(0 != newNode.previosBlockPosition)
        {
            void* prevNodeMemory = (((uint8_t*)memory) + newNode.previosBlockPosition + memAllocationSize + sizeof(memNodeKey));
            memNode* prevNode = static_cast<memNode*>(prevNodeMemory);
            auto prevNodeIterator = prevNode->current;
            if(prevNodeIterator->first.isFree)
            {
                newKey.blockSize += prevNodeIterator->first.blockSize;
                newNode.previosBlockPosition = prevNode->previosBlockPosition;
                newNode.currentBlockPosition = prevNode->currentBlockPosition;
                memoryMultimap.erase(prevNodeIterator);
            }
        }
        mapMemCursor = newNode.currentBlockPosition;
        auto newIterator = memoryMultimap.insert(make_pair(newKey, newNode));
        newIterator->second.current = newIterator;
    }
private:

};

int main ( int argc, char** argv ) 
{
    const uint64_t memorySize = (1024 * 1024) * 2;
    uint8_t memoryPool[memorySize] = {0};
    MemoryManagerRBTree rbTree(memoryPool, memorySize);

    cout <<  "allocation!" << endl;
    uint64_t* ptr0 = new(rbTree.allocate(sizeof(uint64_t) * 54)) uint64_t[54]; 
    uint64_t* ptr1 = new(rbTree.allocate(sizeof(uint64_t) * 101)) uint64_t[101];
    uint64_t* ptr2 = new(rbTree.allocate(sizeof(uint64_t) * 160)) uint64_t[160];
    uint64_t* ptr3 = new(rbTree.allocate(sizeof(uint64_t) * 700)) uint64_t[700];
    uint64_t* ptr4 = new(rbTree.allocate(sizeof(uint64_t) * 80)) uint64_t[80];
    uint64_t* ptr5 = new(rbTree.allocate(sizeof(uint64_t) * 10)) uint64_t[10];
    uint64_t* ptr6 = new(rbTree.allocate(sizeof(uint64_t) * 270)) uint64_t[270];
    

    cout <<  "freeing!" << endl;
    rbTree.free(ptr6);
    rbTree.free(ptr2);
    rbTree.free(ptr0);
    rbTree.free(ptr1);
    rbTree.free(ptr5);
    rbTree.free(ptr4);
    rbTree.free(ptr3);

    return ( 0 );
}
