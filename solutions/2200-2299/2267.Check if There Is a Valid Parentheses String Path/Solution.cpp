// 题目：2267. 检查是否有合法括号字符串路径（Check if There Is a Valid Parentheses String Path）
// 思路：DFS 加记忆化。状态 (i, j, k) 表示走到 (i, j) 时的净左括号数 k；要求 k 始终非负且不超过剩余格子数（剪枝），到达终点时 k == 0 才算合法路径。
// 时间复杂度：O(m * n * (m + n))，即状态总数（记忆化保证每个状态只搜一次）；空间复杂度：O(m * n * (m + n))，用于 vis 数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool hasValidPath(vector<vector<char>>& grid) {  // grid：由 '(' 与 ')' 组成的网格
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        if ((m + n - 1) % 2 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {  // 路径长度必须为偶数；起点不能是 ')'；终点不能是 '('
            return false;  // 任一前提不满足，直接判定不存在合法路径
        }
        bool vis[m][n][m + n];  // 记忆化数组：vis[i][j][k] 表示状态 (i, j, k) 是否已被搜索过
        memset(vis, false, sizeof(vis));  // 全部初始化为「未访问」
        int dirs[3] = {1, 0, 1};  // 两个移动增量 (1,0) 向下、(0,1) 向右，共用一个数组便于循环取值
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> bool {  // 递归 lambda：C++23 显式对象参数实现自引用；k 是进入 (i, j) 之前累计的净左括号数
            if (vis[i][j][k]) {  // 该状态此前已搜过且没有走通
                return false;  // 直接剪枝，避免重复搜索
            }
            vis[i][j][k] = true;  // 标记该状态已访问
            k += grid[i][j] == '(' ? 1 : -1;  // 把当前格子的括号计入净左括号数
            if (k < 0 || k > m - i + n - j) {  // 净数不能为负；也不能超过剩余格子数，否则后面无法回到 0
                return false;  // 剪枝：该分支一定凑不出合法括号串
            }
            if (i == m - 1 && j == n - 1) {  // 已经到达右下角终点
                return k == 0;  // 净数为 0 说明括号恰好完全匹配
            }
            for (int d = 0; d < 2; ++d) {  // 依次尝试向下与向右两个方向
                int x = i + dirs[d], y = j + dirs[d + 1];  // 计算下一个格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && dfs(x, y, k)) {  // 坐标在界内，且该方向能找到合法路径
                    return true;  // 只要存在一条合法路径就立即返回成功
                }
            }
            return false;  // 两个方向都走不通，本状态失败
        };
        return dfs(0, 0, 0);  // 从左上角出发，初始净左括号数为 0
    }
};
