// 题目：1765. 地图中的最高点（Map of Highest Peak）
// 思路：多源 BFS。把所有水域格子当作源点入队并令其高度为 0，再一层层向外扩散，每扩散一层高度加 1；这样既能保证相邻格子高度差不超过 1，又能让高度尽可能大。
// 时间复杂度：O(m * n)，每个格子最多入队一次；空间复杂度：O(m * n)，答案矩阵与 BFS 队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int dirs[5] = {-1, 0, 1, 0, -1};  // 四个方向的偏移量：dirs[k] 与 dirs[k+1] 拼成一个方向向量，多留一位避免 k+1 越界

    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {  // isWater：1 表示水域、0 表示陆地；返回每个格子的最高高度
        int m = isWater.size(), n = isWater[0].size();  // m 是行数，n 是列数
        vector<vector<int>> ans(m, vector<int>(n));  // 答案矩阵，先只分配空间，具体高度在下面填
        queue<pair<int, int>> q;  // BFS 队列，存放已经确定高度的格子坐标
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举每一列
                ans[i][j] = isWater[i][j] - 1;  // 水域（1）变成 0，陆地（0）变成 -1 表示高度尚未确定
                if (ans[i][j] == 0) {  // 高度为 0 说明该格子是水域，作为多源 BFS 的源点
                    q.emplace(i, j);  // 把水域坐标入队
                }
            }
        }
        while (!q.empty()) {  // 队列非空就继续按层向外扩散
            auto [i, j] = q.front();  // 取出队首格子，结构化绑定得到行 i 与列 j
            q.pop();  // 弹出队首，避免重复处理
            for (int k = 0; k < 4; ++k) {  // 枚举上下左右四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 算出相邻格子的坐标 x、y
                if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {  // 越界或该格子已经确定过高度（不等于 -1）就跳过
                    ans[x][y] = ans[i][j] + 1;  // 相邻格子高度 = 当前高度 + 1，既满足差值不超过 1 又取到最大
                    q.emplace(x, y);  // 新确定的格子入队，继续向外扩散
                }
            }
        }  // 所有可达格子都处理完毕
        return ans;  // 返回每个格子的最高高度
    }  // 方法结束
};  // 类定义结束