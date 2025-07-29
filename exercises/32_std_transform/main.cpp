#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    // std::vector<std::string> ans
    //创建一个有 val.size() 个元素的 std::vector<std::string> 容器 ans，并把每个元素初始化为默认值（即空字符串 ""）。
    std::vector<std::string> ans(val.size());
    //val.begin() 和 val.end()：指定输入范围；
    //ans.begin()：指定输出范围（必须提前分配好大小）；
    std::transform(val.begin(), val.end(), ans.begin(), [](int x) {
        return std::to_string(x * 2);
    });
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
