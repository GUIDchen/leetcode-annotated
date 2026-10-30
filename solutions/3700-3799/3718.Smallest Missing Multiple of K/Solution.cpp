// 题目：3718. 缺失的最小倍数（Smallest Missing Multiple of K）
// 思路：先把数组元素全部放进哈希集合，再从 k 的 1 倍开始逐个检查，第一个不在集合中的倍数就是答案。
// 时间复杂度：O(n + m)，m 为答案的倍数序号（不超过 n + 1）；空间复杂度：O(n)，用于存放集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int missingMultiple(vector<int>& nums, int k) {  // nums：整数数组；k：倍数基数；返回最小的不在数组中的 k 的正倍数
        unordered_set<int> s;  // 用哈希集合记录数组里出现过的值
        for (int x : nums) {  // 遍历数组
            s.insert(x);  // 记录当前元素
        }  // 建表结束
        for (int i = 1;; ++i) {  // 从 k 的 1 倍开始逐个检查
            int x = k * i;  // 第 i 个 k 的正倍数
            if (!s.contains(x)) {  // 该倍数不在数组中，即为答案
                return x;  // 立刻返回最小缺失倍数
            }  // 缺失判断结束
        }  // 循环一定会在此之前返回
    }  // 方法结束
};  // 类定义结束
