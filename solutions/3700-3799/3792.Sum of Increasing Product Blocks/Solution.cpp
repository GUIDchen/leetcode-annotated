// 3792. 递增乘积块之和 / Sum of Increasing Product Blocks
// 核心思路：按块模拟，第 i 块由从 k 开始的 i 个连续整数相乘，累加各块乘积并随时对 1e9+7 取模，随后把 k 前移 i。
// 复杂度：时间 O(n²)，空间 O(1)。
class Solution {  // 定义 LeetCode 题解类
public:  // 公开接口
    int sumOfBlocks(int n) {  // 返回前 n 块乘积之和对 1e9+7 取模的结果
        const int mod = 1e9 + 7;  // 取模常量
        long long ans = 0;  // 累加结果
        int k = 1;  // 当前块的起始整数
        for (int i = 1; i <= n; ++i) {  // 依次处理第 i 块（共 i 个数）
            long long x = 1;  // 第 i 块的乘积
            for (int j = k; j < k + i; ++j) {  // 块内包含从 k 开始的 i 个连续整数
                x = x * j % mod;  // 边乘边取模，防止溢出
            }  // 结束块内累乘
            ans = (ans + x) % mod;  // 把当前块乘积累加到答案
            k += i;  // 起点后移 i 个数，作为下一块的起点
        }  // 结束块遍历
        return ans;  // 返回结果
    }  // 结束函数
};  // 结束类
