#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    //shared_ptr创建对象时，shared 的引用计数从 0→1。
    auto shared = std::make_shared<int>(10);
    //将 shared 拷贝给 ptrs[0]、ptrs[1]、ptrs[2]，每一次拷贝都会使引用计数 +1。
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    //observer 只是观察者，不会改变计数。
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "1");
    //ptrs[0] 原来持有一个引用，reset() 会销毁它对资源的拥有权，使计数 −1。
    ptrs[0].reset();
    //其他三个 (shared, ptrs[1], ptrs[2]) 仍然指向同一对象。
    ASSERT(observer.use_count() == 3, "2");

    //给 ptrs[1] 赋 nullptr 也会销毁它对原对象的拥有权，计数 −1。
    ptrs[1] = nullptr;
    //剩下 shared 和 ptrs[2] 两个所有者。
    ASSERT(observer.use_count() == 2, "3");
    //右侧 make_shared 先创建一个全新的对象，其引用计数为 1（仅被新的 std::shared_ptr 持有）。
    // 原来 ptrs[2] 指向旧对象，会先将旧对象的引用计数 −1；
    // 然后 ptrs[2] 持有新对象，但这个新对象与 observer 无关。
    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "4");
    //旧的 ptrs[0] 原先为 nullptr，此处变为指向原始对象，计数 +1 → 2。
    ptrs[0] = shared;
    ptrs[1] = shared;
    //std::move(shared) 把 shared 的所有权“搬”给 ptrs[2]：
    //先析构 ptrs[2]（它原本指向新对象），新对象引用 −1 → 0（销毁那块内存）；
    //再把 shared（原始对象）交给 ptrs[2]，此时对原始对象的引用 不 发生额外加一（是转移），shared 变为空。
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "5");
    
    //ptrs[0] 保持不变，计数无影响。
    std::ignore = std::move(ptrs[0]);
    //“自我移动”在标准库里通常被当成“无效操作”，也不会减少或增加引用。
    ptrs[1] = std::move(ptrs[1]);
    //先析构原来 ptrs[1] 对原始对象的引用 → 计数 −1；
    //然后把 ptrs[2] 的指针移动到 ptrs[1]，ptrs[2] 置空，原始对象计数不再额外 +1（是直接转移）。
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "6");

    //observer.lock() 在对象还存活（引用计数 >0）时，会创建一个新的 shared_ptr，使引用计数 +1。
    //此时有三个所有者：ptrs[0]、ptrs[1]、新得到的 shared。
    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "7");

    //先把从 lock() 得到的 shared 清空 → 3 → 2（剩下两个 ptrs）。
    shared = nullptr;
    //全变为空指针
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "8");

    //很明显此时对象全部没有存货了
    //对象已析构，控制块过期，lock() 返回空 shared_ptr，引用计数保持 0。
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "9");

    return 0;
}
