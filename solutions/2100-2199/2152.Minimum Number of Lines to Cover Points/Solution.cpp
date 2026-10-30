// 题目：2152. 穿过所有点的所需最少直线数量（Minimum Number of Lines to Cover Points）
// 思路：状压 DP —— state 记录已被直线覆盖的点；每次取第一个未覆盖点 i，与另一个未覆盖点 j 确定直线并吞掉同线点，记忆化搜索最少直线数。
// 时间复杂度：O(2^n · n^3)，状态数乘以每次枚举的组合数；空间复杂度：O(2^n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumLines(vector<vector<int>>& points) {  // points：所有点的坐标；返回覆盖全部点所需的最少直线数
        auto check = [&](int i, int j, int k) {  // 判断编号 i、j、k 的三个点是否共线
            int x1 = points[i][0], y1 = points[i][1];  // 取出第 i 个点的坐标
            int x2 = points[j][0], y2 = points[j][1];  // 取出第 j 个点的坐标
            int x3 = points[k][0], y3 = points[k][1];  // 取出第 k 个点的坐标
            return (x2 - x1) * (y3 - y1) == (x3 - x1) * (y2 - y1);  // 叉积为 0 即共线，用整数乘法避免浮点误差
        };  // 共线判断 lambda 结束
        int n = points.size();  // 点的个数 n
        int f[1 << n];  // 记忆化数组：f[state] 表示在已覆盖 state 这些点的前提下还需的最少直线数
        memset(f, 0, sizeof f);  // 全部清零，0 作为「该状态尚未计算」的哨兵
        function<int(int)> dfs = [&](int state) -> int {  // 记忆化搜索：state 的每一位标记对应点是否已被某条直线覆盖
            if (state == (1 << n) - 1) return 0;  // 所有点都已覆盖，不需要再加直线
            if (f[state]) return f[state];  // 该状态算过，直接返回缓存值
            int ans = 1 << 30;  // 当前最优解，先置为足够大的数
            for (int i = 0; i < n; ++i) {  // 找第一个尚未被覆盖的点 i
                if (!(state >> i & 1)) {  // 第 i 位为 0，说明点 i 还没被覆盖
                    for (int j = i + 1; j < n; ++j) {  // 再找一个未覆盖的点 j，与 i 一起确定一条直线
                        int nxt = state | 1 << i | 1 << j;  // 新状态：把 i、j 标记为已覆盖
                        for (int k = j + 1; k < n; ++k) {  // 检查后面的点 k 是否也落在这条直线上
                            if (!(nxt >> k & 1) && check(i, j, k)) {  // k 尚未覆盖且与 i、j 共线，可以顺带覆盖
                                nxt |= 1 << k;  // 把 k 也标记为已覆盖
                            }  // 结束 k 的 if 判断
                        }  // 结束对 k 的循环
                        ans = min(ans, dfs(nxt) + 1);  // 用一条直线覆盖 i、j 及同线点，再递归求剩余部分，取最小值
                    }  // 结束对 j 的循环
                    if (i == n - 1) {  // 只剩最后一个未覆盖点，无法再找更大的 j 配对
                        ans = min(ans, dfs(state | 1 << i) + 1);  // 单独用一条直线覆盖它
                    }  // 结束 i == n-1 的分支
                }  // 结束「点 i 未覆盖」的分支
            }  // 结束对 i 的循环
            return f[state] = ans;  // 记忆化保存并返回该状态的最优解
        };  // 递归 lambda 定义结束
        return dfs(0);  // 从「一个点都没覆盖」的状态开始搜索
    }  // 结束方法
};  // 结束题解类