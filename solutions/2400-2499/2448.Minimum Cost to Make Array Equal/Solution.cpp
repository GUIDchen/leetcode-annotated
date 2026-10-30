// 题目：2448. 使数组相等的最小开销（Minimum Cost to Make Array Equal）
// 思路：把 (nums[i], cost[i]) 按数值升序排序，做两条前缀和：f 记 Σ值×单价、g 记 Σ单价；当目标值取某个 arr[i-1] 时，左侧元素都要抬到该值、右侧元素都要压到该值，代价可由前缀和 O(1) 算出，枚举所有候选目标取最小。
// 时间复杂度：O(n log n)，瓶颈在排序（枚举是 O(n)）；空间复杂度：O(n)，配对数组与前缀和数组。
using ll = long long;  // 把 long long 缩写为 ll，累加代价可能超过 32 位

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minCost(vector<int>& nums, vector<int>& cost) {  // nums 是原数组，cost 是每个位置的单位改动开销
        int n = nums.size();  // 数组长度
        vector<pair<int, int>> arr(n);  // 把数值与单价绑定在一起，便于整体排序
        for (int i = 0; i < n; ++i) arr[i] = {nums[i], cost[i]};  // 逐位打包成 (数值, 单价) 二元组
        sort(arr.begin(), arr.end());  // 按数值升序排序，这样下标 i 左侧就恰好是更小的数
        vector<ll> f(n + 1), g(n + 1);  // f：值×单价的前缀和；g：单价的前缀和；多开一位让 f[0]=g[0]=0
        for (int i = 1; i <= n; ++i) {  // 从 1 开始递推前缀和
            auto [a, b] = arr[i - 1];  // 结构化绑定取出第 i 个元素的数值 a 与单价 b
            f[i] = f[i - 1] + 1ll * a * b;  // 前缀累加 数值×单价（1ll 保证乘法在 64 位下进行）
            g[i] = g[i - 1] + b;  // 前缀累加单价，即左侧每个元素改动 1 的总开销系数
        }
        ll ans = 1e18;  // 用一个足够大的数初始化答案
        for (int i = 1; i <= n; ++i) {  // 枚举目标值：把所有数都变成 arr[i-1] 的数值
            auto [a, _] = arr[i - 1];  // 取出候选目标值 a，单价这一项用不上
            ll l = 1ll * a * g[i - 1] - f[i - 1];  // 左侧（更小的数）全部抬到 a：a*Σ单价 - Σ值×单价
            ll r = f[n] - f[i] - 1ll * a * (g[n] - g[i]);  // 右侧（更大的数）全部压到 a：Σ值×单价 - a*Σ单价
            ans = min(ans, l + r);  // 左右两侧代价相加，与当前最优解取较小者
        }
        return ans;  // 返回所有候选目标中的最小总开销
    }
};
