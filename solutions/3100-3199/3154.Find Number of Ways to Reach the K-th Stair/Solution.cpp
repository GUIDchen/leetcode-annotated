// 题目：3154. 到达第 K 级台阶的方案数（Find Number of Ways to Reach the K-th Stair）
// 思路：记忆化搜索，状态 (当前位置 i, 上一步是否向下退 j, 下一次跳跃指数 jump)；向上跳 2^jump 且 jump 加一，向下退只能在未连续后退时做一次。
// 时间复杂度：O(k log k)，jump 只有 O(log k) 种、位置只有 O(k) 种；空间复杂度：O(k log k)，记忆化表规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int waysToReachStair(int k) {  // k：目标台阶编号，返回到达它的方案数
        unordered_map<long long, int> f;  // 记忆化表：把 (位置, 是否刚后退, jump) 打包成一个 64 位 key
        auto dfs = [&](this auto&& dfs, int i, int j, int jump) -> int {  // i：当前台阶；j：1 表示上一步是向下退；jump：下一次向上跳的步长指数
            if (i > k + 1) {  // 越过 k+1 后最多只能退一步，回不到 k
                return 0;  // 该分支无解
            }
            long long key = ((long long) i << 32) | jump << 1 | j;  // 位拼接成 key：高 32 位放 i，中间放 jump，最低位放 j
            if (f.contains(key)) {  // 该状态已经计算过
                return f[key];  // 直接返回缓存中的方案数
            }
            int ans = i == k ? 1 : 0;  // 当前恰好停在 k，本身就是一种方案
            if (i > 0 && j == 0) {  // 台阶 0 以下不存在，且不能连续两次向后下退
                ans += dfs(i - 1, 1, jump);  // 向下退一步并标记 j=1，跳跃步长保持不变
            }
            ans += dfs(i + (1 << jump), 0, jump + 1);  // 向上跳 2^jump 步，j 归零、跳跃指数加一
            f[key] = ans;  // 记录该状态的方案数
            return ans;  // 返回方案总数
        };
        return dfs(1, 0, 0);  // 从第 1 级台阶出发，未后退过，下一次跳 2^0 步
    }
};
