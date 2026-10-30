// 题目：2778. 特殊元素平方和（Sum of Squares of Special Elements）
// 思路：题目要求下标 i（1 起）能整除 n 的元素 nums[i - 1] 才是特殊元素，直接枚举下标 1..n 判断整除并累加其平方即可。
// 时间复杂度：O(n)，枚举 n 个下标；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int sumOfSquares(vector<int>& nums) {  // nums 是输入数组
        int n = nums.size();  // 数组长度，同时是判断整除的模数
        int ans = 0;  // 特殊元素平方和的累加器
        for (int i = 1; i <= n; ++i) {  // 按 1 起算的下标枚举每个位置
            if (n % i == 0) {  // 下标 i 能整除 n，说明该位置是特殊元素
                ans += nums[i - 1] * nums[i - 1];  // 把对应元素（下标要减一）的平方累加进答案
            }
        }
        return ans;  // 返回所有特殊元素的平方和
    }
};