// 题目：2844. 生成特殊数字的最少操作（Minimum Operations to Make a Special Number）
// 思路：记忆化 DFS，状态为 (下标 i, 已保留数字模 25 的余数 k)；每位数字可以删除或保留，走到末尾且余数为 0 时删除次数最少。
// 时间复杂度：O(n * 25)，共 n*25 个状态、每个状态两次转移；空间复杂度：O(n * 25)，用于记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperations(string num) {  // num：只含数字的字符串，可以删除其中任意一位
        int n = num.size();  // 数字串长度
        int f[n][25];  // 记忆化数组：f[i][k] 表示处理到下标 i、当前余数为 k 时的最少删除次数
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示该状态还没计算过
        auto dfs = [&](this auto&& dfs, int i, int k) -> int {  // 记忆化 DFS；C++23 显式对象参数 this auto&& 让 lambda 能递归调用自己
            if (i == n) {  // 递归边界：所有数位都处理完了
                return k == 0 ? 0 : n;  // 余数为 0 说明保留下来的数字是 25 的倍数，无需再删；否则只能把 n 位全部删掉，代价为 n
            }
            if (f[i][k] != -1) {  // 该状态已经算过，直接复用缓存值
                return f[i][k];  // 返回缓存的最优值
            }
            f[i][k] = dfs(i + 1, k) + 1;  // 方案一：删除第 i 位，删除次数 +1
            f[i][k] = min(f[i][k], dfs(i + 1, (k * 10 + num[i] - '0') % 25));  // 方案二：保留第 i 位，十进制余数向前推进后对 25 取模，取两种方案中较小者
            return f[i][k];  // 返回当前状态的最优值
        };
        return dfs(0, 0);  // 从下标 0、余数 0 开始搜索
    }
};
