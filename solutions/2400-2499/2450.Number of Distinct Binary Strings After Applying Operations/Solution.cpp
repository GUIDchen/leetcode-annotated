// 题目：2450. 应用操作后不同二进制字符串的数量（Number of Distinct Binary Strings After Applying Operations）
// 思路：长度为 k 的窗口共有 n-k+1 个，每个窗口可以独立选择翻转或不翻转，故方案数是 2^(n-k+1) 对 1e9+7 取模。
// 时间复杂度：O(n)，循环执行 n-k+1 次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 模数 10^9+7，答案指数级增长必须随时取模

    int countDistinctStrings(string s, int k) {  // s：原二进制字符串；k：每次操作选取的子串长度
        int ans = 1;  // 方案数累乘器，初值 1（即 2 的 0 次方）
        for (int i = 0; i < s.size() - k + 1; ++i) {  // 循环次数就是长度 k 的滑动窗口个数 n-k+1
            ans = (ans * 2) % mod;  // 每多一个独立窗口方案数就翻倍，并及时取模防止 int 溢出
        }
        return ans;  // 返回 2^(n-k+1) mod (10^9+7)
    }
};