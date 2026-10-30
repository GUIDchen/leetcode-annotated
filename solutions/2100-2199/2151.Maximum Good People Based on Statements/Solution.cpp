// 题目：2151. 基于陈述统计最多好人数（Maximum Good People Based on Statements）
// 思路：用二进制掩码枚举「谁是好人」的所有非空子集，只校验好人说出的话，与假设矛盾就排除，取人数最大值。
// 时间复杂度：O(2^n · n^2)，枚举 2^n 个子集、每个子集检查 n^2 条陈述；空间复杂度：O(n)，除递归外的常数级辅助空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumGood(vector<vector<int>>& statements) {  // statements[i][j]：i 对 j 的陈述（0 表坏、1 表好、2 表未陈述）；返回最多好人数
        int ans = 0;  // 记录目前为止枚举到的最大好人数
        for (int mask = 1; mask < 1 << statements.size(); ++mask) ans = max(ans, check(mask, statements));  // 用二进制掩码枚举所有非空的好人集合，逐个校验并更新最优解
        return ans;  // 返回最大好人数
    }  // 结束方法

    int check(int mask, vector<vector<int>>& statements) {  // 校验某个「好人集合」假设是否自洽，返回好人数，矛盾则返回 0
        int cnt = 0;  // 当前假设下的好人数
        int n = statements.size();  // 总人数 n
        for (int i = 0; i < n; ++i) {  // 遍历每个人，只让假设中的好人的陈述参与校验
            if ((mask >> i) & 1) {  // 第 i 位为 1：假设 i 是好人
                for (int j = 0; j < n; ++j) {  // 检查 i 对每个人的评价
                    int v = statements[i][j];  // i 对 j 的陈述值
                    if (v < 2 && ((mask >> j) & 1) != v) return 0;  // 有明确评价（0 或 1）且与实际假设不符，说明该假设矛盾，直接排除
                }  // 结束对 j 的循环
                ++cnt;  // i 的全部陈述都与假设一致，好人数加一
            }  // 结束 if 判断
        }  // 结束对 i 的循环
        return cnt;  // 返回该假设下的好人数
    }  // 结束辅助方法
};  // 结束题解类