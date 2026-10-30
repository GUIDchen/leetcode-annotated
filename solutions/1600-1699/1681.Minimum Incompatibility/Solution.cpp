// 题目：1681. 最小不兼容性（Minimum Incompatibility）
// 思路：状压 DP。先用 g[mask] 预处理每个「元素个数为 n/k 且数字互不相同」的子集的不兼容性，再在状态 mask 上枚举剩余可选位置组成的子集做转移，f[mask] 表示恰好覆盖 mask 的最小代价。
// 时间复杂度：O(n·2^n + 3^n)，子集枚举主导（n ≤ 16）；空间复杂度：O(2^n)，g 与 f 两个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumIncompatibility(vector<int>& nums, int k) {  // nums：待分组数字；k：组数；返回最小不兼容性之和
        int n = nums.size();  // n 是数字个数
        int m = n / k;  // 每组恰好 m 个数字
        int g[1 << n];  // g[mask]：mask 这个子集单独作为一组时的不兼容性（最大值减最小值）
        memset(g, -1, sizeof(g));  // 初始化为 -1，表示该子集不能单独成组
        for (int i = 1; i < 1 << n; ++i) {  // 枚举所有非空子集
            if (__builtin_popcount(i) != m) {  // 元素个数不是 m 的子集不能成组
                continue;  // 直接跳过
            }
            unordered_set<int> s;  // 用集合检查子集内部是否有重复数字
            int mi = 20, mx = 0;  // mi、mx 记录子集的最小值与最大值（数字不超过 16，20 当哨兵）
            for (int j = 0; j < n; ++j) {  // 逐位检查哪些位置被选进子集
                if (i >> j & 1) {  // 第 j 位为 1，说明 nums[j] 属于子集 i
                    if (s.count(nums[j])) {  // 出现重复数字，这个子集不合法
                        break;  // 提前跳出内层循环
                    }
                    s.insert(nums[j]);  // 记录该数字，供后续去重判断
                    mi = min(mi, nums[j]);  // 更新子集最小值
                    mx = max(mx, nums[j]);  // 更新子集最大值
                }
            }
            if (s.size() == m) {  // 集合大小正好为 m，说明这 m 个数字互不相同
                g[i] = mx - mi;  // 该子集的不兼容性等于最大值减最小值
            }
        }
        int f[1 << n];  // f[mask]：用若干合法组恰好覆盖 mask 的最小不兼容性之和
        memset(f, 0x3f, sizeof(f));  // 初始化为无穷大，表示暂时不可达
        f[0] = 0;  // 空集不需要任何组，代价为 0
        for (int i = 0; i < 1 << n; ++i) {  // 按 mask 递增顺序推状态
            if (f[i] == 0x3f3f3f3f) {  // 该状态不可达，无法继续扩展
                continue;  // 跳过
            }
            unordered_set<int> s;  // 记录已经选过代表的数字，保证同一组内不出现重复值
            int mask = 0;  // mask 汇总「每个不同数值各取一个代表位置」的位
            for (int j = 0; j < n; ++j) {  // 遍历所有位置
                if ((i >> j & 1) == 0 && !s.count(nums[j])) {  // 位置 j 还没被使用，且它对应的数值还没被选作代表
                    s.insert(nums[j]);  // 标记该数值已出现
                    mask |= 1 << j;  // 把位置 j 加入候选位掩码
                }
            }
            if (s.size() < m) {  // 剩下的不同数值不足 m 个，无法再凑出一组
                continue;  // 跳过
            }
            for (int j = mask; j; j = (j - 1) & mask) {  // 枚举 mask 的所有非空子集，每个子集都是候选的下一组
                if (g[j] != -1) {  // 该子集本身能作为合法的一组
                    f[i | j] = min(f[i | j], f[i] + g[j]);  // 用这一组更新目标状态的最优值
                }
            }
        }
        return f[(1 << n) - 1] == 0x3f3f3f3f ? -1 : f[(1 << n) - 1];  // 全选状态仍为无穷大说明无解，返回 -1，否则返回该状态的最小代价
    }
};  // 题解类结束