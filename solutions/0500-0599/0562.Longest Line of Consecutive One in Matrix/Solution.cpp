// 题目：562. 矩阵中最长的连续 1 线段（Longest Line of Consecutive One in Matrix）
// 思路：按竖直、水平、主对角线、副对角线四个方向做线性 DP：a/b/c/d 分别记录以当前格为终点在该方向的连续 1 长度，边填表边取全局最大值。
// 时间复杂度：O(m·n)，每格常数次转移；空间复杂度：O(m·n)，四个 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestLine(vector<vector<int>>& mat) {  // mat 是只含 0/1 的矩阵，返回八个方向中最长的连续 1 线段长度
        int m = mat.size(), n = mat[0].size();  // m、n 分别是行数与列数
        vector<vector<int>> a(m + 2, vector<int>(n + 2));  // a：以当前格为终点、竖直向上方向的连续 1 长度
        vector<vector<int>> b(m + 2, vector<int>(n + 2));  // b：以当前格为终点、水平向左方向的连续 1 长度
        vector<vector<int>> c(m + 2, vector<int>(n + 2));  // c：以当前格为终点、主对角线（左上到右下）方向的连续 1 长度
        vector<vector<int>> d(m + 2, vector<int>(n + 2));  // d：以当前格为终点、副对角线（右上到左下）方向的连续 1 长度
        int ans = 0;  // ans 记录所有方向、所有位置上的最大长度
        for (int i = 1; i <= m; ++i) {  // 外扩一圈全 0 边界（i 从 1 开始），省去越界判断
            for (int j = 1; j <= n; ++j) {  // j 从 1 开始循环，对应原始矩阵第 j-1 列
                if (mat[i - 1][j - 1]) {  // mat[i-1][j-1] 为 1 才能延长线段
                    a[i][j] = a[i - 1][j] + 1;  // 竖直方向：由上一行同列的计数加 1
                    b[i][j] = b[i][j - 1] + 1;  // 水平方向：由同一行左一列的计数加 1
                    c[i][j] = c[i - 1][j - 1] + 1;  // 主对角线方向：由左上角的计数加 1
                    d[i][j] = d[i - 1][j + 1] + 1;  // 副对角线方向：由右上角（j+1 列）的计数加 1，这正是每行多开两列的原因
                    ans = max(ans, max(a[i][j], max(b[i][j], max(c[i][j], d[i][j]))));  // 四个方向取最大，再与历史答案比较
                }  // 非 1 位置不做转移，判断结束
            }  // 内层列循环结束
        }  // 外层行循环结束
        return ans;  // 返回全局最长连续 1 线段长度
    }
};