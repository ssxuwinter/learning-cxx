#include "../exercise.h"
#include <format>
// READ: 运算符 <https://zh.cppreference.com/w/cpp/language/expressions#.E8.BF.90.E7.AE.97.E7.AC.A6>
//打印流输出需要加括号
int main(int argc, char **argv) {
    // TODO: 补全变量定义并打印加法运算
    // x ?
    int x;
    x = 42; // 假设 x 的值为 42
    std::cout << x << " + " << x << " = " << x + x << std::endl;
    //打印流输出需要加括号<<例如我希望移位
    std::cout <<  (1 << 2) << std::endl; // 打印 1 左移 2 位的结果
    // std::cout << std::format("Formatted output: {}", x + x) << std::endl;

    return 0;
}
