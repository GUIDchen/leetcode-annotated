// 3836. 恰好 K 个下标对的最大得分 / Maximum Score Using Exactly K Pairs（困难）
// 核心思路：三维 DP，f[i][j][k] 表示 nums1 前 i 个元素与 nums2 前 j 个元素中恰好选出 k 个不交叉下标对的最大得分；每个状态可跳过 nums1[i-1]、跳过 nums2[j-1]，或让两者配成一对（乘积累加）。
// 复杂度：时间 O(n*m*K)，空间 O(n*m*K)。
class Solution {  // LeetCode 要求的类名
public:  // 对外接口区
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int K) {  // 返回恰好 K 对下标配对的最大得分
        int n = nums1.size(), m = nums2.size();  // 两个数组的长度
        long long NEG = LLONG_MIN / 4;  // 负无穷哨兵，取四分之一以免加法溢出
        vector f(n + 1, vector(m + 1, vector<long long>(K + 1, NEG)));  // f[i][j][k]：两个前缀中恰好选出 k 对的最大得分，整体初始化为负无穷
        f[0][0][0] = 0;  // 空前缀选 0 对，得分为 0（合法起点）
        for (int i = 0; i <= n; i++) {  // 枚举 nums1 的前缀长度
            for (int j = 0; j <= m; j++) {  // 枚举 nums2 的前缀长度
                for (int k = 0; k <= K; k++) {  // 枚举已经选出的下标对数
                    if (i > 0) {  // 允许完全不使用 nums1 的最后一个元素
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);  // 继承 i-1 的状态，即 nums1[i-1] 不参与配对
                    }  // 跳过 nums1 末元素的选项结束
                    if (j > 0) {  // 允许完全不使用 nums2 的最后一个元素
                        f[i][j][k] = max(f[i][j][k], f[i][j - 1][k]);  // 继承 j-1 的状态，即 nums2[j-1] 不参与配对
                    }  // 跳过 nums2 末元素的选项结束
                    if (i > 0 && j > 0 && k > 0) {  // 两个前缀都非空，且还需要再凑出一对
                        f[i][j][k] = max(  // 尝试把 nums1[i-1] 与 nums2[j-1] 配成第 k 对
                            f[i][j][k],  // 保留之前（跳过某一侧）得到的更优值
                            f[i - 1][j - 1][k - 1] + 1LL * nums1[i - 1] * nums2[j - 1]);  // 前 k-1 对的最优解加上这对的乘积（1LL 防止 int 相乘溢出）
                    }  // 配对分支结束
                }  // 对数维度循环结束
            }  // nums2 维度循环结束
        }  // nums1 维度循环结束
        return f[n][m][K];  // 两个完整数组恰好 K 对的最大得分
    }  // 方法结束
};  // 类定义结束
