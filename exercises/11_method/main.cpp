#include "../exercise.h"
//函数定义写道结构体里边
struct Fibonacci {
    unsigned long long cache[128];
    int cached;
    //与python中的self的一致
    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib={{0,1},2};
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
