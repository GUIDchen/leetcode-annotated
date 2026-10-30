// 题目：1815. 得到新鲜甜甜圈的最多组数（Maximum Number of Groups Getting Fresh Donuts）
// 思路：余数为 0 的组直接算作满意组；其余组按余数用五进制压缩成状态，记忆化搜索 dfs(state, mod) 枚举下一组，若当前累计余数为 0 则该组满意。
// 时间复杂度：O(batchSize^batchSize * 状态数) 的记忆化搜索，实际远小于上界；空间复杂度：O(状态数)，哈希表缓存每个状态的最优值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxHappyGroups(int batchSize, vector<int>& groups) {  // batchSize：每批甜甜圈数；groups：每组人数
        using ll = long long;  // 状态用 64 位整数压缩，避免溢出
        unordered_map<ll, int> f;  // 记忆化哈希表：键是压缩状态，值是还能得到的满意组数
        ll state = 0;  // 用五进制位段记录各个非零余数还有多少组
        int ans = 0;  // 已经确定满意的组数
        for (auto& v : groups) {  // 先处理所有组
            int i = v % batchSize;  // 该组人数对 batchSize 取余
            ans += i == 0;  // 余数为 0 的组单独成批，直接算作满意组
            if (i) {  // 余数非 0 的组才需要纳入状态
                state += 1ll << (i * 5);  // 第 i 个五进制位段加 1（每个位段占 5 个二进制位）
            }
        }
        function<int(ll, int)> dfs = [&](ll state, int mod) {  // 记忆化搜索：state 为剩余组的状态，mod 为当前批已累计的余数
            if (f.count(state)) {  // 该状态之前算过
                return f[state];  // 直接返回缓存的结果
            }
            int res = 0;  // 当前状态能额外得到的满意组数
            int x = mod == 0;  // 若此前累计余数为 0，说明新开一批，本组开始前甜甜圈是新鲜的
            for (int i = 1; i < batchSize; ++i) {  // 枚举下一组使用的余数 i
                if (state >> (i * 5) & 31) {  // 取出第 i 个位段的计数，非 0 说明还有该余数的组可用
                    int t = dfs(state - (1ll << (i * 5)), (mod + i) % batchSize);  // 用掉一个余数 i 的组后递归
                    res = max(res, t + x);  // 当前组是否满意（x）加上后续最优值，取最大
                }
            }
            return f[state] = res;  // 记忆化后返回当前状态的最优值
        };  // dfs lambda 定义结束
        ans += dfs(state, 0);  // 剩余组的最优结果累加到答案上
        return ans;  // 返回最多满意组数
    }
};  // 结束 Solution 类定义