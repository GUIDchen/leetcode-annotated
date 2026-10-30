// 题目：2061. 扫地机器人清扫过的空间个数（Number of Spaces Cleaning Robot Cleaned）
// 思路：DFS 模拟机器人移动，状态为（行, 列, 朝向）；能前进就前进，否则原地右转，状态重复出现即停止。
// 时间复杂度：O(mn)，每个格子只有 4 种朝向状态；空间复杂度：O(mn)，vis 三维数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfCleanRooms(vector<vector<int>>& room) {  // room：房间格子，0 为空地、1 为家具、-1 为已清扫
        int m = room.size(), n = room[0].size();  // 行数 m 与列数 n
        bool vis[m][n][4];  // vis[i][j][k]：是否以朝向 k 到达过格子 (i, j)
        memset(vis, false, sizeof(vis));  // 全部初始化为未访问
        int dirs[5] = {0, 1, 0, -1, 0};  // 方向增量：右、下、左、上；成对使用 dirs[k] 与 dirs[k+1]
        int ans = 0;  // 累计清扫过的不同格子数
        function<void(int, int, int)> dfs = [&](int i, int j, int k) {  // i、j：当前位置；k：当前朝向
            if (vis[i][j][k]) {  // 同一位置同一朝向重复出现，说明已经进入循环
                return;  // 直接结束，避免无限递归
            }
            ans += room[i][j] == 0;  // 只有当格子还是 0（尚未清扫）时才计数
            room[i][j] = -1;  // 标记该格子已清扫，后续再经过也不会重复计数
            vis[i][j][k] = true;  // 记录「曾以朝向 k 到达 (i, j)」
            int x = i + dirs[k], y = j + dirs[k + 1];  // 按当前朝向算出下一格的坐标
            if (x >= 0 && x < m && y >= 0 && y < n && room[x][y] != 1) {  // 下一格在房间内且不是家具
                dfs(x, y, k);  // 可以前进，朝向保持不变
            } else {  // 前方越界、是墙或是家具
                dfs(i, j, (k + 1) % 4);  // 原地顺时针右转 90 度：朝向 0→1→2→3→0
            }
        };
        dfs(0, 0, 0);  // 从左上角、朝右的方向开始清扫
        return ans;  // 返回清扫过的格子总数
    }
};