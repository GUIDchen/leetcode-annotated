// 题目：711. 不同岛屿的数量 II（Number of Distinct Islands II）
// 核心思路：DFS 取出每座岛的全部坐标，再生成 8 种旋转/镜像形态，各自平移到左上角后取字典序最小者作为规范形状，用 set 去重统计。
// 时间复杂度：O(m·n·log(m·n))，每个格子访问一次、每座岛做 8 次排序；空间复杂度：O(m·n)，递归栈与形状集合。
typedef pair<int, int> PII;  // 用 PII 简写坐标对 (行, 列)，后面大量使用，省去写 pair<int, int>

class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的接口区
    int numDistinctIslands2(vector<vector<int>>& grid) {  // grid 中 1 表示陆地，返回本质不同的岛屿形状数量
        set<vector<PII>> s;  // 存放每座岛的规范形状；set 自动去重并保持有序
        for (int i = 0; i < grid.size(); ++i) {  // 逐行扫描网格
            for (int j = 0; j < grid[0].size(); ++j) {  // 逐列扫描网格
                if (grid[i][j]) {  // 找到一块尚未访问的陆地，作为新岛屿的起点
                    vector<PII> shape;  // 收集这座岛所有格子的坐标
                    dfs(i, j, grid, shape);  // 洪泛填充整座岛，同时把访问过的陆地置 0 防止重复访问
                    s.insert(normalize(shape));  // 计算规范形状后插入集合，同一形状只会保留一份
                }  // 结束 if 分支
            }  // 结束内层列循环
        }  // 结束外层行循环
        return s.size();  // 集合大小即不同岛屿的数量
    }  // 结束 numDistinctIslands2 方法

    vector<PII> normalize(vector<PII>& shape) {  // 把一座岛的坐标列表转换成 8 种对称形态下的字典序最小表示
        vector<vector<PII>> shapes(8);  // shapes[k] 保存第 k 种变换（旋转/镜像）后的坐标列表
        for (auto& e : shape) {  // 遍历岛上的每个格子
            int i = e.first, j = e.second;  // 拆出行坐标 i 与列坐标 j
            shapes[0].push_back({i, j});  // 原样，即旋转 0°
            shapes[1].push_back({i, -j});  // 沿列方向镜像
            shapes[2].push_back({-i, j});  // 沿行方向镜像
            shapes[3].push_back({-i, -j});  // 旋转 180°
            shapes[4].push_back({j, i});  // 主对角线翻转（行列互换）
            shapes[5].push_back({j, -i});  // 旋转 90°
            shapes[6].push_back({-j, -i});  // 副对角线翻转
            shapes[7].push_back({-j, i});  // 旋转 270°（即 -90°）
        }  // 8 种对称形态已收集完毕
        for (auto& e : shapes) {  // 对每一种形态分别做平移规范化
            sort(e.begin(), e.end());  // 先按 (行, 列) 排序，得到与遍历起点无关的序列
            for (int k = e.size() - 1; k >= 0; --k) {  // 倒序平移，避免先改掉作为基准的 e[0]
                e[k].first -= e[0].first;  // 行坐标减去最小行坐标，把形状整体移到第 0 行
                e[k].second -= e[0].second;  // 列坐标减去最小列坐标，把形状整体移到第 0 列
            }  // 结束平移循环
        }  // 结束 8 种形态的规范化循环
        sort(shapes.begin(), shapes.end());  // 8 种形态之间按字典序排序
        return shapes[0];  // 取字典序最小的形态作为该岛的规范形状，形状等价的岛会得到同一结果
    }  // 结束 normalize 方法

    void dfs(int i, int j, vector<vector<int>>& grid, vector<PII>& shape) {  // 从 (i, j) 出发，用深度优先搜索收集整座岛的坐标
        shape.push_back({i, j});  // 记录当前陆地格子（此时尚未标记，坐标是原值）
        grid[i][j] = 0;  // 置 0 表示已访问，避免同一格子被重复收集
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成一个方向，依次是上、下、左、右
        for (int k = 0; k < 4; ++k) {  // 枚举四个方向
            int x = i + dirs[k], y = j + dirs[k + 1];  // 计算邻居坐标 x、y
            if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 1)  // 邻居在界内且是未访问的陆地，才继续搜索
                dfs(x, y, grid, shape);  // 递归洪泛，把相连的陆地全部并入当前岛屿
        }  // 结束方向循环
    }  // 结束 dfs 方法
};  // 结束 Solution 类定义