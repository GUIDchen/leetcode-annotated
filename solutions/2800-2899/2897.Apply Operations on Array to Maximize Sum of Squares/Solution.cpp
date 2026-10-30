// 题目：2897. 对数组执行操作使平方和最大（Apply Operations on Array to Maximize Sum of Squares）
// 思路：按二进制位统计每个位置上 1 的总个数；每次把还能用的 1 尽量堆到同一个数上（贪心让大数更大），重复 k 次并累加平方和。
// 时间复杂度：O(31 * (n + k))，n 为数组长度；空间复杂度：O(31)，位计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSum(vector<int>& nums, int k) {  // nums：原数组；k：最终数组中可保留（构造）的元素个数
        int cnt[31]{};  // cnt[i]：第 i 个二进制位上 1 的总个数，初始全 0
        for (int x : nums) {  // 遍历数组中的每个数
            for (int i = 0; i < 31; ++i) {  // 逐位检查该数的二进制表示
                if (x >> i & 1) {  // 第 i 位是 1
                    ++cnt[i];  // 该位的 1 的可用次数加一
                }
            }
        }
        long long ans = 0;  // 平方和答案，用 long long 防止溢出
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        while (k--) {  // 一共构造 k 个数（每次消耗掉一批 1）
            int x = 0;  // 本次构造出来的数
            for (int i = 0; i < 31; ++i) {  // 从低位到高位扫描所有剩余可用的 1
                if (cnt[i]) {  // 该位还有剩余的 1
                    x |= 1 << i;  // 把这一位设为 1
                    --cnt[i];  // 消耗该位的一个 1
                }
            }
            ans = (ans + 1LL * x * x) % mod;  // 累加本数的平方并取模，1LL 保证乘法在 64 位下进行
        }
        return ans;  // 返回 k 个数的平方和取模结果
    }
};