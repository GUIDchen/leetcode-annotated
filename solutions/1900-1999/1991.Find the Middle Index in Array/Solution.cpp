// 题目：1991. 找到数组的中间位置（Find the Middle Index in Array）
// 思路：前缀和。先把总和放进右和 r，遍历时先从 r 中扣掉 nums[i]，此时 l 与 r 恰好是左右两侧元素和，相等即答案，否则把 nums[i] 并入 l。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用了两个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMiddleIndex(vector<int>& nums) {  // nums：输入数组
        int l = 0, r = accumulate(nums.begin(), nums.end(), 0);  // l 是 i 左侧元素和（初值 0）；r 初始化为整数组之和，相当于 i 右侧元素和
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右枚举每个可能的下标 i
            r -= nums[i];  // 先从右和中扣掉 nums[i]，此时 r 恰好是 [i+1, n) 的元素和
            if (l == r) {  // 左右两侧之和相等，i 就是要求的中间位置
                return i;  // 立即返回该下标
            }  // 左侧多累加一个 nums[i]，交给下一轮比较
            l += nums[i];  // 循环结束仍未找到
        }  // 不存在满足条件的下标，返回 -1
        return -1;  // 方法结束
    }  // 题解类结束
};
