// 题目：1467. 两个盒子中球的颜色数相同的概率（Probability of a Two Boxes Having The Same Number of Distinct Balls）
// 核心思路：组合数 + 记忆化搜索。按颜色逐个决定放几个球进第一个盒子，同时维护还需放的球数 j 与「颜色数差」diff，合法方案数除以总分配数 C(2n, n) 即为概率。
// 时间复杂度：O(k·n·k·maxBall)，状态数 k×n×2k，每个状态枚举该颜色的分配个数；空间复杂度：O(k·n·k + m^2)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double getProbability(vector<int>& balls) {  // balls[i] 是第 i 种颜色的球数，返回值是颜色数相同的概率
        int n = accumulate(balls.begin(), balls.end(), 0) / 2;  // 球总数的一半，即每个盒子要装的球数 n
        int mx = *max_element(balls.begin(), balls.end());  // 单种颜色的最多球数，作为组合数表规模的下界之一
        int m = max(mx, n << 1);  // 组合数表规模取 max(最大单色球数, 总球数 2n)，保证 C(balls[i], x) 与 C(2n, n) 都够用
        long long c[m + 1][m + 1];  // 帕斯卡三角形：c[i][j] 表示组合数 C(i, j)
        memset(c, 0, sizeof(c));  // 全部清零，后面只需填下三角
        for (int i = 0; i <= m; ++i) {  // 逐行递推组合数
            c[i][0] = 1;  // C(i, 0) = 1
            for (int j = 1; j <= i; ++j) {  // 只计算 j ≤ i 的有效部分
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];  // 帕斯卡恒等式：C(i, j) = C(i-1, j-1) + C(i-1, j)
            }  // 内层循环结束
        }  // 组合数表构造完成
        int k = balls.size();  // 颜色种数 k，同时用 k 作为颜色数差的下标偏移量
        long long f[k][n + 1][k << 1 | 1];  // 记忆化数组：状态 (已处理颜色数, 第一个盒子还差的球数, 颜色数差 + k)
        memset(f, -1, sizeof(f));  // memset 按字节填 -1，表示该状态尚未计算
        function<long long(int, int, int)> dfs = [&](int i, int j, int diff) -> long long {  // dfs 返回：从第 i 种颜色开始分配、还需 j 个球、颜色数差为 diff-k 时的合法方案数
            if (i >= k) {  // 所有颜色都已分配完
                return j == 0 && diff == k ? 1 : 0;  // 只有球数刚好用完且颜色数差为 0（diff == k）才是一种合法方案
            }  // 递归出口结束
            if (j < 0) {  // 第一个盒子已经超过 n 个球，非法
                return 0;  // 该分支无解
            }  // 提前剪枝结束
            if (f[i][j][diff] != -1) {  // 命中记忆化
                return f[i][j][diff];  // 直接返回缓存值
            }  // 缓存判断结束
            long long ans = 0;  // 累加当前状态的方案数
            for (int x = 0; x <= balls[i]; ++x) {  // 枚举第 i 种颜色往第一个盒子里放 x 个球
                int y = x == balls[i] ? 1 : (x == 0 ? -1 : 0);  // 该颜色是否只出现在一个盒子：全放 A 记 +1，全放 B 记 -1，两边都有记 0
                ans += dfs(i + 1, j - x, diff + y) * c[balls[i]][x];  // 子问题方案数乘以该颜色的选择数 C(balls[i], x)
            }  // 枚举结束
            return f[i][j][diff] = ans;  // 先写回缓存再返回
        };  // lambda 定义结束
        return dfs(0, n, k) * 1.0 / c[n << 1][n];  // 合法方案数 / 总分配数 C(2n, n)；初始 diff 传 k 表示颜色数差为 0
    }  // 方法结束
};  // 类定义结束