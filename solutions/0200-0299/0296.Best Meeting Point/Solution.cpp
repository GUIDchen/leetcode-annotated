// 题目：296. 最佳的碰头地点（Best Meeting Point）🔒
// 思路：曼哈顿距离的行、列两部分可分离，各自取中位数即最优；行号按行扫描天然有序，列号排序后取中位数。
// 时间复杂度：O(mn + k log k)，k 为人数；空间复杂度：O(k)，保存所有点的行、列坐标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTotalDistance(vector<vector<int>>& grid) {  // grid：0/1 矩阵，1 表示该格有人
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        vector<int> rows;  // 收集所有 1 所在的行号
        vector<int> cols;  // 收集所有 1 所在的列号
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                if (grid[i][j]) {  // 该格有人
                    rows.emplace_back(i);  // 记录行号；按行扫描，所以 rows 天然递增有序
                    cols.emplace_back(j);  // 记录列号（此时尚未排序）
                }  // if 块结束
            }  // 内层列循环结束
        }  // 外层行循环结束
        sort(cols.begin(), cols.end());  // cols 是按行收集的，必须排序才能取中位数
        int i = rows[rows.size() / 2];  // 行方向的距离和在中位数处取最小
        int j = cols[cols.size() / 2];  // 列方向同理，取中位数作为会合列
        auto f = [](vector<int>& arr, int x) {  // lambda：计算数组 arr 中所有点到坐标 x 的距离之和
            int s = 0;  // 累加器
            for (int v : arr) {  // 遍历每一个坐标
                s += abs(v - x);  // 累加曼哈顿距离在该方向上的分量
            }  // for 循环结束
            return s;  // 返回该方向的总距离
        };  // lambda 定义结束
        return f(rows, i) + f(cols, j);  // 行、列可分离，总距离就是两个方向距离和相加
    }  // 方法结束
};  // 类定义结束