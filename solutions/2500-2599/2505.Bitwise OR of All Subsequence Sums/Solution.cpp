// 题目：2505. 所有子序列和的按位或（Bitwise OR of All Subsequence Sums）🔒
// 思路：先统计每个二进制位上 1 的总数；某位出现过就能出现在某个子序列和中，再按“每两个低位进位到高一位”向上累加。
// 时间复杂度：O(31n)，n 为元素个数；空间复杂度：O(1)，只需 64 个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long subsequenceSumOr(vector<int>& nums) {  // nums：输入数组；返回所有子序列和按位或的结果
        vector<long long> cnt(64);  // cnt[i]：所有数中第 i 个二进制位为 1 的个数（long long 防止进位累加溢出）
        long long ans = 0;  // ans：所有子序列和按位或的结果
        for (int v : nums) {  // 遍历每个数
            for (int i = 0; i < 31; ++i) {  // 题目数值在 int 范围内，最多只有低 31 位可能为 1
                if (v >> i & 1) {  // 取出第 i 位，判断是否为 1
                    ++cnt[i];  // 统计这一位上 1 的个数
                }  // 位判断结束
            }  // 位数循环结束
        }  // 元素遍历结束
        for (int i = 0; i < 63; ++i) {  // 从低位到高位处理进位；总和最大约 2^31·n，63 位足够
            if (cnt[i]) {  // 第 i 位至少出现一次，说明某个子序列和的第 i 位可以为 1
                ans |= 1ll << i;  // 把第 i 位置入答案
            }  // 位判断结束
            cnt[i + 1] += cnt[i] / 2;  // 两个第 i 位的 1 相加会向第 i+1 位进位：每 2 个 1 产生一个更高位的 1
        }  // 进位循环结束
        return ans;  // 返回所有子序列和按位或的结果
    }  // 方法结束
};  // 类定义结束