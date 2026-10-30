// 题目：1714. 数组中特殊等间距元素的和（Sum Of Special Evenly-Spaced Elements In Array）
// 思路：根号分治。预处理步长 1..sqrt(n) 的后缀和表 suf[i][j]；查询时小步长 O(1) 查表，大步长直接按步长跳着累加。
// 时间复杂度：O(n·sqrt(n) + q·sqrt(n))，其中 q 为查询个数；空间复杂度：O(n·sqrt(n))。
class Solution {
public:
    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {  // nums：原始数组；queries：每个查询为 [x, y]，求 nums[x] + nums[x+y] + ... 的和
        int n = nums.size();  // 数组长度
        int m = (int) sqrt(n);  // 分块阈值：约等于 sqrt(n)，决定预处理哪些步长
        const int mod = 1e9 + 7;  // 取模常数（题目要求对 1e9+7 取模）
        int suf[m + 1][n + 1];  // suf[i][j]：从 j 开始、步长为 i 的所有元素之和（已取模）
        memset(suf, 0, sizeof(suf));  // 全部清零，越界位置视作空和 0
        for (int i = 1; i <= m; ++i) {  // 只预处理步长 1..m
            for (int j = n - 1; ~j; --j) {  // 从后往前递推，~j 等价于 j >= 0
                suf[i][j] = (suf[i][min(n, j + i)] + nums[j]) % mod;  // 当前位置的值 + 后一个同余位置；min(n, j+i) 处理越界
            }
        }
        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 逐个处理查询
            int x = q[0], y = q[1];  // x：起点下标；y：步长
            if (y <= m) {  // 步长较小，直接用预处理结果 O(1) 回答
                ans.push_back(suf[y][x]);  // 查表得到后缀和
            } else {  // 步长较大，直接按步长跳着累加
                int s = 0;  // 累加和
                for (int i = x; i < n; i += y) {  // 每次前进 y 步，最多跳 n/y ≤ sqrt(n) 次
                    s = (s + nums[i]) % mod;  // 累加并取模，防止溢出
                }
                ans.push_back(s);  // 记录本次查询的答案
            }
        }
        return ans;  // 返回所有查询的答案
    }
};