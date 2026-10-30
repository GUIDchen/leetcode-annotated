// 题目：338. 比特位计数（Counting Bits）
// 核心思路：直接调用编译器内置的 popcount 指令，逐个数字统计二进制中 1 的个数并填入结果数组。
// 时间复杂度：O(n)，每个数只需一次内置位运算；空间复杂度：O(n)，答案数组保存 n+1 个结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countBits(int n) {  // n 为范围上界，返回下标 0..n 每个整数二进制中 1 的个数
        vector<int> ans(n + 1);  // 结果数组，ans[i] 表示 i 的二进制 1 的个数；vector 默认把元素初始化为 0
        for (int i = 0; i <= n; ++i) {  // 遍历 0 到 n 的每个整数
            ans[i] = __builtin_popcount(i);  // __builtin_popcount 是 GCC/Clang 内置函数，直接统计 int 中 1 的位数
        }  // for 循环结束
        return ans;  // 返回构造好的答案数组
    }  // 方法结束
};  // 类定义结束