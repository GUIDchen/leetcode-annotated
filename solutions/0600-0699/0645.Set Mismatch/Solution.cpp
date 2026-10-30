// 题目：645. 错误的集合（Set Mismatch）
// 核心思路：重复值 = 原数组总和 - 去重集合之和；缺失值 = 1..n 的理论总和 - 去重集合之和。
// 时间复杂度：O(n)，遍历数组与集合各一次；空间复杂度：O(n)，哈希集合存放去重后的元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findErrorNums(vector<int>& nums) {  // 返回 [重复的数字, 缺失的数字]
        int n = nums.size();  // 数组长度，也等于 1..n 的取值范围
        int s1 = (1 + n) * n / 2;  // 1..n 的理论总和
        int s2 = 0;  // 去重后各元素之和
        unordered_set<int> set(nums.begin(), nums.end());  // 用哈希集合去掉重复元素
        for (int x : set) {  // 遍历去重后的元素
            s2 += x;  // 累加得到每个数只出现一次时的和
        }  // 去重和统计完成
        int s = accumulate(nums.begin(), nums.end(), 0);  // 原数组的总和
        return {s - s2, s1 - s2};  // 原和比去重和多出的部分就是重复值，理论和中少掉的部分就是缺失值
    }  // 方法结束
};  // 类结束