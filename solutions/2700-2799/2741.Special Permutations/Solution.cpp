// 题目：2741. 特别的排列（Special Permutations）
// 核心思路：状压 DP，f[集合掩码 i][末尾下标 j] 表示已选集合为 i、最后一个是 nums[j] 的合法排列数，按整除关系转移。
// 时间复杂度：O(2^n * n^2)；空间复杂度：O(2^n * n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int specialPerm(vector<int>& nums) {  // nums：互不相同的正整数数组
        const int mod = 1e9 + 7;  // 结果对 1e9+7 取模，防止数值溢出
        int n = nums.size();  // 元素个数
        int m = 1 << n;  // 状态总数：每个元素选或不选，共 2^n 种
        int f[m][n];  // f[集合掩码 i][末尾下标 j]：以 j 结尾且已选集合为 i 的排列数
        memset(f, 0, sizeof(f));  // 全部清零，表示还没有构造出任何排列
        for (int i = 1; i < m; ++i) {  // 枚举所有非空集合（空集 i=0 不合法，跳过）
            for (int j = 0; j < n; ++j) {  // 枚举集合 i 中可能的最后一个元素
                if ((i >> j & 1) == 1) {  // 第 j 位为 1，说明 nums[j] 属于集合 i
                    int ii = i ^ (1 << j);  // 去掉 j 之后得到的前缀集合
                    if (ii == 0) {  // 前缀为空，说明 j 是排列的第一个元素
                        f[i][j] = 1;  // 只有一个元素的排列，方案数为 1
                        continue;  // 没有前驱可枚举，直接看下一个状态
                    }
                    for (int k = 0; k < n; ++k) {  // 枚举前缀集合中的末尾元素 k
                        if (nums[j] % nums[k] == 0 || nums[k] % nums[j] == 0) {  // 相邻两数必须互相整除
                            f[i][j] = (f[i][j] + f[ii][k]) % mod;  // 累加所有合法前缀的方案数并取模
                        }
                    }
                }
            }
        }
        int ans = 0;  // 统计所有以任意元素结尾的完整排列数
        for (int x : f[m - 1]) {  // f[m-1] 是全集状态，遍历它的每一种结尾
            ans = (ans + x) % mod;  // 累加并取模
        }
        return ans;  // 返回长度为 n 的合法排列总数
    }
};