// 3459. 最长 V 形对角线段的长度 / Length of Longest V-Shaped Diagonal Segment
// 核心思路：从每个值为 1 的格子出发，沿 4 条对角线方向做记忆化深搜，允许在途中拐弯一次，取能走出的最长 V 形段。
// 复杂度：时间复杂度 O(m·n)，空间复杂度 O(m·n)。
class Solution {  // 题解类
public:  // 公有接口
    static constexpr int MAXN = 501;  // 网格最大边长
    int f[MAXN][MAXN][4][2];  // 记忆化数组：f[i][j][k][cnt] 表示从 (i,j) 沿方向 k、拐弯状态为 cnt 时的后续最大长度

    int lenOfVDiagonal(vector<vector<int>>& grid) {  // 求最长的 V 形对角线段的长度
        int m = grid.size(), n = grid[0].size();  // 网格行数与列数
        int dirs[5] = {1, 1, -1, -1, 1};  // 四个对角线方向的增量，首尾相接便于用 (k+1)%4 拐弯
        memset(f, -1, sizeof(f));  // 记忆化数组初始化为 -1 表示未计算

        auto dfs = [&](this auto&& dfs, int i, int j, int k, int cnt) -> int {  // 记忆化深搜：cnt 为 1 表示还能拐弯
            if (f[i][j][k][cnt] != -1) {  // 该状态已经算过
                return f[i][j][k][cnt];  // 直接返回记忆值
            }  // 结束记忆命中判断
            int x = i + dirs[k];  // 按方向 k 计算下一个行下标
            int y = j + dirs[k + 1];  // 按方向 k 计算下一个列下标
            int target = grid[i][j] == 1 ? 2 : (2 - grid[i][j]);  // V 形段要求的下一格数值：1→2、2→0、0→2
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != target) {  // 越界或数值不满足要求
                f[i][j][k][cnt] = 0;  // 无法继续延伸
                return 0;  // 返回 0
            }  // 结束可行性判断
            int res = dfs(x, y, k, cnt);  // 继续沿原方向前进
            if (cnt > 0) {  // 还有拐弯机会
                res = max(res, dfs(x, y, (k + 1) % 4, 0));  // 也可以在此处拐弯，之后不再能拐弯
            }  // 结束拐弯尝试
            f[i][j][k][cnt] = 1 + res;  // 记忆结果：包含下一格在内的后续长度
            return 1 + res;  // 当前格自身贡献 1
        };  // 结束 dfs 定义

        int ans = 0;  // 答案
        for (int i = 0; i < m; ++i) {  // 枚举起点行
            for (int j = 0; j < n; ++j) {  // 枚举起点列
                if (grid[i][j] == 1) {  // V 形段必须以 1 开头
                    for (int k = 0; k < 4; ++k) {  // 枚举四个出发方向
                        ans = max(ans, dfs(i, j, k, 1) + 1);  // 加上起点自身后更新答案
                    }  // 结束方向枚举
                }  // 结束起点判断
            }  // 结束列枚举
        }  // 结束行枚举
        return ans;  // 返回最长 V 形对角线段长度
    }  // 结束 lenOfVDiagonal
};  // 结束题解类
