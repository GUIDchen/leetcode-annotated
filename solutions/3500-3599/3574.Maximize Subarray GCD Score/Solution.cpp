// 题目：3574. 最大子数组 GCD 分数 / Maximize Subarray GCD Score（困难）
// 核心思路：先统计每个元素的因子 2 个数 cnt[i]；枚举子数组左端点并向右扩展，用 gcd 维护区间 GCD，同时维护区间内最小因子 2 个数 mi 与取到该最小值的元素个数 t。因为翻倍一个元素等价于把它的因子 2 个数加一，所以只有把取到最小值的这 t 个元素全部翻倍才能让 GCD 再乘 2，条件是 t <= k；于是得分 = 长度 * (t <= k ? 2 * g : g)，枚举过程中取最大值。
// 复杂度：时间复杂度 O(n^2 log V)（V 为元素最大值），空间复杂度 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员函数
    long long maxGCDScore(vector<int>& nums, int k) {  // 返回最大子数组 GCD 分数，nums 为正整数数组，k 为最多翻倍次数
        int n = nums.size();  // 数组长度
        vector<int> cnt(n);  // cnt[i] 记录 nums[i] 中因子 2 的个数
        for (int i = 0; i < n; ++i) {  // 预处理每个元素的因子 2 个数
            for (int x = nums[i]; x % 2 == 0; x /= 2) {  // 不断除以 2，直到变成奇数
                ++cnt[i];  // 因子 2 的个数加一
            }
        }

        long long ans = 0;  // 记录最大得分
        for (int l = 0; l < n; ++l) {  // 枚举子数组左端点 l
            int g = 0;  // 当前子数组的 GCD，0 与任意数取 gcd 仍是该数
            int mi = INT32_MAX;  // 当前子数组中最小的因子 2 个数
            int t = 0;  // 取到最小因子 2 个数的元素个数
            for (int r = l; r < n; ++r) {  // 枚举子数组右端点 r
                g = gcd(g, nums[r]);  // 维护区间 GCD
                if (cnt[r] < mi) {  // 出现了更小的因子 2 个数
                    mi = cnt[r];  // 更新最小值
                    t = 1;  // 目前只有当前元素取到最小值
                } else if (cnt[r] == mi) {  // 与当前最小值相等
                    ++t;  // 取到最小值的元素个数加一
                }
                long long score = static_cast<long long>(r - l + 1) * (t > k ? g : g * 2);  // 得分 = 长度 * GCD；最小值元素都能翻倍时 GCD 翻倍
                ans = max(ans, score);  // 用当前得分更新答案
            }
        }

        return ans;  // 返回最大得分
    }
};
