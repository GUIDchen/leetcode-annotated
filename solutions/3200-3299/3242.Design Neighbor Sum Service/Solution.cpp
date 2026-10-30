// 题目：3242. 设计相邻元素求和服务（Design Neighbor Sum Service）
// 思路：构造时建立「值 → 坐标」的哈希表，查询时在方向表上取四个偏移，判断不越界后累加对应格子的值。
// 时间复杂度：构造 O(m × n)，单次查询 O(1)；空间复杂度：O(m × n)，保存矩阵副本与坐标表。
class NeighborSum {  // 设计题：按 value 查询相邻格与对角格之和
public:  // 构造函数与两个查询方法对外可见
    NeighborSum(vector<vector<int>>& grid) {  // 构造时就建立索引，后续查询不必再扫描矩阵
        this->grid = grid;  // 保存矩阵副本，查询时按坐标取值
        int m = grid.size(), n = grid[0].size();  // m 行数，n 列数
        for (int i = 0; i < m; ++i) {  // 逐行
            for (int j = 0; j < n; ++j) {  // 逐列
                d[grid[i][j]] = {i, j};  // 记录每个值所在的坐标（题目保证矩阵中的值互不相同）
            }  // 内层 for 结束
        }  // 外层 for 结束
    }  // 构造函数结束

    int adjacentSum(int value) {  // 求 value 上下左右四个相邻格子的和
        return cal(value, 0);  // 复用 cal，k=0 表示选相邻方向表
    }  // 方法结束

    int diagonalSum(int value) {  // 求 value 四个对角格子的和
        return cal(value, 1);  // 复用 cal，k=1 表示选对角方向表
    }  // 方法结束

private:  // 以下为内部数据与辅助方法
    vector<vector<int>> grid;  // 矩阵副本
    unordered_map<int, pair<int, int>> d;  // 值到坐标的哈希表，键是格子里的值
    int dirs[2][5] = {{-1, 0, 1, 0, -1}, {-1, 1, 1, -1, -1}};  // 方向表：[0] 是上下左右四方向，[1] 是四个对角方向；末尾重复首元素，方便相邻两项成对取用

    int cal(int value, int k) {  // 通用求和：k 选方向表，value 指定中心格
        auto [i, j] = d[value];  // 用结构化绑定取出中心坐标
        int s = 0;  // s 累加四个合法邻居的值
        for (int q = 0; q < 4; ++q) {  // 四个方向各看一次
            int x = i + dirs[k][q], y = j + dirs[k][q + 1];  // 方向表中相邻两个数构成一个 (dx, dy) 偏移
            if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {  // 邻居仍在矩阵内才计入
                s += grid[x][y];  // 累加邻居的值
            }  // if 结束
        }  // for 结束
        return s;  // 返回四个邻居之和
    }  // cal 结束
};  // 类结束

// 下面是 LeetCode 判题器给出的调用示例，属于注释，原样保留
/**
 * Your NeighborSum object will be instantiated and called as such:
 * NeighborSum* obj = new NeighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */
