// 题目：1954. 收集足够苹果的最小花园周长（Minimum Garden Perimeter to Collect Enough Apples）
// 思路：方形花园中坐标为 (i, j) 的树贡献 |i| + |j| 个苹果，按行列求和可得半边长 x 时总数恰为 2x(x+1)(2x+1)；因此从小到大枚举 x，首个满足需求的 x 给出最小周长 8x。
// 时间复杂度：O(x)，x 为答案对应的半边长（最坏约 4×10^4 次枚举）；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumPerimeter(long long neededApples) {  // neededApples：至少需要收集的苹果数；返回所需的最小周长
        long long x = 1;  // x 是花园的「半边长」，从 1 开始枚举，最终周长就是 8x
        while (2 * x * (x + 1) * (2 * x + 1) < neededApples) {  // 半边长 x 的方形花园共有 2x(x+1)(2x+1) 个苹果，不够就继续扩大
            ++x;  // 半边长加一；苹果数随 x 单调递增，所以第一次满足即为最小可行解
        }
        return 8 * x;  // 边长 2x 的正方形，周长为 8x
    }
};