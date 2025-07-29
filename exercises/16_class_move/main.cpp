#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器 构造函数
    DynFibonacci(int capacity): cache(new size_t[capacity]{0,1}), cached(2) {}

    // TODO: 实现移动构造器  
    /*
    DynFibonacci(DynFibonacci &&others)noexcept :
        cache(others.cache), cached(others.cached) {
        //避免二次删除
        others.cache = nullptr;
        others.cached = 0; // 将源对象的资源转移到当前对象
    }
        */
    //或者  
    DynFibonacci(DynFibonacci &&others)noexcept :
        cache(std::exchange(others.cache, nullptr)),
        cached(std::exchange(others.cached, 0)) {
        std::cout << "copy constructor called" << std::endl;
    }
    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    //运算符重载 operator= 其中=是重载的符号
    //右赋值赋值到左边
    DynFibonacci &operator=(DynFibonacci &&others) noexcept {
        //1.判断是否移动到自己 判断当前地址与others的地址是否一样
        if(this != &others) { // 避免自我赋值
            std::cout << "move assigment called" << std::endl;
            //2.释放自己的资源 原地析构 
            delete[] cache; // 释放当前对象的资源
            //3.做移动赋值的操作
            cache = std::exchange(others.cache, nullptr);
            cached = std::exchange(others.cached, 0); // 转移资源
        }
        else{
            std::cerr << "self move assignment" << std::endl;
        }
        //返回被赋值的坐值引用
        return *this; // 返回当前对象的引用
    };

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache; // 释放缓存空间
    };

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
