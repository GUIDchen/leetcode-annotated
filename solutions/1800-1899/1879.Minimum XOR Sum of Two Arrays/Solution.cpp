// 题目：1879. 两个数组最小的异或值之和（Minimum XOR Sum of Two Arrays）
// 思路：状压 DP。f[i][j] 表示 nums1 的前 i 个元素与 nums2 中「集合 j 所含下标」配对后的最小异或和，枚举第 i 个元素与集合 j 中的哪个下标 k 配对来转移。
// 时间复杂度：O(n^2 * 2^n)，n <= 14；空间复杂度：O(n * 2^n)，即 DP 表的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：长度均为 n 的数组；返回所有排列配对方式中最小的异或值之和
        int n = nums1.size();  // n：数组长度，也是状态压缩的规模
        int f[n + 1][1 << n];  // f[i][j]：nums1 前 i 个元素与集合 j（二进制第 k 位为 1 表示 nums2[k] 已被使用）配对的最小异或和
        memset(f, 0x3f, sizeof(f));  // 先整体填成一个很大的数，表示该状态暂时不可达
        f[0][0] = 0;  // 边界：没有元素要配、也没有用过任何下标时，异或和为 0
        for (int i = 1; i <= n; ++i) {  // 阶段：从小到大逐个处理 nums1 的前 i 个元素
            for (int j = 0; j < 1 << n; ++j) {  // 状态：枚举所有可能的使用集合 j（j < 2^n）
                for (int k = 0; k < n; ++k) {  // 决策：尝试让 nums1[i-1] 与 nums2[k] 配成一对
                    if (j >> k & 1) {  // 集合 j 必须包含下标 k（(j >> k) & 1 为 1）时才可能由它转移而来
                        f[i][j] = min(f[i][j], f[i - 1][j ^ (1 << k)] + (nums1[i - 1] ^ nums2[k]));  // j ^ (1 << k) 把 k 从集合中剔除得到上一层状态，再加上本次配对的异或代价
                    }  // 该决策处理完毕
                }  // 决策 k 枚举结束
            }  // 状态 j 枚举结束
        }  // 阶段 i 枚举结束
        return f[n][(1 << n) - 1];  // 全部元素配对完成、nums2 的所有下标都用过时的最优答案
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行）