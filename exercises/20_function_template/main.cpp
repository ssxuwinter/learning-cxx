#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
//模板本身是一个 代码生成器，它在编译阶段不会直接生成二进制代码。
//只有当模板被实际使用（调用或实例化）时，编译器才会根据模板的定义和传入的类型生成具体的代码。

template <class T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    //精确 用定点数
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过 
    ASSERT(plus(0.1f, 0.2f) == 0.3f, "How to make this pass?");

    return 0;
}
