#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        ASSERT(sizeof(vec) == sizeof(std::vector<int>), "Fill in the correct value."); 
        // 注释：sizeof(vec) 返回的是 std::vector 对象本身的大小，而不是它所包含的元素的大小。
        // std::vector 对象通常包含指向堆上分配的内存的指针，以及一些用于管理容量和大小的成员。
        // 因此，sizeof(vec) 的值与 std::vector<int> 类型的大小相同。
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
            // 注释：同上，sizeof(vec) 返回的是 std::vector 对象本身的大小，而不是它所包含的元素的大小。
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {   //push_back是向 vector 的末尾添加一个元素。
            //size当前容量
            //capacity当前分配的内存大小，在不重新分配内存情况下
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
            // 注释：push_back() 操作会改变 vector 的大小，但不会改变 vector 对象本身的大小。
            //pop_back() 是从 vector 的末尾删除一个元素。
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
            // 注释：pop_back() 操作会改变 vector 的大小，但不会改变 vector 对象本身的大小。
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            // 插入和删除操作的时间复杂度通常是 O(n)，因为在插入或删除元素时，可能需要移动其他元素以保持顺序。\
            //vec.insert是在 vector 的指定位置插入一个元素。
            vec.insert(vec.begin() + 1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            //vec.erase是从 vector 中删除指定位置的元素。
            vec.erase(vec.begin() + 3);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
        }
    }
    {
        std::vector<char> vec(48, 'z'); // TODO: 调用正确的构造函数
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == sizeof(std::vector<char>), "Fill in the correct value.");
        // 注释：同上，sizeof(vec) 返回的是 std::vector 对象本身的大小，而不是它所包含的元素的大小。
        {
            auto capacity = vec.capacity();
            vec.resize(16);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 48, "Fill in a correct identifier.");
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}