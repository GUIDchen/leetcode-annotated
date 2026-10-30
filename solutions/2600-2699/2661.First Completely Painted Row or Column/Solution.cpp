// 题目：2661. 找出叠涂元素（First Completely Painted Row or Column）
// 核心思路：先建「值 → 坐标」哈希表，再按 arr 的顺序逐格涂色，用 row/col 计数数组统计每行每列已涂格数，首次达到满行或满列即返回下标。
// 时间复杂度：O(m*n)，建索引与涂色各线性一次；空间复杂度：O(m*n)，哈希表与计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {  // arr：涂色顺序（元素为矩阵中的值）；mat：待涂色的 m×n 矩阵
        int m = mat.size(), n = mat[0].size();  // 矩阵的行数 m 与列数 n
        unordered_map<int, pair<int, int>> idx;  // 哈希表：值 → 它在矩阵中的（行，列）坐标
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                idx[mat[i][j]] = {i, j};  // 记录该数值的位置，后面就能 O(1) 查到坐标
            }  // 列循环结束
        }  // 行循环结束：矩阵中每个值的位置索引都建好了
        vector<int> row(m), col(n);  // row[i]：第 i 行已涂的格数；col[j]：第 j 列已涂的格数
        for (int k = 0;; ++k) {  // 按涂色顺序推进；题目保证一定存在答案，所以省略循环上界
            auto [i, j] = idx[arr[k]];  // 取出本次被涂的值所在的行列（结构化绑定一次解出 i、j）
            ++row[i];  // 该行已涂格数加一
            ++col[j];  // 该列已涂格数加一
            if (row[i] == n || col[j] == m) {  // 某行涂满 n 格或某列涂满 m 格，说明出现了第一条完整的行或列
                return k;  // 返回触发“完整行/列”的涂色下标 k
            }  // if 分支结束
        }  // for 循环结束
    }  // 方法结束
};  // 类定义结束（文件末尾无换行，按原样保留）