// 题目：2556. 二进制矩阵中翻转最多一次使路径不连通（Disconnect Path in a Binary Matrix by at Most One Flip）
// 思路：DFS 把走过的格子置 0。第一次搜索判断起点到终点是否本来连通，并清空它走过的一条路径；恢复起点和终点后再搜第二次，若仍连通说明至少有两条内部不相交的路径，无法一刀切断。
// 时间复杂度：O(mn)，两次 DFS 每个格子最多访问一次；空间复杂度：O(mn)，递归栈最坏深度为 m + n。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPossibleToCutPath(vector<vector<int>>& grid) {  // grid 中 1 表示可走，问能否只翻一个格子就切断所有路径
        int m = grid.size(), n = grid[0].size();  // 记录矩阵的行数 m 和列数 n
        function<bool(int, int)> dfs = [&](int i, int j) -> bool {  // 递归找一条从 (0,0) 到 (m-1,n-1) 的路径；顺路把走过的格子置 0，避免重复访问
            if (i >= m || j >= n || grid[i][j] == 0) {  // 越界或当前格子不可走（被访问过也算不可走）
                return false;  // 这条路走不通
            }  // 非法格子判断结束
            if (i == m - 1 && j == n - 1) {  // 走到终点
                return true;  // 说明找到了一条路径
            }  // 终点判断结束
            grid[i][j] = 0;  // 标记当前格子已访问，防止来回绕圈
            return dfs(i + 1, j) || dfs(i, j + 1);  // 只能往右或往下走，任一方向能到终点即可
        };  // lambda 定义结束
        bool a = dfs(0, 0);  // 第一次搜索：判断起点到终点是否本来就连通
        grid[0][0] = grid[m - 1][n - 1] = 1;  // DFS 会把起点和终点也置 0，这里先恢复，才能进行第二次搜索
        bool b = dfs(0, 0);  // 第二次搜索：第一次的路径已被清空，若还能连通说明存在第二条不相交路径
        return !(a && b);  // 两次都连通 => 不存在可以切断所有路径的必经点，返回 false
    }  // isPossibleToCutPath 方法结束
};  // Solution 类定义结束
