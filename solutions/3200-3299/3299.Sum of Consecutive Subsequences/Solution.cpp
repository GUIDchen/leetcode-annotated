// 题目：3299. 连续子序列的和（Sum of Consecutive Subsequences）🔒
// 思路：按元素贡献计数。正反两遍 DP：统计每个元素出现在多少条「下标递增时数值恰好 +1」的链中，再乘以元素值累加。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，left/right 数组与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getSum(vector<int>& nums) {  // nums：输入数组；返回所有连续子序列元素和之和对 1e9+7 取模的结果
        using ll = long long;  // 用 long long 承接中间结果，避免取模前溢出
        const int mod = 1e9 + 7;  // 模数常量 10^9+7
        auto calc = [&](const vector<int>& nums) -> ll {  // 闭包 calc：统计所有「数值随下标递增 1」的连续子序列（长度 >= 2）的贡献
            int n = nums.size();  // n：数组长度
            vector<ll> left(n), right(n);  // left[i]：位置 i 作为链尾时可接的链条数；right[i]：位置 i 作为链头时可接的链条数
            unordered_map<int, ll> cnt;  // cnt[v]：以值 v 结尾、且数值随下标递增 1 的链条数

            for (int i = 1; i < n; ++i) {  // 从左往右扫描，递推以每个位置结尾的链条数
                cnt[nums[i - 1]] = (cnt[nums[i - 1]] + 1 + cnt[nums[i - 1] - 1]) % mod;  // 所有以 nums[i-1]-1 结尾的链都能接上 nums[i-1]，再加一条只含 nums[i-1] 的新链
                left[i] = cnt[nums[i] - 1];  // 位置 i 左侧能接到 nums[i] 前面的链条数（i 作链尾）
            }

            cnt.clear();  // 清空哈希表，改用从右往左的扫描

            for (int i = n - 2; i >= 0; --i) {  // 从右往左扫描，递推以每个位置开头的链条数
                cnt[nums[i + 1]] = (cnt[nums[i + 1]] + 1 + cnt[nums[i + 1] + 1]) % mod;  // 所有以 nums[i+1]+1 开头的链都能前接 nums[i+1]，再加一条只含 nums[i+1] 的新链
                right[i] = cnt[nums[i] + 1];  // 位置 i 右侧能接在 nums[i] 后面的链条数（i 作链头）
            }

            ll ans = 0;  // 累计本方向的元素和贡献
            for (int i = 0; i < n; ++i) {  // 逐个元素统计它被多少条递增链包含
                ans = (ans + (left[i] + right[i] + left[i] * right[i] % mod) * nums[i] % mod) % mod;  // i 作链尾 left[i] 条 + i 作链头 right[i] 条 + i 在中间 left[i]*right[i] 条，再乘元素值
            }
            return ans;  // 返回递增方向的总贡献
        };

        ll x = calc(nums);  // x：所有递增（数值随下标 +1）连续子序列的贡献
        reverse(nums.begin(), nums.end());  // 原地反转，原数组的递减链就变成递增链
        ll y = calc(nums);  // y：所有递减（数值随下标 -1）连续子序列的贡献
        ll s = accumulate(nums.begin(), nums.end(), 0LL);  // s：所有长度为 1 的子序列贡献之和，即整个数组的和
        return static_cast<int>((x + y + s) % mod);  // 递增 + 递减 + 单元素三类贡献相加取模，再转回 int
    }
};
