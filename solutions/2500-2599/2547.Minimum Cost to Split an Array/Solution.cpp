// 题目：2547. 拆分数组的最小代价（Minimum Cost to Split an Array）
// 思路：记忆化搜索。f[i] 表示把 nums[i..n-1] 拆完的最小代价；枚举最后一段 [i, j]，该段代价为 k + 段长 - 段内只出现一次的元素个数，再加上后缀 f[j+1]。
// 时间复杂度：O(n^2)，每个状态 i 向后扫一遍 j；空间复杂度：O(n^2)，记忆化数组 O(n)，递归栈上每层还有一个 O(n) 的桶数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(vector<int>& nums, int k) {  // nums：待拆分数组；k：每一段的固定代价
        int n = nums.size();  // n 是数组长度，后续所有边界都以它为准
        int f[n];  // f[i] 记忆「从下标 i 拆到最后」的最小代价，0 表示尚未计算
        memset(f, 0, sizeof f);  // 整体清零，让 0 承担「未计算」的哨兵作用
        function<int(int)> dfs = [&](int i) {  // dfs(i)：返回把 nums[i..] 拆完的最小代价，[&] 以引用方式捕获外部变量
            if (i >= n) {  // 递归出口：后缀已经为空
                return 0;  // 没有元素可拆，代价为 0
            }
            if (f[i]) {  // 该状态之前算过（值非 0）
                return f[i];  // 直接返回缓存值，避免重复搜索同一后缀
            }
            int cnt[n];  // 桶数组：统计当前段内每个值的出现次数（值域 1..n）
            memset(cnt, 0, sizeof cnt);  // 每进入一个新状态都要把桶清零
            int one = 0;  // one：当前段内「只出现一次」的元素个数
            int ans = 1 << 30;  // 用一个足够大的数作为最优值初值
            for (int j = i; j < n; ++j) {  // 枚举当前段的右端点 j，即当前段是 nums[i..j]
                int x = ++cnt[nums[j]];  // 先自增再取值，x 是 nums[j] 在段内新的出现次数
                if (x == 1) {  // 原来是 0 次，现在变成出现 1 次
                    ++one;  // 它成为新的「只出现一次」元素
                } else if (x == 2) {  // 原来是 1 次，现在变成出现 2 次
                    --one;  // 它不再是「只出现一次」元素（出现 3 次以上时 one 不变）
                }
                ans = min(ans, k + j - i + 1 - one + dfs(j + 1));  // 段代价 = k + 段长 - one，再加上后缀的最优代价
            }
            return f[i] = ans;  // 写入并返回 f[i]，同时完成记忆化
        };  // lambda 定义结束，dfs 从下一行起即可递归调用
        return dfs(0);  // 答案：从下标 0 开始拆分的最小代价
    }
};  // 类定义结束
