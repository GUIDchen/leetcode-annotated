// 题目：2518. 好分区的数目（Number of Great Partitions）
// 核心思路：总方案 2^n 减去坏分区。某一组元素和 < k 的划分就是坏分区，用 01 背包 f[i][j] 统计前 i 个数中和为 j（j < k）的子集数。
// 时间复杂度：O(n * k)；空间复杂度：O(n * k)，即 DP 表 f 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    const int mod = 1e9 + 7;  // 取模常数 1e9 + 7，防止方案数溢出

    int countPartitions(vector<int>& nums, int k) {  // nums：待分区的数组；k：每个分区元素和的下界
        long s = accumulate(nums.begin(), nums.end(), 0l);  // 先求数组总和，用于快速排除不可能的情况
        if (s < k * 2) return 0;  // 两组都至少要有 k，总和不足 2k 时一定无解
        int n = nums.size();  // 元素个数
        long f[n + 1][k];  // f[i][j]：前 i 个数中选出和为 j（j < k）的方案数
        int ans = 1;  // ans 从 1 开始，循环中不断翻倍，最终等于 2^n
        memset(f, 0, sizeof f);  // 把 DP 表清零，避免读到未初始化的值
        f[0][0] = 1;  // 边界：从前 0 个数凑出和 0，方案数为 1
        for (int i = 1; i <= n; ++i) {  // 逐个把元素加入背包
            int v = nums[i - 1];  // 当前正在考察的元素值
            ans = ans * 2 % mod;  // 每多一个元素，全部子集方案数翻倍
            for (int j = 0; j < k; ++j) {  // 枚举背包容量，只需处理 0..k-1，和达到 k 就不再是坏分区
                f[i][j] = f[i - 1][j];  // 不选当前元素，方案数继承上一层
                if (j >= v) {  // 容量够放下当前元素时
                    f[i][j] = (f[i][j] + f[i - 1][j - v]) % mod;  // 选当前元素，累加上一层剩余容量对应的方案数
                }  // 结束 if
            }  // 结束内层 for
        }  // 结束外层 for，2^n 与所有坏分区方案数都已算出
        for (int j = 0; j < k; ++j) {  // 枚举所有会构成坏分区的元素和 j < k
            ans = (ans - f[n][j] * 2 % mod + mod) % mod;  // 某一组和 < k 的子集与它的补集构成两类坏划分，故各减一次（乘 2）；加 mod 防止负数
        }  // 结束 for
        return ans;  // 返回好分区数目
    }  // 结束 countPartitions
};  // 结束 Solution 类