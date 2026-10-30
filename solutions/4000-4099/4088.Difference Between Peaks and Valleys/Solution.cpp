// 题目：4088. 峰值与谷值的差（Difference Between Peaks and Valleys）
// 核心思路：逐个检查非端点的中间元素，若它比左右邻居都大就是峰值（累加其值），若比左右邻居都小就是谷值（减去其值），端点不参与判断。
// 复杂度：时间 O(n)，一次线性扫描；空间 O(1)，只用累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    int peakValleyDifference(vector<int>& nums) {  // nums：目标数组；返回所有峰值之和减去所有谷值之和
        int ans = 0;  // ans 累计「峰值之和 - 谷值之和」
        for (int i = 1; i < nums.size() - 1; i++) {  // 只检查非端点的中间元素
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {  // 比左右邻居都大，说明是峰值
                ans += nums[i];  // 峰值计入答案（加）
            } else if (nums[i - 1] > nums[i] && nums[i] < nums[i + 1]) {  // 比左右邻居都小，说明是谷值
                ans -= nums[i];  // 谷值从答案中扣除（减）
            }  // 峰谷判断结束
        }  // 中间元素遍历结束
        return ans;  // 返回峰值之和与谷值之和的差
    }  // peakValleyDifference 结束
};  // Solution 类结束