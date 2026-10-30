// 题目：1413. 逐步求和得到正数的最小值（Minimum Value to Get Positive Step by Step Sum）
// 思路：先求所有前缀和的最小值 t，起始值只要让 t 加上它不小于 1 即可，即 max(1, 1-t)。
// 时间复杂度：O(n)，一次遍历求最小前缀和；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minStartValue(vector<int>& nums) {  // nums 是待逐步累加的数组，返回使每步前缀和都为正的最小起始值
        int s = 0, t = INT_MAX;  // s 是当前前缀和，t 记录整趟过程中的最小前缀和
        for (int num : nums) {  // 依次把每个元素累加进前缀和
            s += num;  // 累加得到当前位置的前缀和
            t = min(t, s);  // 更新一路上的最小前缀和
        }  // 结束遍历
        return max(1, 1 - t);  // 起始值加上最小前缀和至少为 1，故需 1-t；同时起始值本身至少是 1
    }  // 结束题解方法
};  // 结束题解类