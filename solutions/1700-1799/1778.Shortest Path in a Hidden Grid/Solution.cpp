// 题目：1778. 未知网格中的最短路径（Shortest Path in a Hidden Grid）
// 思路：先用 DFS 在隐藏网格上探索，记录所有可走格子与目标位置；再用 BFS 从起点出发求到目标的最短步数。
// 时间复杂度：O(S)，S 为探索到的可达格子数；空间复杂度：O(S) 用于存访问集合与队列。
/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

class Solution {  // LeetCode 约定的题解类
private:  // 私有成员：坐标编码所需的常量与探索状态
    const int n = 2010;  // 把二维坐标压成一维时使用的进制（取值足够大，保证编码不冲突）
    int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的坐标增量：上、右、下、左
    string s = "URDL";  // 与 dirs 一一对应的方向字符
    int target;  // 目标格子的一维编码
    unordered_set<int> vis;  // 已访问（可通行）格子的一维编码集合

public:  // 题解方法对外可见
    int findShortestPath(GridMaster& master) {  // master：隐藏网格的交互接口
        target = n * n;  // 用一个不可能出现的编码表示“尚未找到目标”
        vis.insert(0);  // 起点 (0,0) 的编码为 0，先标记为已访问
        dfs(0, 0, master);  // 第一次 DFS：探索整个可达区域并记录目标位置
        if (target == n * n) {  // 没有找到目标
            return -1;  // 返回 -1
        }
        vis.erase(0);  // 移除起点，之后把集合当作 BFS 的“未访问”标记使用
        queue<pair<int, int>> q;  // BFS 用的队列
        q.emplace(0, 0);  // 起点入队
        for (int ans = 0; q.size(); ++ans) {  // ans 记录当前层已经走过的步数
            for (int m = q.size(); m; --m) {  // 逐层扩展：只处理当前层的 m 个格子
                auto [i, j] = q.front();  // 取出队首坐标（结构化绑定）
                q.pop();  // 队首出队
                if (i * n + j == target) {  // 到达目标
                    return ans;  // 返回步数，分层 BFS 保证这是最短距离
                }
                for (int k = 0; k < 4; ++k) {  // 尝试四个方向
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居坐标
                    if (vis.count(x * n + y)) {  // 邻居可通行且尚未访问（仍在集合中）
                        vis.erase(x * n + y);  // 标记为已访问
                        q.emplace(x, y);  // 邻居入队
                    }
                }
            }
        }
        return -1;  // 队列空了仍未到达目标
    }

    void dfs(int i, int j, GridMaster& master) {  // 在未知网格上做 DFS 探索：i、j 是当前坐标
        if (master.isTarget()) {  // 当前格子就是目标
            target = i * n + j;  // 记录目标的一维编码
        }
        for (int k = 0; k < 4; ++k) {  // 尝试四个方向
            int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居坐标
            if (master.canMove(s[k]) && !vis.count(x * n + y)) {  // 能走过去且没有访问过
                vis.insert(x * n + y);  // 标记该邻居为已访问
                master.move(s[k]);  // 真的把角色移动到邻居格子
                dfs(x, y, master);  // 继续深入探索
                master.move(s[(k + 2) % 4]);  // 回溯：沿反方向走回当前格子
            }
        }
    }
};  // 类定义结束