// 题目：3701. 计算交替和（Compute Alternating Sum）
// 核心思路：一次遍历，偶数下标取正、奇数下标取负，边遍历边累加得到交替和。
// 复杂度：时间 O(n)，只扫一遍数组；空间 O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int alternatingSum(vector<int>& nums) {  // 返回数组的交替和：nums[0] - nums[1] + nums[2] - ...
        int ans = 0;  // ans 累积交替和，初值为 0
        for (int i = 0; i < nums.size(); ++i) {  // 按下标 i 从头到尾遍历
            ans += (i % 2 == 0 ? nums[i] : -nums[i]);  // 偶数下标取正、奇数下标取负后累加
        }  // 结束遍历
        return ans;  // 返回交替和
    }  // 结束 alternatingSum
};  // 结束题解类
