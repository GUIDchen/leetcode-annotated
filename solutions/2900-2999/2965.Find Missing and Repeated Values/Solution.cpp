// 题目：2965. 找出缺失和重复的数字（Find Missing and Repeated Values）
// 思路：用计数数组统计 1..n*n 每个数字出现的次数，次数为 2 的是重复的数，次数为 0 的是缺失的数。
// 时间复杂度：O(n^2)，遍历矩阵与计数数组各一遍；空间复杂度：O(n^2)，计数数组长度为 n*n+1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {  // grid：n×n 的矩阵；返回 {重复的数, 缺失的数}
        int n = grid.size();  // n 是矩阵边长，矩阵里的数字取值范围是 1..n*n
        vector<int> cnt(n * n + 1);  // 计数数组，cnt[v] 表示数字 v 出现的次数（下标 0 不用）
        vector<int> ans(2);  // 答案数组：ans[0] 存重复的数，ans[1] 存缺失的数，初始都为 0
        for (auto& row : grid) {  // 按行遍历矩阵
            for (int x : row) {  // 遍历这一行里的每个数字
                if (++cnt[x] == 2) {  // 先自增计数再判断：等于 2 说明这是第二次出现，即重复的数
                    ans[0] = x;  // 记下重复的数
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        for (int x = 1;; ++x) {  // 从 1 开始找第一个没出现过的数，找到就立即返回
            if (cnt[x] == 0) {  // 计数为 0 说明这个数字缺失
                ans[1] = x;  // 记下缺失的数
                return ans;  // 两个答案都齐了，直接返回
            }  // if 结束
        }  // for 结束（循环上界省略，靠 return 退出）
    }  // 方法结束
};  // 类定义结束