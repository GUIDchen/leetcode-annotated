// 题目：594. 最长和谐子序列（Longest Harmonious Subsequence）
// 思路：先用哈希表统计每个值出现的次数，再对每个值 x 检查 x+1 是否存在；两者次数之和就是一个候选答案，取最大值。
// 时间复杂度：O(n)，一次哈希统计加一次哈希遍历；空间复杂度：O(n)，哈希表最多存 n 个不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findLHS(vector<int>& nums) {  // nums 是输入数组，返回最长和谐子序列的长度
        unordered_map<int, int> cnt;  // 统计每个值出现的次数：键是元素值，值是出现次数
        for (int x : nums) {  // 遍历数组中的每个元素
            ++cnt[x];  // 当前值的计数加一
        }
        int ans = 0;  // 最长和谐子序列的长度，初始为 0
        for (auto& [x, c] : cnt) {  // 结构化绑定：x 是值，c 是该值的出现次数
            if (cnt.contains(x + 1)) {  // 只有 x 与 x+1 都存在时才可能构成和谐子序列（C++20 的 contains）
                ans = max(ans, c + cnt[x + 1]);  // 两者的次数之和就是一个候选答案，取较大者
            }
        }
        return ans;  // 没有满足条件的组合时返回 0
    }
};