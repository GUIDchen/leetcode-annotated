// 题目：2017. 网格游戏（Grid Game）
// 思路：枚举机器人一在第一行第 j 列向下拐弯；此后机器人二只能走第一行 j 右侧或第二行 j 左侧，必然选剩余和更大的一侧，答案即所有 j 中该最大值的最小值。
// 时间复杂度：O(n)，只需一次线性扫描；空间复杂度：O(1)，仅用了常数个变量。
using ll = long long;  // 类型别名，后续 ll 等价于 long long，避免反复书写

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long gridGame(vector<vector<int>>& grid) {  // grid：2 行 n 列的网格，返回机器人二在最优策略下最多能拿走的分数
        ll ans = LONG_MAX;  // 答案初始化为 long long 的最大值，保证第一次比较一定被更新
        int n = grid[0].size();  // n 是网格列数，两行长度相同
        ll s1 = 0, s2 = 0;  // s1 维护第一行的剩余后缀和，s2 维护第二行已走过部分的前缀和
        for (int& v : grid[0]) s1 += v;  // 先把第一行全部元素累加进 s1，作为 j = 0 时的初始状态
        for (int j = 0; j < n; ++j) {  // 枚举机器人一在第一行向下拐弯的列 j
            s1 -= grid[0][j];  // 机器人一取走 (0, j)，s1 变成第一行 j 之后的后缀和
            ans = min(ans, max(s1, s2));  // 机器人二必选剩余和更大的一侧，先取 max 再与 ans 取 min
            s2 += grid[1][j];  // (1, j) 已被机器人一拿走，把它并入第二行前缀和供下一列使用
        }  // 列枚举结束
        return ans;  // 返回所有拐弯列里「机器人二最大得分」的最小值
    }  // gridGame 方法结束
};  // Solution 类定义结束