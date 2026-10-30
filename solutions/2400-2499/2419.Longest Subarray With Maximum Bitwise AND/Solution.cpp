// 题目：2419. 按位与最大的最长子数组（Longest Subarray With Maximum Bitwise AND）
// 核心思路：子数组的按位与不会超过其中任一元素，故最大按位与就是数组最大值 mx；只需统计 mx 连续出现的最长一段。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubarray(vector<int>& nums) {  // nums：输入数组
        int mx = ranges::max(nums);  // 按位与只会让数值变小或不变，所以能达到的最大值就是数组最大值
        int ans = 0, cnt = 0;  // ans 记录最长长度，cnt 记录当前连续等于 mx 的个数
        for (int x : nums) {  // 顺序扫描每个元素
            if (x == mx) {  // 命中最大值，这一段可以持续参与与运算而不降低结果
                ans = max(ans, ++cnt);  // 先自增当前连续计数，再用它更新答案
            } else {  // 遇到比 mx 小的元素
                cnt = 0;  // 纳入它会让与运算结果变小，连续段必须断开
            }
        }
        return ans;  // 返回最长子数组长度
    }
};
