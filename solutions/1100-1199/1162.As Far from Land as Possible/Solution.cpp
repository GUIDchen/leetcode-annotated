// 题目：1162. 地图分析（As Far from Land as Possible）
// 思路：多源 BFS，把所有陆地同时作为起点向外扩展，最后一层的层数即最远海洋格的曼哈顿距离。
// 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，队列与地图同阶。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int maxDistance(vector<vector<int>>& grid) {  // grid 中 1 是陆地、0 是海洋，求离陆地最远的海洋格到最近陆地的距离
        int n = grid.size();  // 方阵边长
        queue<pair<int, int>> q;  // BFS 队列，存放待扩展的陆地坐标
        for (int i = 0; i < n; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                if (grid[i][j]) {  // 该格是陆地
                    q.emplace(i, j);  // 陆地作为多源 BFS 的起点入队
                }  // 结束陆地判断
            }  // 结束列遍历
        }  // 结束行遍历
        int ans = -1;  // 距离答案，全陆地或全海洋时保持 -1
        if (q.empty() || q.size() == n * n) {  // 没有陆地或全是陆地，都不存在海洋格
            return ans;  // 直接返回 -1
        }  // 结束特判
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四邻方向首尾闭合，便于取相邻两个数组成一组偏移
        while (!q.empty()) {  // 逐层向外扩展
            for (int m = q.size(); m; --m) {  // 固定当前层的节点数
                auto [i, j] = q.front();  // 取出队首坐标（结构化绑定）
                q.pop();  // 弹出队首
                for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居坐标
                    if (x >= 0 && x < n && y >= 0 && y < n && !grid[x][y]) {  // 邻居在界内且是尚未访问的海洋格
                        grid[x][y] = 1;  // 标记为已到达，其距离已确定
                        q.emplace(x, y);  // 入队，下一层继续扩展
                    }  // 结束合法邻居判断
                }  // 结束方向枚举
            }  // 结束当前层处理
            ++ans;  // 每扩展一层，距离加一
        }  // 结束 BFS
        return ans;  // 返回最远海洋格到最近陆地的距离
    }  // 方法结束
};  // 类定义结束