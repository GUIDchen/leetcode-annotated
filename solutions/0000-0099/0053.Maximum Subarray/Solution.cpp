// 题目：53. 最大子数组和（Maximum Subarray）
// 思路：动态规划 / 贪心。f 表示以当前元素结尾的最大子数组和，若 f 为负就丢弃前面、只留当前元素，边递推边更新全局最大值。
// 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用两个变量滚动更新。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubArray(vector<int>& nums) {  // nums 为输入数组，返回其连续子数组的最大和
        int ans = nums[0], f = nums[0];  // ans 记录全局最大值；f 记录以当前元素结尾的最大和，都先用首元素初始化
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始递推（首元素已经在初值里考虑过）
            f = max(f, 0) + nums[i];  // f 为负说明前面的部分只会拖累，干脆从当前元素重新开始累加
            ans = max(ans, f);  // 用当前结尾的最优值更新全局最优解
        }  // for 结束
        return ans;  // 返回最大子数组和
    }  // maxSubArray 结束
};  // 类定义结束