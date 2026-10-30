// 题目：3568. 清理教室的最少移动（Minimum Moves to Clean the Classroom）
// 思路：状态 BFS。状态由 (行, 列, 剩余体力, 尚未清理的垃圾掩码) 组成，从起点 S 按层向外扩展；走到 R 把体力重置为 energy，其余格子消耗 1 点体力，走到 L 则清掉对应的一位掩码，体力耗尽的状态直接丢弃；最早出现掩码为 0 的那一层就是最少移动次数。
// 时间复杂度：O(m * n * energy * 2^L)，每层每个状态扩展 4 个方向；空间复杂度：O(m * n * energy * 2^L)，即访问标记数组的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<string>& classroom, int energy) {  // classroom：教室网格；energy：初始体力；返回清理全部垃圾的最少移动次数，无法完成时返回 -1
        int m = classroom.size(), n = classroom[0].size();  // 教室的行数与列数
        vector<vector<int>> d(m, vector<int>(n, 0));  // d[i][j] 记录格子 (i,j) 上垃圾的编号，用作状态掩码的位下标
        int x = 0, y = 0, cnt = 0;  // x、y 记录起点 S 的坐标，cnt 统计垃圾堆数
        for (int i = 0; i < m; ++i) {  // 逐行扫描教室
            string& row = classroom[i];  // 引用当前行，避免反复拷贝字符串
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                char c = row[j];  // 取出当前格子的字符
                if (c == 'S') {  // 找到起点
                    x = i;  // 记录起点的行号
                    y = j;  // 记录起点的列号
                } else if (c == 'L') {  // 找到一堆垃圾
                    d[i][j] = cnt;  // 给这堆垃圾分配一个位编号
                    cnt++;  // 垃圾计数加一
                }  // 格子分类判断结束
            }  // 列扫描结束
        }  // 行扫描结束
        if (cnt == 0) {  // 教室里没有垃圾，不需要移动
            return 0;  // 直接返回 0
        }  // 特判结束
        vector<vector<vector<vector<bool>>>> vis(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(energy + 1, vector<bool>(1 << cnt, false))));  // 访问标记的四个维度依次是行、列、剩余体力、未清理垃圾掩码，避免同一状态重复入队
        queue<tuple<int, int, int, int>> q;  // BFS 队列存放 (行, 列, 剩余体力, 未清理掩码)
        q.emplace(x, y, energy, (1 << cnt) - 1);  // 起点入队，掩码全 1 表示所有垃圾都还没清理
        vis[x][y][energy][(1 << cnt) - 1] = true;  // 标记起点状态已访问
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组，相邻两项组成上下左右的行列偏移
        int ans = 0;  // 记录已经走过的步数，也就是 BFS 的层数
        while (!q.empty()) {  // 按层向外扩展，直到队列为空
            int sz = q.size();  // 当前层的状态个数
            while (sz--) {  // 逐个处理当前层的状态
                auto [i, j, cur_energy, mask] = q.front();  // 取出队首状态
                q.pop();  // 弹出队首
                if (mask == 0) {  // 掩码为 0 表示所有垃圾都已清理
                    return ans;  // 当前层数即最少移动次数
                }  // 完成判断结束
                if (cur_energy <= 0) {  // 体力已耗尽，无法再走动
                    continue;  // 丢弃该状态
                }  // 体力判断结束
                for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                    int nx = i + dirs[k], ny = j + dirs[k + 1];  // 计算相邻格子的坐标
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {  // 越界或撞上障碍物 X 都不能走
                        int nxt_energy = classroom[nx][ny] == 'R' ? energy : cur_energy - 1;  // 走到 R 体力重置为 energy，其余格子消耗 1 点
                        int nxt_mask = mask;  // 新状态的掩码先沿用当前值
                        if (classroom[nx][ny] == 'L') {  // 目标格是一堆垃圾
                            nxt_mask &= ~(1 << d[nx][ny]);  // 清掉该垃圾对应的位，表示已经清理
                        }  // 垃圾处理结束
                        if (!vis[nx][ny][nxt_energy][nxt_mask]) {  // 新状态没访问过才允许入队
                            vis[nx][ny][nxt_energy][nxt_mask] = true;  // 标记新状态已访问
                            q.emplace(nx, ny, nxt_energy, nxt_mask);  // 新状态入队
                        }  // 访问判断结束
                    }  // 合法格子判断结束
                }  // 方向循环结束
            }  // 当前层处理结束
            ans++;  // 一层扩展完，步数加一
        }  // BFS 结束
        return -1;  // 队列耗尽仍未清完，说明无法完成
    }  // 方法结束
};  // 类定义结束
