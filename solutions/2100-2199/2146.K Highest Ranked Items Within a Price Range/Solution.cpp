// 题目：2146. 价格范围内最高排名的 K 样物品（K Highest Ranked Items Within a Price Range）
// 思路：从起点做 BFS 求出每个可走格子的最短距离，把价格在区间内的格子记为 (距离, 价格, 行, 列) 四元组，再排序取前 k 个。
// 时间复杂度：O(mn log(mn))，BFS 为 O(mn)、排序为 O(mn log(mn))；空间复杂度：O(mn)，队列与候选列表最坏存下全部格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {  // grid：价格网格；pricing：价格区间；start：起点；k：取前几名
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        int row = start[0], col = start[1];  // 拆出 BFS 起点的行、列坐标
        int low = pricing[0], high = pricing[1];  // 拆出允许的价格区间 [low, high]
        queue<pair<int, int>> q;  // BFS 队列，存放待扩展的格子坐标
        q.push({row, col});  // 起点先入队
        vector<tuple<int, int, int, int>> pq;  // 候选物品容器：{距离, 价格, 行, 列}
        if (low <= grid[row][col] && grid[row][col] <= high) {  // 起点本身若价格在区间内，它也是候选物品
            pq.push_back({0, grid[row][col], row, col});  // 起点物品的距离为 0
        }
        grid[row][col] = 0;  // 把已访问的格子改成 0（相当于墙），防止重复入队
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移表：(dirs[j], dirs[j+1]) 依次为上、右、下、左
        for (int step = 1; q.size(); ++step) {  // 逐层 BFS，step 就是当前这一层的距离
            int sz = q.size();  // 先固定本层节点数，内层循环才不会被新入队元素影响
            for (int i = 0; i < sz; ++i) {  // 依次处理本层的每个格子
                auto [x, y] = q.front();  // 用 C++17 结构化绑定取出队首坐标
                q.pop();  // 队首出队
                for (int j = 0; j < 4; ++j) {  // 枚举四个相邻方向
                    int nx = x + dirs[j];  // 相邻格子的行坐标
                    int ny = y + dirs[j + 1];  // 相邻格子的列坐标
                    if (0 <= nx && nx < m && 0 <= ny && ny < n && grid[nx][ny] > 0) {  // 未越界且该格可走（价格 > 0 表示不是墙）
                        if (low <= grid[nx][ny] && grid[nx][ny] <= high) {  // 该格价格落在区间内，可作为候选物品
                            pq.push_back({step, grid[nx][ny], nx, ny});  // 记录距离、价格与坐标，供最后排序
                        }
                        grid[nx][ny] = 0;  // 标记为已访问，避免重复扩展
                        q.push({nx, ny});  // 入队，等待下一层继续扩展
                    }
                }
            }
        }
        sort(pq.begin(), pq.end());  // 按元组字典序排序：距离 → 价格 → 行 → 列
        vector<vector<int>> ans;  // 最终答案：前 k 个物品的坐标
        for (int i = 0; i < min(k, (int) pq.size()); ++i) {  // 最多取 k 个，且不能超过候选总数
            ans.push_back({get<2>(pq[i]), get<3>(pq[i])});  // 从四元组里取出行、列，作为该物品的坐标
        }
        return ans;  // 返回排名最高的 k 个物品坐标
    }
};  // 类定义结束
