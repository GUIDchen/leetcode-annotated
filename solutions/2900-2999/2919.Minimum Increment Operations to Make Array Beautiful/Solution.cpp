// 题目：2919. 使数组变美的最小增量运算数（Minimum Increment Operations to Make Array Beautiful）
// 思路：动态规划，f/g/h 表示最近被抬高的元素是 i-2 / i-1 / i 时的最小代价，新状态 = 三者最小值 + 把当前元素抬到 k 的代价。
// 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用了三个滚动变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minIncrementOperations(vector<int>& nums, int k) {  // nums：目标数组；k：任意连续三个元素之和至少要达到 k
        long long f = 0, g = 0, h = 0;  // 滚动 DP：f/g/h 分别表示最近被抬高的元素是 i-2 / i-1 / i 时的最小代价
        for (int x : nums) {  // 从左到右处理每个元素
            long long hh = min({f, g, h}) + max(k - x, 0);  // 让当前元素达标：三种前态取最小值，加上把 x 抬到 k 所需的增量
            f = g;  // 整体右移：原来的 g 变成新的 f
            g = h;  // 原来的 h 变成新的 g
            h = hh;  // 新算出的状态放到 h
        }  // 遍历结束
        return min({f, g, h});  // 任意结尾状态都合法，取三者最小值
    }  // minIncrementOperations 结束
};  // 类定义结束