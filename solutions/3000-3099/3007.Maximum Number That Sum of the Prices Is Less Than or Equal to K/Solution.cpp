// 题目：3007. 价值和小于等于 K 的最大数字（Maximum Number That Sum of the Prices Is Less Than or Equal to K）
// 核心思路：价值和随数字单调不减，因此二分答案；用数位 DP（记忆化）在 O(位数 × 位数) 内算出 [0, num] 的价值总和，据此收缩二分区间。
// 时间复杂度：O(log² r)，二分 O(log r) 轮、每轮数位 DP 状态数 O(log² r)；空间复杂度：O(log² r)，记忆化数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long findMaximumNumber(long long k, int x) {  // k：价值和上限；x：只统计位置为 x 倍数的二进制位
        using ll = long long;  // 给 long long 起别名，简化后续书写
        ll l = 1, r = 1e17;  // 二分答案的下界与上界（答案不超过 1e17）
        ll num = 0;  // num 是当前二分到的数，dfs 会读取它逐位枚举
        ll f[65][65];  // 数位 DP 的记忆化数组：f[剩余位数][已累计的价值]
        auto dfs = [&](this auto&& dfs, int pos, int cnt, bool limit) -> ll {  // 递归 lambda：pos 为剩余位数，cnt 为已累计价值，limit 表示是否贴着 num 的上界
            if (pos == 0) {  // 位数用完了，这条路径的价值就是 cnt
                return cnt;  // 返回这条路径的价值
            }  // if 分支结束
            if (!limit && f[pos][cnt] != -1) {  // 不贴上限且之前算过，直接复用记忆化结果
                return f[pos][cnt];  // 返回缓存值
            }  // if 分支结束
            int up = limit ? num >> (pos - 1) & 1 : 1;  // 这一位能取的最大值：贴上限时由 num 的当前位决定，否则可以取到 1
            ll ans = 0;  // 累加所有合法分支带来的价值
            for (int i = 0; i <= up; ++i) {  // 枚举这一位所有可能的取值
                ans += dfs(pos - 1, cnt + (i == 1 && pos % x == 0), limit && i == up);  // 该位取 1 且位数位置是 x 的倍数时价值加一，同时把 limit 向下传递
            }  // 枚举分支累加结束
            if (!limit) {  // 只有不贴上限的结果才能记忆化，否则结果依赖具体的 num
                f[pos][cnt] = ans;  // 写入缓存
            }  // if 分支结束
            return ans;  // 返回 [0, num] 内所有数字的价值总和
        };  // 递归 lambda 定义结束
        while (l < r) {  // 二分：寻找满足「价值和 <= k」的最大数字
            ll mid = (l + r + 1) >> 1;  // 取上中位数，既保证区间收缩又不会死循环
            num = mid;  // 把当前二分的数写进闭包变量，供 dfs 读取各位
            memset(f, -1, sizeof(f));  // 每轮都把记忆化数组重置为 -1
            int pos = 64 - __builtin_clzll(mid);  // mid 的二进制位数（64 减去前导零个数）
            if (dfs(pos, 0, true) <= k) {  // 价值总和不超过 k，说明答案至少是 mid，向右收缩
                l = mid;  // 下界抬到 mid
            } else {  // 否则答案一定严格小于 mid
                r = mid - 1;  // 上界降到 mid - 1
            }  // if / else 分支结束
        }  // 二分循环结束
        return l;  // 此时 l == r，就是最大可行数字
    }  // 方法结束
};  // 类定义结束
