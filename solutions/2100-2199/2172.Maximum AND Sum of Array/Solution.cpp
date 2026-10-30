// 题目：2172. 数组的最大与和（Maximum AND Sum of Array）
// 思路：状压 DP——把每个槽位拆成两个「格子」，用 m 位掩码记录哪些格子已占用；掩码从小到大转移，第 cnt 个数放进第 j 个格子。
// 时间复杂度：O(n · 2^m)，m = 2·numSlots，每个状态枚举 m 个格子；空间复杂度：O(2^m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumANDSum(vector<int>& nums, int numSlots) {  // nums：待分配的数字；numSlots：槽位个数（每个槽位可放两个数）
        int n = nums.size();  // 元素个数 n，最多只需要分配 n 个数
        int m = numSlots << 1;  // 每个槽位看成两个格子，共 m 个格子，便于用一个二进制掩码表示占用情况
        int f[1 << m];  // f[mask]：使用 mask 所表示的格子集合时，已放入数字能得到的最大与和
        memset(f, 0, sizeof(f));  // 全部清零，作为 DP 的起点（一个数都不放时答案为 0）
        for (int i = 0; i < 1 << m; ++i) {  // 按掩码递增枚举所有状态，保证转移时用的子状态已经算好
            int cnt = __builtin_popcount(i);  // __builtin_popcount 统计已占用的格子数，也就等于已放入的数字个数
            if (cnt > n) {  // 已经放满了 n 个数，不能再放
                continue;  // 该状态不参与转移，直接跳过
            }  // if 分支结束
            for (int j = 0; j < m; ++j) {  // 枚举最后一个放进去的格子 j
                if (i >> j & 1) {  // 只有 mask 里被占用的格子才可能是「最后放入」的那个
                    f[i] = max(f[i], f[i ^ (1 << j)] + (nums[cnt - 1] & (j / 2 + 1)));  // 从 mask 中删掉 j 得到前一状态，再加上把 nums[cnt-1] 放进第 j/2+1 号槽位的与值（槽位编号从 1 开始）
                }  // if 分支结束
            }  // 所有格子 j 都试完，取最大值
        }  // 掩码循环结束
        return *max_element(f, f + (1 << m));  // 答案不必恰好放满 n 个格子，故在所有可达状态中取最大值
    }  // 方法结束
};  // 类定义结束，源文件到此为止