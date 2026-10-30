// 题目：3801. 合并有序列表的最小成本（Minimum Cost to Merge Sorted Lists）
// 思路：预处理每个子集的中位数，再对子集做区间 DP：f[mask] = min(f[j] + f[mask^j] + |med[j] - med[mask^j]|) + 元素个数。
// 时间复杂度：O(2^n · n · log V)，枚举子集并二分中位数；空间复杂度：O(2^n)，存放每个子集的计数、中位数与 DP 值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minMergeCost(vector<vector<int>>& lists) {  // lists 中每个子数组都已升序，返回合并成一个数组的最小成本
        int n = lists.size();  // 子数组个数
        vector<int> vals;  // 收集所有出现过的数值
        for (auto& v : lists) {  // 遍历每个子数组
            vals.insert(vals.end(), v.begin(), v.end());  // 把它的元素追加到 vals 末尾
        }  // 结束 for (auto& v : lists)
        sort(vals.begin(), vals.end());  // 排序，便于二分
        vals.erase(unique(vals.begin(), vals.end()), vals.end());  // 去重，得到有序的候选数值集合

        vector<int> cnt(1 << n);  // cnt[mask]：mask 内所有子数组的元素总数
        vector<int> med(1 << n);  // med[mask]：mask 内所有元素的（下）中位数
        for (int i = 1; i < 1 << n; ++i) {  // 从小到大枚举每个非空子集 mask
            for (int j = 0; j < n; ++j) {  // 检查 mask 的每一位
                if (i >> j & 1) {  // 第 j 个子数组在 mask 里
                    cnt[i] += lists[j].size();  // 累加该子数组的元素个数
                }  // 结束 if (i >> j & 1)
            }  // 结束 for (int j = 0; j < n; ++j)
            int need = (cnt[i] + 1) / 2;  // 中位数在全体元素中的排名（向下取整的中位）
            int l = 0, r = vals.size() - 1;  // 在去重后的数值上二分，l、r 为左右边界
            while (l < r) {  // 找到最小的下标 l，使「≤ vals[l] 的元素个数 ≥ need」
                int mid = (l + r) >> 1;  // 二分中点
                int le = 0;  // 统计 ≤ vals[mid] 的元素个数
                for (int b = i; b; b &= b - 1) {  // 遍历 mask 的所有置位（每次消掉最低位）
                    int id = __builtin_ctz(b);  // 最低置位对应的子数组下标
                    le += upper_bound(lists[id].begin(), lists[id].end(), vals[mid]) - lists[id].begin();  // 累加该子数组中 ≤ vals[mid] 的元素个数
                    if (le >= need) {  // 个数已经够用
                        break;  // 提前结束统计
                    }  // 结束 if (le >= need)
                }  // 结束 for (int b = i; b; b &= b - 1)
                if (le >= need) {  // 数量够，答案可以更小
                    r = mid;  // 收缩右边界
                } else {  // 数量不够
                    l = mid + 1;  // 增大左边界
                }  // 结束 else
            }  // 结束 while (l < r)
            med[i] = vals[l];  // 记录该子集的中位数
        }  // 结束 for (int i = 1; i < 1 << n; ++i)

        vector<long long> f(1 << n, 1e18);  // f[mask]：把 mask 内子数组合并成一个数组的最小代价
        for (int i = 1; i < 1 << n; ++i) {  // 枚举每个非空子集
            if (__builtin_popcount(i) == 1) {  // 只有一个子数组
                f[i] = 0;  // 无需合并，代价为 0
                continue;  // 直接处理下一个子集
            }  // 结束 if (__builtin_popcount(i) == 1)
            for (int j = (i - 1) & i; j; j = (j - 1) & i) {  // 枚举 i 的所有非空真子集 j
                int k = i ^ j;  // k 是 i 中除去 j 剩下的部分
                if (j <= k) {  // 只算一次，避免 (j,k) 与 (k,j) 重复
                    f[i] = min(f[i], f[j] + f[k] + abs(med[j] - med[k]));  // 先分别合并两半，再付出两半中位数之差的代价
                }  // 结束 if (j <= k)
            }  // 结束 for (int j = (i - 1) & i; j; j = (j - 1) & i)
            f[i] += cnt[i];  // 新合并出的数组每个元素都要付出一次代价，共 cnt[i]
        }  // 结束 for (int i = 1; i < 1 << n; ++i)
        return f[(1 << n) - 1];  // 全部子数组合并成一个数组的结果
    }  // 结束 long long minMergeCost(vector<vector<int>>& lists)
};  // 结束 class Solution
