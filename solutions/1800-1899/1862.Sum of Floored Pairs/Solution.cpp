// 题目：1862. 向下取整数对和（Sum of Floored Pairs）
// 思路：先做值域计数 cnt 与前缀和 s，再枚举分母 y 与商 d，用前缀和一次统计「除以 y 后商恰好为 d」的分子个数，累加 个数 × d × cnt[y]。
// 时间复杂度：O(n + M log M)，M 为最大值（调和级数式枚举倍数）；空间复杂度：O(M)，存放计数与前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfFlooredPairs(vector<int>& nums) {  // nums：待统计的整数数组
        const int mod = 1e9 + 7;  // 题目要求的结果对 1e9+7 取模
        int mx = *max_element(nums.begin(), nums.end());  // 最大值：决定计数数组与前缀和数组的长度
        vector<int> cnt(mx + 1);  // cnt[x]：数值 x 在数组中出现的次数（值域计数）
        vector<int> s(mx + 1);  // s[x]：数值不超过 x 的元素个数（cnt 的前缀和）
        for (int x : nums) {  // 遍历数组，建立值域计数
            ++cnt[x];  // 数值 x 的频次加一
        }  // 计数结束
        for (int i = 1; i <= mx; ++i) {  // 从小到大构造前缀和
            s[i] = s[i - 1] + cnt[i];  // 前缀和递推：不超过 i 的个数 = 不超过 i-1 的个数 + 数值 i 的个数
        }  // 前缀和构造完成
        long long ans = 0;  // 答案可能超过 int 范围，用 long long 累加
        for (int y = 1; y <= mx; ++y) {  // 枚举分母 y（分母只能取数组中出现过的值）
            if (cnt[y]) {  // 该数值没出现过就跳过，它不会出现在任何数对里
                for (int d = 1; d * y <= mx; ++d) {  // 枚举商 d，d*y 是这一档分子的下界，超过最大值即可停止
                    ans += 1LL * cnt[y] * d * (s[min(mx, d * y + y - 1)] - s[d * y - 1]);  // 商为 d 的分子个数 = s[min(mx, d*y+y-1)] - s[d*y-1]；再乘商 d 与分母个数 cnt[y]
                    ans %= mod;  // 每步取模，防止累加溢出
                }  // 这一档商处理完毕
            }  // 这个分母处理完毕
        }  // 所有分母枚举结束
        return ans;  // 返回取模后的答案
    }  // 方法结束
};  // 类定义结束