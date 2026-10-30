// 题目：2229. 检查数组是否连贯（Check if an Array Is Consecutive）
// 思路：用哈希集合去重，同时记录最小值与最大值；若既无重复又满足「最大值 - 最小值 + 1 == 长度」，则数组恰好覆盖一段连续整数。
// 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(n)，哈希集合最多保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isConsecutive(vector<int>& nums) {  // nums 为待检查数组；返回它是否恰好构成一段连续整数
        unordered_set<int> s;  // 哈希集合：既做去重，又能在 O(1) 内判断元素是否已出现
        int mi = nums[0], mx = 0;  // mi 记录最小值（先用首元素打底），mx 记录最大值
        for (int x : nums) {  // 逐个遍历数组元素
            if (s.contains(x)) {  // C++20 的 contains：判断该值是否已经出现过
                return false;  // 出现重复值，必然不连贯，立即返回 false
            }
            s.insert(x);  // 第一次出现，加入集合
            mi = min(mi, x);  // 更新最小值
            mx = max(mx, x);  // 更新最大值
        }
        return mx - mi + 1 == nums.size();  // 无重复且极差恰好等于长度 - 1，说明正好覆盖 [mi, mx] 内全部整数
    }
};
