// 题目：1237. 找出给定方程的正整数解（Find Positive Integer Solution for a Given Equation）
// 思路：枚举 x，利用 f 关于 y 单调递增的性质，在 [1, 1000] 上二分出使 f(x, y) >= z 的最小 y，再判断是否恰好等于 z。
// 时间复杂度：O(1000 log 1000)，每个 x 做一次二分；空间复杂度：O(1)，除答案外只用常数变量。
/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {  // customfunction 是单调递增的 f，z 是目标和，返回所有正整数解
        vector<vector<int>> ans;  // 收集所有满足 f(x, y) == z 的解
        for (int x = 1; x <= 1000; ++x) {  // 枚举 x（题目保证解不超过 1000）
            int l = 1, r = 1000;  // 对固定的 x，f(x, y) 关于 y 单调，用二分查找目标 y
            while (l < r) {  // 二分区间还没缩小到一个点
                int mid = (l + r) >> 1;  // 取中点（右移一位等于除以 2）
                if (customfunction.f(x, mid) >= z) {  // f(x, y) 随 y 递增：结果 >= z 说明答案在左半边（含 mid）
                    r = mid;  // 收缩右边界到 mid
                } else {  // 否则答案在右半边
                    l = mid + 1;  // 收缩左边界到 mid + 1
                }  // if-else 结束
            }  // 此时 l == r，是使 f(x, l) >= z 的最小 y
            if (customfunction.f(x, l) == z) {  // 恰好等于 z 才是合法解
                ans.push_back({x, l});  // 记录解 (x, l)
            }  // if 结束
        }  // for 结束
        return ans;  // 返回按 x 升序排列的全部解
    }  // 方法结束
};  // 类定义结束