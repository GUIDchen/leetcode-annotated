// 题目：1906. 查询差绝对值的最小值（Minimum Absolute Difference Queries）
// 思路：元素值域只有 1..100，用二维前缀和 preSum[i][j] 记录前 i 个元素中值 j 的出现次数；对每个询问按值升序扫描，出现过且相邻的两个值之差取最小。
// 时间复杂度：O((m + n)·100)，建表与每次询问都只扫 100 个值；空间复杂度：O(100m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {  // nums：原数组；queries：若干 [left, right] 闭区间询问
        int m = nums.size(), n = queries.size();  // 数组长度与询问个数
        vector<vector<int>> preSum(m + 1, vector<int>(101));  // 二维前缀计数：preSum[i][j] 表示 nums 前 i 个元素中值 j 出现的次数
        for (int i = 1; i <= m; ++i) {  // 按下标从左到右填表
            for (int j = 1; j <= 100; ++j) {  // 元素值域为 1..100
                int t = nums[i - 1] == j ? 1 : 0;  // 判断第 i 个元素（下标 i-1）是否等于值 j
                preSum[i][j] = preSum[i - 1][j] + t;  // 前缀和递推：继承前 i-1 个元素的计数，再加上当前元素
            }  // 结束值域循环
        }  // 结束建表循环

        // 前缀表建好后，逐个询问在值域上扫描求最小差值
        vector<int> ans(n);  // 预先分配好每个询问的答案
        for (int i = 0; i < n; ++i) {  // 逐个处理询问
            int left = queries[i][0], right = queries[i][1] + 1;  // 前缀和的区间写成左闭右开，所以右端点要加 1
            int t = 101;  // 最小差值初值取比最大可能差值 100 还大的数，表示「还没找到」
            int last = -1;  // 上一个在区间内出现过的值，-1 表示还没遇到
            for (int j = 1; j <= 100; ++j) {  // 从小到大枚举所有可能的值
                if (preSum[right][j] > preSum[left][j]) {  // 差值计数大于 0 说明值 j 在该区间内确实出现过
                    if (last != -1) {  // 不是区间内第一个出现过的值时才存在相邻差
                        t = min(t, j - last);  // 升序枚举时最小差值只可能出现在相邻的两个出现过的值之间
                    }  // 结束 if 分支
                    last = j;  // 记下最近一次出现的值，供下一个出现的值求差
                }  // 结束「值存在」判断
            }  // 结束值域循环
            if (t == 101) {  // 差值仍是初值，说明区间内不同值不足两个
                t = -1;  // 按题目要求返回 -1
            }  // 结束 if 分支
            ans[i] = t;  // 保存该询问的答案
        }  // 结束询问循环
        return ans;  // 返回所有询问的答案
    }  // 结束题解方法
};  // 结束题解类