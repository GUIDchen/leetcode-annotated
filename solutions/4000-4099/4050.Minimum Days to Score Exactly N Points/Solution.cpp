// 题目：4050. 得到恰好 N 分的最少天数（Minimum Days to Score Exactly N Points）
// 思路：完全背包式的预处理 DP。一段连续 j 天恰好得 1+2+...+j = j(j+1)/2 分，故 f[i] = min(f[i-s] + j + 1)，s 取遍不超过 i 的三角数；把 f[0] 设为 -1 作为哨兵，使「只取一个三角数」的总天数正好是 j。表在静态局部 lambda 里只算一次，之后 O(1) 查表。
// 复杂度：时间复杂度 O(M * sqrt(M))，M = 100001 为预处理上界，单次查询 O(1)；空间复杂度 O(M)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDays(int n) {  // n：目标分数；返回恰好得到 n 分的最少天数
        static const auto f = [] {  // 静态局部 lambda：整个评测进程只计算一次，多次调用复用同一张表
            constexpr int mx = 100001;  // 预处理的最大分数
            vector<int> f(mx, INT_MAX);  // f[i]：恰好得到 i 分的最少天数，先全部置为无穷

            f[0] = -1;  // 哨兵：让转移式里的 +1 在「只取一段」时被抵消，使 j(j+1)/2 分恰好花 j 天

            for (int i = 1; i < mx; i++) {  // 从小到大递推每个分数
                for (int j = 1; j * (j + 1) / 2 <= i; j++) {  // 枚举本段天数 j，其三角数不超过 i
                    int s = j * (j + 1) / 2;  // 连续 j 天得到的分数为 1+2+...+j
                    f[i] = std::min(f[i], f[i - s] + j + 1);  // 用这一段的 s 分，天数 = 剩余部分的天数 + j + 1
                }  // 天数 j 的枚举结束
            }  // 分数 i 的递推结束

            return f;  // 返回预处理好的表
        }();  // 立即调用 lambda，完成预处理

        return f[n];  // 直接查表得到答案
    }  // 方法结束
};  // 题解类结束