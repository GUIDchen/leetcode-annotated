// 题目：3177. 求出最长好子序列 II（Find the Maximum Length of a Good Subsequence II）
// 思路：沿用 3176 的 DP，但把「枚举前驱」换成查表：mp[h][值] 记录以该值结尾的最优长度，g[h] 记录该额度下最大的两个长度（需区分结尾值），从而 O(1) 转移。
// 时间复杂度：O(n k)，哈希表查询与更新均摊 O(1)；空间复杂度：O(n k)，即状态表 f 与 mp 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumLength(vector<int>& nums, int k) {  // nums：输入数组；k：允许的相邻不相等次数上限
        int n = nums.size();  // 记录数组长度，用于确定状态表规模
        vector<vector<int>> f(n, vector<int>(k + 1));  // f[i][h]：以 i 结尾、额度不超过 h 的最长长度
        vector<unordered_map<int, int>> mp(k + 1);  // mp[h]：按结尾值分组，记录额度 h 下的最优长度
        vector<vector<int>> g(k + 1, vector<int>(3));  // g[h] 三项：最大值对应的结尾值、最大值本身、次大值
        int ans = 0;  // 记录全局最优答案
        for (int i = 0; i < n; ++i) {  // 依次把每个元素作为子序列的结尾来处理
            for (int h = 0; h <= k; ++h) {  // 枚举已使用的相邻不相等次数上限 h
                f[i][h] = mp[h][nums[i]];  // 先取「结尾值与当前值相同」时已有的最优长度
                if (h > 0) {  // 额度还有剩余时，才可能通过换结尾值产生一次坏对
                    if (g[h - 1][0] != nums[i]) {  // g[h-1] 的最优结尾值与当前值不同
                        f[i][h] = max(f[i][h], g[h - 1][1]);  // 可以直接接上该额度下的最大值
                    } else {  // g[h-1] 的最优结尾值恰好就是当前值
                        f[i][h] = max(f[i][h], g[h - 1][2]);  // 只能接次大值，避免把同一序列重复计数
                    }
                }
                ++f[i][h];  // 把当前元素本身计入长度
                mp[h][nums[i]] = max(mp[h][nums[i]], f[i][h]);  // 刷新「以 nums[i] 结尾」的最优长度
                if (g[h][0] != nums[i]) {  // 当前最优值来自新的结尾值，需要重排最大值与次大值
                    if (f[i][h] >= g[h][1]) {  // 当前长度不小于原有最大值，说明它将取代最大值
                        g[h][2] = g[h][1];  // 原最大值退为次大值
                        g[h][1] = f[i][h];  // 记录新的最大值
                        g[h][0] = nums[i];  // 同时记录最大值对应的结尾值，供下次比对
                    } else {  // 当前长度未超过最大值
                        g[h][2] = max(g[h][2], f[i][h]);  // 只尝试刷新次大值
                    }
                } else {  // 结尾值正是当前最大值对应的值，最大值与结尾值保持一致
                    g[h][1] = max(g[h][1], f[i][h]);  // 原地刷新最大值即可
                }
                ans = max(ans, f[i][h]);  // 每个状态都可能成为最终答案，随时更新
            }
        }

        return ans;  // 返回最长好子序列的长度
    }
};