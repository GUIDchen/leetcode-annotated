// 题目：3919. 在下标间移动的最小代价（Minimum Cost to Move Between Indices）
// 思路：相邻下标之间要么照价付差值、要么借助 closest 只花 1，因此按「向右」「向左」两个方向各做一遍前缀和，查询时按 l < r 取对应的前缀差。
// 时间复杂度：O(n + m)，n 为数组长度、m 为查询数；空间复杂度：O(n)，两个前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {  // nums：严格递增数组；queries：每项是 [l, r]，返回每个查询的最小代价
        int n = nums.size();  // 数组长度
        vector<int> s1(n, 0);  // s1[i]：从下标 0 向右走到 i 的最小累计代价
        vector<int> s2(n, 0);  // s2[i]：从下标 0 沿向左方向走到 i 的最小累计代价
        for (int i = 1; i < n; i++) {  // 预处理每条相邻边（即 i-1 与 i 之间）的代价
            int c1 = (i > 1 && nums[i - 1] - nums[i - 2] <= nums[i] - nums[i - 1]) ? nums[i] - nums[i - 1] : 1;  // 向右跨 (i-1)→i 的代价：closest(i-1) 不指向 i 时只能照价付差值，否则花 1
            int c2 = (i < n - 1 && nums[i] - nums[i - 1] > nums[i + 1] - nums[i]) ? nums[i] - nums[i - 1] : 1;  // 向左跨 i→(i-1) 的代价：closest(i) 指向 i+1 时只能照价付差值，否则花 1
            s1[i] = s1[i - 1] + c1;  // 累加得到向右方向的前缀代价
            s2[i] = s2[i - 1] + c2;  // 累加得到向左方向的前缀代价
        }  // 相邻边预处理结束
        int m = queries.size();  // 查询个数
        vector<int> ans(m);  // 存放每个查询的答案
        for (int i = 0; i < m; i++) {  // 逐个处理查询
            int l = queries[i][0];  // 起点下标
            int r = queries[i][1];  // 终点下标
            ans[i] = (l < r) ? s1[r] - s1[l] : s2[l] - s2[r];  // l < r 时用向右的 s1 差分，否则用向左的 s2 差分
        }  // 查询处理结束
        return ans;  // 返回全部答案
    }  // 方法结束
};  // 类定义结束
