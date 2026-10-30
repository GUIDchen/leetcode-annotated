// 3708. Longest Fibonacci Subarray（3708. 最长斐波那契子数组）
// 核心思路：从左到右扫描，若 nums[i] 恰好等于前两项之和就把当前子数组长度加一，否则把长度重置为 2，全程维护最大长度。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int longestSubarray(vector<int>& nums) {  // 返回最长的类斐波那契子数组长度
        int f = 2;  // 当前子数组长度，任意两个数都构成长度 2 的合法子数组
        int ans = f;  // 答案至少为 2
        for (int i = 2; i < nums.size(); ++i) {  // 从第三个元素开始检查是否满足相邻两项之和的关系
            if (nums[i] == nums[i - 1] + nums[i - 2]) {  // 满足关系，当前子数组可以再延长一位
                ++f;  // 当前长度加一
                ans = max(ans, f);  // 更新最长长度
            } else {  // 不满足关系，子数组在此断开
                f = 2;  // 以 i-1、i 两个元素重新起算，长度回到 2
            }  // 结束分支
        }  // 结束遍历
        return ans;  // 返回最长长度
    }  // 方法结束
};  // 类定义结束
