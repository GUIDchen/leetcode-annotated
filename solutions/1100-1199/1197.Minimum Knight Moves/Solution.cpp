// 题目：1197. 进击的骑士（Minimum Knight Moves）
// 思路：从原点出发做 BFS，八种马步逐层向外扩展，按层数统计到达目标的最少步数。
// 时间复杂度：O(V + E)，V、E 为扩展到的棋盘点数与边数；空间复杂度：O(V)，最多 700×700 的访问表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minKnightMoves(int x, int y) {  // x、y 是目标坐标（可能为负），返回骑士从 (0,0) 到 (x,y) 的最少步数
        x += 310;  // 整体平移 310，把可能为负的坐标搬进非负数组下标范围
        y += 310;  // y 同样平移 310
        int ans = 0;  // ans 记录当前 BFS 的层数，也就是已经走过的步数
        queue<pair<int, int>> q;  // BFS 队列，存放待扩展的坐标点
        q.push({310, 310});  // 起点（平移后的原点）入队
        vector<vector<bool>> vis(700, vector<bool>(700));  // vis 标记点是否访问过，700×700 足以覆盖平移后的坐标范围
        vis[310][310] = true;  // 起点标记为已访问，避免绕回原点重复入队
        vector<vector<int>> dirs = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};  // 骑士的八种 L 形走法
        while (!q.empty()) {  // 队列非空说明还有同层或下一层的点待处理
            for (int k = q.size(); k > 0; --k) {  // 按当前队列长度分层遍历，保证同一层的点步数相同
                auto p = q.front();  // 取出队首元素
                q.pop();  // 弹出队首，此时 p 正是要扩展的点
                if (p.first == x && p.second == y) return ans;  // 出队时判断是否到达目标，此时的 ans 就是最少步数
                for (auto& dir : dirs) {  // 枚举八个方向，各试走一步
                    int c = p.first + dir[0], d = p.second + dir[1];  // c、d 是走这一步之后的新坐标
                    if (!vis[c][d]) {  // 新坐标没访问过才继续扩展，避免重复入队
                        vis[c][d] = true;  // 标记为已访问，同样起去重作用
                        q.push({c, d});  // 新坐标入队，留到下一层扩展
                    }
                }
            }
            ++ans;  // 本层扫完，步数加一
        }
        return -1;  // 理论上不会走到这里；返回 -1 表示不可达
    }
};