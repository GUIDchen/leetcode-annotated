// 题目：960. 删列造序 III（Delete Columns to Make Sorted III）
// 思路：把「保留下来的列」看成下标递增的序列，相邻两列必须在所有行上都非递减，于是转化为最长上升子序列 DP，答案是总列数减去最长长度。
// 时间复杂度：O(m²·n)，m 为列数、n 为字符串个数；空间复杂度：O(m)，DP 数组长度为 m。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDeletionSize(vector<string>& strs) {  // strs：等长字符串数组，返回最少要删除的列数
        int n = strs[0].size();  // n：列数，也就是每个字符串的长度
        vector<int> f(n, 1);  // f[i]：以第 i 列结尾、能保留下来的最长合法列序列长度，只含自己时为 1
        for (int i = 1; i < n; ++i) {  // 枚举作为结尾的列 i
            for (int j = 0; j < i; ++j) {  // 枚举前一列 j（只能从更靠左的列接过来）
                if (ranges::all_of(strs, [&](const string& s) { return s[j] <= s[i]; })) {  // 检查所有行：第 j 列 <= 第 i 列才允许这两列相邻保留
                    f[i] = max(f[i], f[j] + 1);  // 状态转移：接到以 j 结尾的最优序列后面
                }
            }
        }
        return n - ranges::max(f);  // 总列数减去能保留的最多列数，就是最少删除列数
    }
};
