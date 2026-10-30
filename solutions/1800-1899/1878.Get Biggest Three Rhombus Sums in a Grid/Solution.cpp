// 题目：1878. 矩阵中最大的三个菱形和（Get Biggest Three Rhombus Sums in a Grid）
// 思路：分别对「↘」和「↙」两个斜方向做前缀和，再枚举每个格子作为菱形中心与半径 k，用四条边的差分求和并修正多算/漏算的顶点，用 set 维护最大的三个和。
// 时间复杂度：O(m * n * min(m, n) * log 3)，枚举中心与半径；空间复杂度：O(m * n)，两张斜向前缀和表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getBiggestThree(vector<vector<int>>& grid) {  // grid：m 行 n 列的正整数矩阵；返回最大的三个互不相同的菱形和（不足三个则全返回）
        int m = grid.size(), n = grid[0].size();  // m：行数；n：列数
        vector<vector<int>> s1(m + 1, vector<int>(n + 2));  // s1[i][j]：沿「↘」方向到 (i, j) 的斜向前缀和；多开一行两列，省去边界判断
        vector<vector<int>> s2(m + 1, vector<int>(n + 2));  // s2[i][j]：沿「↙」方向到 (i, j) 的斜向前缀和；同样多留边界
        for (int i = 1; i <= m; ++i) {  // 用 1 基下标遍历每一行（与 grid 的 0 基相差 1）
            for (int j = 1; j <= n; ++j) {  // 用 1 基下标遍历每一列
                s1[i][j] = s1[i - 1][j - 1] + grid[i - 1][j - 1];  // 「↘」方向递推：上一格 (i-1, j-1) 的前缀和再加当前格 grid[i-1][j-1]
                s2[i][j] = s2[i - 1][j + 1] + grid[i - 1][j - 1];  // 「↙」方向递推：右上格 (i-1, j+1) 的前缀和再加当前格（j+1 依赖多开的那一列）
            }  // 当前格的两条斜向前缀和都已算好
        }  // 全表前缀和计算完毕
        set<int> ss;  // 有序集合：自动去重并升序保存目前见过的菱形和
        for (int i = 1; i <= m; ++i) {  // 枚举菱形的中心行 i（1 基）
            for (int j = 1; j <= n; ++j) {  // 枚举菱形的中心列 j（1 基）
                int l = min({i - 1, m - i, j - 1, n - j});  // 半径上限：中心到四条边界的最近距离，保证菱形不越界
                ss.insert(grid[i - 1][j - 1]);  // 半径 0 的退化菱形就是单个格子，本身也是一个候选和
                for (int k = 1; k <= l; ++k) {  // 枚举半径 k，对应四边长度为 k 的菱形
                    int a = s1[i + k][j] - s1[i][j - k];  // 左下边：沿「↘」从 (i, j-k) 到 (i+k, j) 的格子和
                    int b = s1[i][j + k] - s1[i - k][j];  // 右上边：沿「↘」从 (i-k, j) 到 (i, j+k) 的格子和
                    int c = s2[i][j - k] - s2[i - k][j];  // 左上边：沿「↙」从 (i-k, j) 到 (i, j-k) 的格子和
                    int d = s2[i + k][j] - s2[i][j + k];  // 右下边：沿「↙」从 (i, j+k) 到 (i+k, j) 的格子和
                    ss.insert(a + b + c + d - grid[i + k - 1][j - 1] + grid[i - k - 1][j - 1]);  // 四条边相加时下顶点被算两次要减掉，上顶点一次都没算要补上，得到菱形和
                }  // 半径枚举结束
                while (ss.size() > 3) {  // 只要最大的三个和，多余的小值随时裁掉以控制集合大小
                    ss.erase(ss.begin());  // set 升序存放，begin() 是最小值，直接删除
                }  // 裁剪到不超过 3 个元素
            }  // 中心列枚举结束
        }  // 中心行枚举结束
        return vector<int>(ss.rbegin(), ss.rend());  // set 升序存放，用反向迭代器构造出降序结果
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行）