// 题目：2147. 分隔长廊的方案数（Number of Ways to Divide a Long Corridor）
// 思路：记忆化搜索 dfs(i, k)，i 为当前下标、k 为当前隔间已有座位数（0/1/2）；k 满 2 时既可不放隔板，也可在此处放隔板并把 k 归零。
// 时间复杂度：O(n)，状态数为 3n 且每个状态 O(1) 转移；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfWays(string corridor) {  // corridor：只含 'S'（座位）与 'P'（植物）的长廊字符串
        int n = corridor.size();  // 长廊长度，也就是递归的下标上界
        int f[n][3];  // 记忆化数组：f[i][k] 存下标 i、当前隔间座位数 k 时的方案数
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示该状态还没有被计算过
        const int mod = 1e9 + 7;  // 方案数需要对 1e9+7 取模
        auto dfs = [&](this auto&& dfs, int i, int k) -> int {  // C++23 显式对象参数写法，让 lambda 能递归调用自身；i 为下标，k 为当前隔间座位数
            if (i >= n) {  // 已经处理完整个长廊
                return k == 2;  // 最后一个隔间必须恰好有 2 个座位才算一种合法方案
            }
            if (f[i][k] != -1) {  // 该状态之前算过
                return f[i][k];  // 直接返回记忆化结果，避免重复计算
            }
            k += corridor[i] == 'S';  // 若当前位置是座位，则把当前隔间的座位计数加一
            if (k > 2) {  // 一个隔间里超过 2 个座位就不合法
                return 0;  // 该分支没有任何方案
            }
            f[i][k] = dfs(i + 1, k);  // 选择不在当前位置放隔板：继续往后走，把方案数记入表中
            if (k == 2) {  // 当前隔间正好满 2 个座位，此处可以新增一块隔板
                f[i][k] = (f[i][k] + dfs(i + 1, 0)) % mod;  // 累加「放隔板」的方案，新隔间的座位计数从 0 开始
            }
            return f[i][k];  // 返回该状态的方案总数
        };
        return dfs(0, 0);  // 从下标 0、空隔间（0 个座位）开始递归求解
    }
};  // 类定义结束
