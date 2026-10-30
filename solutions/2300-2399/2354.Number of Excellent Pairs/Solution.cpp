// 题目：2354. 优质数对的数目（Number of Excellent Pairs）
// 思路：优质判据等价于 popcount(a) + popcount(b) ≥ k（按位或与按位与的 1 的个数相加恰为两者 popcount 之和）；先去重，再按 popcount 值桶计数，最后枚举有序对累加。
// 时间复杂度：O(n + 32·m)，m 为去重后元素数；空间复杂度：O(m)。
class Solution {  // LeetCode 约定的题解类
public:
    long long countExcellentPairs(vector<int>& nums, int k) {  // nums 为候选数组（可含重复）；k 为优质对的 1 个数阈值；答案可达 10¹⁰ 需 64 位
        unordered_set<int> s(nums.begin(), nums.end());  // 去重：重复值不影响 popcount 分布统计
        vector<int> cnt(32);  // cnt[x] 表示二进制恰有 x 个 1 的元素个数，值域 30 位内，开 32 足矣
        for (int v : s) ++cnt[__builtin_popcount(v)];  // 遍历去重后的每个值，按 popcount 分桶计数
        long long ans = 0;  // 答案累加器，最坏约 10⁵ × 10⁵ 会超 int，故用 long long
        for (int v : s) {  // 枚举有序对的第一个数 v
            int t = __builtin_popcount(v);  // t 是 v 的二进制中 1 的个数
            for (int i = 0; i < 32; ++i) {  // 枚举第二个数的 popcount 取值 i（0..31）
                if (t + i >= k) {  // 优质条件：两者 popcount 之和 ≥ k
                    ans += cnt[i];  // 有 cnt[i] 个元素能跟 v 组成优质对，全部累加
                }  // if 块结束
            }  // 32 种 popcount 取值枚举结束
        }  // 外层枚举结束
        return ans;  // 返回优质对总数（有序对，(v, v) 自查也计入）
    }  // 方法结束
};  // 类定义结束