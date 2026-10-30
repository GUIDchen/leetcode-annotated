// 题目：2395. 和相等的子数组（Find Subarrays With Equal Sum）
// 思路：用哈希集合记录已经出现过的「相邻两元素之和」，一旦某个和重复出现，说明存在两段和相等的子数组。
// 时间复杂度：O(n)，每个元素只参与一次求和并插入一次集合；空间复杂度：O(n)，集合最多保存 n-1 个不同的和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool findSubarrays(vector<int>& nums) {  // nums：输入数组；返回值表示是否存在两段和相等的长度为 2 的子数组
        unordered_set<int> vis;  // 哈希集合：记录已经出现过的相邻两元素之和
        for (int i = 1; i < nums.size(); ++i) {  // 从下标 1 开始遍历，i-1 与 i 恰好构成一段长度为 2 的子数组
            int x = nums[i - 1] + nums[i];  // 计算当前这段子数组的和
            if (vis.count(x)) {  // 集合里已经有相同的和，说明前面某段子数组与当前这段和相等
                return true;  // 立即返回 true
            }
            vis.insert(x);  // 把当前和加入集合，供后面的子数组比较
        }
        return false;  // 遍历结束没有出现重复的和，返回 false
    }
};