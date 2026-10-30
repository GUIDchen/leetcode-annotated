// 题目：1329. 将矩阵按对角线排序（Sort the Matrix Diagonally）
// 思路：同一条「左上→右下」对角线上的元素 i-j 相同，用 m-i+j 给对角线编号分桶；每个桶降序排序后，再按原坐标从桶尾取最小值依次写回。
// 时间复杂度：O(m*n*log(min(m,n)))，每条对角线单独排序；空间复杂度：O(m*n)，桶里存全部元素。
class Solution {  // 题解类
public:  // 对外暴露题解接口
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {  // mat：待排序的 m 行 n 列矩阵，返回原地排序后的矩阵
        int m = mat.size(), n = mat[0].size();  // m 为行数，n 为列数（题目保证矩阵非空）
        vector<int> g[m + n];  // 桶数组：用 m-i+j 作为对角线编号，共 m+n 个可能的编号
        for (int i = 0; i < m; ++i) {  // 枚举行下标
            for (int j = 0; j < n; ++j) {  // 枚举列下标
                g[m - i + j].push_back(mat[i][j]);  // 把元素放进它所在对角线的桶里
            }  // 列循环结束
        }  // 行循环结束
        for (auto& e : g) {  // 逐条对角线单独排序
            sort(e.rbegin(), e.rend());  // 降序排列，后面配合 back()/pop_back() 就能每次取到最小值
        }  // 排序结束
        for (int i = 0; i < m; ++i) {  // 再次枚举矩阵，把排好序的元素写回原位
            for (int j = 0; j < n; ++j) {  // 枚举列下标
                mat[i][j] = g[m - i + j].back();  // 降序桶的末尾正是当前剩余的最小元素
                g[m - i + j].pop_back();  // 取走一个，保证沿对角线方向递增填充
            }  // 列循环结束
        }  // 行循环结束
        return mat;  // 返回排序后的矩阵
    }  // 方法结束
};  // 类定义结束