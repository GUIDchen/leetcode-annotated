// 题目：1253. 重构 2 行二进制矩阵（Reconstruct a 2-Row Binary Matrix）
// 思路：先填 colsum 为 2 的列（两行都必须放 1），再贪心处理 colsum 为 1 的列——哪行剩余配额多就把 1 放哪行；任一时刻配额为负即无解。
// 时间复杂度：O(n)，n 为列数，每列只处理一次；空间复杂度：O(n)，除返回矩阵外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {  // upper/lower：上、下两行各自应放的 1 的个数；colsum[j]：第 j 列 1 的个数；返回任意一个可行矩阵
        int n = colsum.size();  // n 是矩阵的列数，也是 colsum 的长度
        vector<vector<int>> ans(2, vector<int>(n));  // 答案矩阵 2 行 n 列，先把所有位置初始化为 0
        for (int j = 0; j < n; ++j) {  // 从左到右逐列构造
            if (colsum[j] == 2) {  // 情况一：这一列必须放两个 1
                ans[0][j] = ans[1][j] = 1;  // 上下两行都置 1（链式赋值从右往左执行）
                upper--;  // 上行的配额随之减一
                lower--;  // 下行的配额随之减一
            }
            if (colsum[j] == 1) {  // 情况二：这一列恰好一个 1，需要决定放在哪一行
                if (upper > lower) {  // 贪心：剩余可用 1 更多的那一行优先填，避免后面出现某行不够用
                    upper--;  // 上行配额减一
                    ans[0][j] = 1;  // 于是把这一列的 1 记在上行
                } else {  // else 分支：上行配额不多于下行，于是把这一列的 1 让给下行
                    lower--;  // 下行配额减一
                    ans[1][j] = 1;  // 于是把这一列的 1 记在下行
                }
            }
            if (upper < 0 || lower < 0) {  // 某行配额一旦为负，说明已经放多了，此构造方案不可行
                break;  // 提前结束构造，交给最后一行统一判空
            }
        }
        return upper || lower ? vector<vector<int>>() : ans;  // 两行配额必须恰好用完：否则无解返回空矩阵，否则返回构造好的 ans
    }
};