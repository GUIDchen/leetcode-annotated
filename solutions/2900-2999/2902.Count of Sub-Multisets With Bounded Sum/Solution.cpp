// 题目：2902. 和带限制的子多重集合的数目（Count of Sub-Multisets With Bounded Sum）
// 思路：按数值做有界背包，用「先做完全背包式前缀和、再减去超量取法」的滑动窗口技巧把每种数值的转移压到 O(r)；数值 0 不改变和，最后单独乘以取法数。
// 时间复杂度：O(V * r)，V 为不同数值的个数；空间复杂度：O(r)，另有 20001 大小的频次与 dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSubMultisets(const vector<int>& nums, int l, int r) {  // nums：输入多重集合；l、r：子多重集和的下界与上界
        int cnt[20001] = {};  // cnt[v]：数值 v 在 nums 中出现的次数（值域上界 2e4）
        int memo[20001] = {};  // memo[s]：已处理数值能凑出和 s 的子多重集方案数
        const int mod = 1000000007;  // 取模常数
        for (int n : nums) {  // 遍历 nums，统计每个数值的出现次数
            ++cnt[n];  // 数值 n 的频次加一
        }  // 统计结束
        fill_n(memo, cnt[1] + 1, 1);  // 只考虑数值 1 时，和 0..cnt[1] 各只有一种取法（取 0..cnt[1] 个 1）
        for (int n = 2, total = cnt[1]; n <= r; ++n) {  // n 为当前处理的数值，total 为目前所有数值能凑出的最大和
            if (!cnt[n]) {  // 数值 n 没有出现
                continue;  // 直接处理下一个数值
            }  // if 语句结束
            int top = (cnt[n] + 1) * n;  // (cnt[n]+1)*n 即「用了超过 cnt[n] 个 n」的起始和，用于扣除超量部分
            total += n * cnt[n];  // 把 n 的全部副本并入当前总容量
            for (int i = n, ii = min(total, r); i <= ii; ++i) {  // 正向做完全背包式前缀和：允许取任意多个 n
                memo[i] = (memo[i] + memo[i - n]) % mod;  // memo[i-n] 本轮已被更新，故累加相当于再多取一个 n
            }  // for 循环结束
            for (int i = min(total, r); i >= top; --i) {  // 倒序扣掉用了超过 cnt[n] 个 n 的非法方案
                memo[i] = (mod + memo[i] - memo[i - top]) % mod;  // 减掉 memo[i-top] 对应的超量取法，加 mod 防止出现负数
            }  // for 循环结束
        }  // n 循环结束
        return accumulate(memo + l, memo + r + 1, 0LL) * (cnt[0] + 1) % mod;  // 对 [l, r] 区间求和，再乘上数值 0 的 (cnt[0]+1) 种取法（选 0..cnt[0] 个）
    }  // 方法结束
};  // 类定义结束
