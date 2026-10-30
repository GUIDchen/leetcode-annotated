// 题目：1039. 多边形三角剖分的最低得分（Minimum Score Triangulation of Polygon）
// 思路：区间 DP 记忆化搜索，枚举边 (i, j) 对应的三角形第三个顶点 k，把多边形分成两个子区间递归求解，答案为各三角形顶点乘积之和的最小值。
// 时间复杂度：O(n^3)，共 O(n^2) 个区间、每个区间枚举 O(n) 个 k；空间复杂度：O(n^2)，记忆化数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minScoreTriangulation(vector<int>& values) {  // values 是多边形各顶点的值（按顺/逆时针排列），返回最低三角剖分得分
        int n = values.size();  // 多边形顶点个数 n
        vector<vector<int>> f(n, vector<int>(n));  // 记忆化数组 f[i][j]：区间 [i, j] 构成的多边形的最低得分，0 表示还没算过
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 泛型递归 lambda：求下标 i 到 j 这一段多边形的最低得分
            if (i + 1 == j) {  // 只剩一条边（i 与 j 相邻），无法再剖分出三角形
                return 0;  // 此时没有三角形产生，得分为 0
            }  // 边界判断结束
            if (f[i][j]) {  // 该区间已经计算过（非 0 即为已缓存）
                return f[i][j];  // 直接返回缓存值，避免重复计算
            }  // 缓存命中分支结束
            int ans = 1 << 30;  // 答案初值取一个足够大的数 2^30
            for (int k = i + 1; k < j; ++k) {  // 枚举 i 与 j 之间的分割点 k，即三角形 (i, k, j) 的第三个顶点
                ans = min(ans, dfs(i, k) + dfs(k, j) + values[i] * values[k] * values[j]);  // 取「子区间 i..k 的得分 + 子区间 k..j 的得分 + 本次三角形的乘积」的最小值
            }  // 枚举分割点结束
            return f[i][j] = ans;  // 把答案写入记忆化数组，再一并作为返回值
        };  // 递归 lambda 结束
        return dfs(0, n - 1);  // 从整个多边形的首尾下标开始递归求解
    }  // 方法结束
};  // 类结束
