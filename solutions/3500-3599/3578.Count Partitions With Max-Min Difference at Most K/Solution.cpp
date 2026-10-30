// 题目：3578. 统计极差最大为 K 的分割方式数 / Count Partitions With Max-Min Difference at Most K（中等）
// 核心思路：设 f[r] 表示把前 r 个元素分割、且最后一段以 r 结尾（起点 s >= l）的方案数，g 为 f 的前缀和便于区间求和；用 multiset 维护滑窗 [l, r] 的最大值与最小值，一旦极差超过 k 就把左边界右移，保证以 r 结尾的合法最后一段起点至少为 l，于是 f[r] = f[l-1] + ... + f[r-1] = g[r-1] - g[l-2]。
// 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员函数
    int countPartitions(vector<int>& nums, int k) {  // 返回极差不超过 k 的分割方式数
        const int mod = 1e9 + 7;  // 取模常数
        multiset<int> sl;  // 有序多重集合，用于 O(log n) 维护滑窗最值
        int n = nums.size();  // 数组长度
        vector<int> f(n + 1, 0), g(n + 1, 0);  // f 为以当前位置结尾的方案数，g 为 f 的前缀和
        f[0] = 1;  // 空前缀只有一种分割方式（作为递推边界）
        g[0] = 1;  // 前缀和初值
        int l = 1;  // 合法最后一段起点的下界（1 基准下标）
        for (int r = 1; r <= n; ++r) {  // 枚举分割前缀的长度 r
            int x = nums[r - 1];  // 新加入滑窗的元素
            sl.insert(x);  // 插入有序集合
            while (*sl.rbegin() - *sl.begin() > k) {  // 滑窗极差超过 k
                sl.erase(sl.find(nums[l - 1]));  // 移出左端点对应的元素
                ++l;  // 左边界右移
            }
            f[r] = (g[r - 1] - (l >= 2 ? g[l - 2] : 0) + mod) % mod;  // 最后一段起点可在 [l, r]，方案数由前缀和作差得到
            g[r] = (g[r - 1] + f[r]) % mod;  // 更新前缀和
        }
        return f[n];  // 前 n 个元素的方案数即答案
    }
};
