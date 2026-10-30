// 题目：1. 两数之和（Two Sum）
// 思路：哈希表保存「值 → 下标」，遍历时检查补数 target - x 是否已经出现。
// 时间复杂度：O(n)，每个元素只查一次表；空间复杂度：O(n)，哈希表最多存 n 个键值对。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> twoSum(vector<int>& nums, int target) {  // nums：输入数组；target：目标和
        unordered_map<int, int> d;  // 哈希表：键是元素值，值是下标
        for (int i = 0;; ++i) {  // 题目保证有解，所以循环上界可以省略
            int x = nums[i];  // 当前元素
            int y = target - x;  // 还需要的另一个数
            if (d.contains(y)) {  // C++20 的 contains：判断补数是否已在表中
                return {d[y], i};  // 返回补数下标与当前下标
            }
            d[x] = i;  // 补数未出现，把当前值与下标存入哈希表
        }
    }
};
