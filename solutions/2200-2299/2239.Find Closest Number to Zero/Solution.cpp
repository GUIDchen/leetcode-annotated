// 题目：2239. 找到最接近 0 的数字（Find Closest Number to Zero）
// 思路：一次遍历，用变量记录「当前最优数字」与它到 0 的距离；距离更小就替换，距离相同时取更大的数字。
// 时间复杂度：O(n)，只遍历数组一遍；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findClosestNumber(vector<int>& nums) {  // nums：给定的整数数组
        int ans = 0, d = 1 << 30;  // ans：当前最接近 0 的数字；d：它到 0 的距离，初始取足够大的 2^30
        for (int x : nums) {  // 依次枚举数组中的每个元素
            int y = abs(x);  // 当前元素到 0 的距离
            if (y < d || (y == d && x > ans)) {  // 距离更小就更新；距离相同时取更大的数字（题目要求距离相同返回较大值）
                ans = x;  // 更新答案数字
                d = y;  // 同步更新当前的最优距离
            }
        }
        return ans;  // 返回最接近 0 的数字
    }
};