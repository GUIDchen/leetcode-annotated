// 题目：2596. 检查骑士巡视方案（Check Knight Tour Configuration）
// 思路：先用编号做下标反查每一步的坐标，再依次检查相邻两步的坐标差是否为「日」字（1×2 或 2×1）。
// 时间复杂度：O(n²)，建表与校验各扫一遍 n×n；空间复杂度：O(n²)，坐标表存 n² 个点对。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkValidGrid(vector<vector<int>>& grid) {  // grid：n×n 的巡视编号矩阵；返回该矩阵是否描述一条合法的骑士巡视路线
        if (grid[0][0] != 0) {  // 骑士必须从左上角 (0,0) 出发，因此该格编号必须是 0
            return false;  // 起点编号不为 0，方案非法
        }  // 起点检查通过，继续后续校验
        int n = grid.size();  // 棋盘边长 n，总步数为 n * n
        vector<pair<int, int>> pos(n * n);  // pos[v] 保存编号 v 所处格子的坐标 (行, 列)
        for (int i = 0; i < n; ++i) {  // 枚举每一行，把所有格子登记到坐标表
            for (int j = 0; j < n; ++j) {  // 枚举当前行的每一列
                pos[grid[i][j]] = {i, j};  // 反查：把格子 (i, j) 挂到它对应的步数编号 grid[i][j] 下
            }  // 本行登记完毕
        }  // 整张表登记完毕
        for (int i = 1; i < n * n; ++i) {  // 依次检查第 i-1 步到第 i 步是否构成合法的骑士跳跃
            auto [x1, y1] = pos[i - 1];  // 上一步的坐标（C++17 结构化绑定解包）
            auto [x2, y2] = pos[i];  // 当前这一步的坐标
            int dx = abs(x1 - x2);  // 行号差的绝对值
            int dy = abs(y1 - y2);  // 列号差的绝对值
            bool ok = (dx == 1 && dy == 2) || (dx == 2 && dy == 1);  // 骑士只能走「日」字，即行差列差为 1 与 2（顺序可交换）
            if (!ok) {  // 步长不符合骑士规则
                return false;  // 该相邻步非法，直接判定方案无效
            }  // 本对相邻步检查完毕
        }  // 所有相邻步均已检查完
        return true;  // 全部相邻步都合法，方案有效
    }
};