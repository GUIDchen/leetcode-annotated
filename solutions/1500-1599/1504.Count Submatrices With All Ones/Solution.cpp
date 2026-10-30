// 题目：1504. 统计全 1 子矩形（Count Submatrices With All Ones）
// 思路：先求 g[i][j] = 以 (i,j) 结尾向左连续 1 的个数；再枚举右下角 (i,j)，向上扩展高度，累加该高度下的最小宽度。
// 时间复杂度：O(m^2 * n)，枚举底边、右边、顶边三层；空间复杂度：O(m * n)，保存连续 1 长度表。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int numSubmat(vector<vector<int>>& mat) {  // mat：0/1 矩阵；返回所有元素全为 1 的子矩形个数
        int m = mat.size(), n = mat[0].size();  // m 行 n 列
        vector<vector<int>> g(m, vector<int>(n));  // g[i][j]：以 (i,j) 为右端向左连续 1 的个数；默认 0 表示该格本身为 0
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (mat[i][j] == 1) {  // 只有当前格为 1 才需要计算左连续长度
                    g[i][j] = j == 0 ? 1 : 1 + g[i][j - 1];  // 第 0 列长度为 1；否则等于左边一格的长度加 1
                }
            }  // 本行结束
        }  // 整个矩阵的连续长度统计完成
        int ans = 0;  // 全 1 子矩形的个数累加器
        for (int i = 0; i < m; ++i) {  // 枚举子矩形的底边所在行 i
            for (int j = 0; j < n; ++j) {  // 枚举子矩形的右边所在列 j
                int col = 1 << 30;  // 自底向上扩展时的最小宽度，先取一个足够大的初值
                for (int k = i; k >= 0 && col > 0; --k) {  // 顶边 k 从 i 逐行上移到 0；宽度为 0 后再上移不会有贡献，提前退出
                    col = min(col, g[k][j]);  // 高度增加一行，宽度取覆盖到的各行左连续长度的最小值
                    ans += col;  // 高度固定时左边界的可选位置恰好有 col 个，全部计入答案
                }
            }
        }
        return ans;
    }
};