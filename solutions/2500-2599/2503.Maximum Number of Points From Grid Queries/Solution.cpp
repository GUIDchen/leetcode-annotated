// 题目：2503. 矩阵查询可获得的最大分数（Maximum Number of Points From Grid Queries）
// 思路：把查询按值升序排序，用小根堆从 (0,0) 开始按格子值递增“解锁”格子，堆顶值小于当前查询值就出堆计分；查询递增处理，cnt 只增不减。
// 时间复杂度：O(m·n log(m·n) + k log k)，每个格子最多入堆出堆一次；空间复杂度：O(m·n + k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成一个方向的 (dx, dy)，写 5 个元素便于同时取 h 与 h+1

    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {  // grid：矩阵；queries：查询数组；返回每个查询对应的最大分数
        int k = queries.size();  // k：查询个数
        vector<pair<int, int>> qs(k);  // qs：把 (查询值, 原下标) 打包，便于排序后仍能放回原位置
        for (int i = 0; i < k; ++i) qs[i] = {queries[i], i};  // 填入查询值与其原始下标
        sort(qs.begin(), qs.end());  // 按查询值升序排序，使每个格子只需被处理一次
        vector<int> ans(k);  // ans：按查询的原始下标保存答案
        int m = grid.size(), n = grid[0].size();  // 矩阵的行数 m 与列数 n
        bool vis[m][n];  // vis：标记格子是否已经入堆（访问过）；变长数组是 g++/clang 的扩展
        memset(vis, 0, sizeof vis);  // 初始化为未访问
        vis[0][0] = true;  // 起点 (0, 0) 标记为已访问
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;  // 小根堆：元素为 (格子值, 行, 列)，按格子值从小到大出堆
        q.push({grid[0][0], 0, 0});  // 起点入堆，等待被某个查询“解锁”
        int cnt = 0;  // cnt：当前查询值下能到达并计分的格子数
        for (auto& e : qs) {  // 按查询值从小到大依次处理
            int v = e.first;  // v：当前查询值
            k = e.second;  // k：该查询的原始下标，答案要放回这个位置
            while (!q.empty() && get<0>(q.top()) < v) {  // 堆顶格子的值严格小于 v 时，该格子才可以被走到
                auto [_, i, j] = q.top();  // 取出堆顶的 (格子值, 行, 列)，格子值用 _ 忽略
                q.pop();  // 弹出堆顶
                ++cnt;  // 该格子计入分数
                for (int h = 0; h < 4; ++h) {  // 枚举四个相邻方向
                    int x = i + dirs[h], y = j + dirs[h + 1];  // 算出相邻格子的行列坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y]) {  // 坐标合法且未被访问过
                        vis[x][y] = true;  // 入堆前就标记已访问，避免同一格子被重复入堆
                        q.push({grid[x][y], x, y});  // 把相邻格子加入小根堆，等待后续查询处理
                    }  // 相邻格子判断结束
                }  // 方向枚举结束
            }  // 当前查询能解锁的格子全部处理完
            ans[k] = cnt;  // 把当前累计的格子数作为该查询的答案
        }  // 查询循环结束
        return ans;  // 返回按原始下标排列的答案
    }  // 方法结束
};  // 类定义结束