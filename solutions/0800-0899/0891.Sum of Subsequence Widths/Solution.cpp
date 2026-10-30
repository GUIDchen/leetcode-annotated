// 题目：891. 子序列宽度之和（Sum of Subsequence Widths）
// 思路：先排序，把每个子序列的宽度拆成「最大值的贡献 - 最小值的贡献」；排序后第 i 小的数在 2^i 个子序列里当最小值、在 2^(n-1-i) 个里当最大值，合并后即为 (nums[i] - nums[n-1-i]) * 2^i 的累加。
// 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(1)，只用了若干标量变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 取模常量，防止答案超出范围

    int sumSubseqWidths(vector<int>& nums) {  // nums：输入数组；返回所有非空子序列宽度之和（对 mod 取模）
        sort(nums.begin(), nums.end());  // 升序排序：宽度与元素次序无关，排序后最值就落在两端，便于按下标结算贡献
        long ans = 0, p = 1;  // ans 累加答案；p 是 2^i，代表当前下标在子序列中被「选中」的方案数
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n; ++i) {  // 枚举排序后的每个位置，处理第 i 小和第 i 大这一对
            ans = (ans + (nums[i] - nums[n - i - 1]) * p + mod) % mod;  // 第 i 小贡献正、第 i 大贡献负，乘上 2^i 种组合；加 mod 是为了避免负数取模
            p = (p << 1) % mod;  // 幂次翻倍：2^i -> 2^(i+1)，同时取模防溢出
        }  // 所有下标结算完毕
        return ans;  // 返回取模后的答案，值域落在 int 内
    }  // 方法结束
};  // 类定义结束