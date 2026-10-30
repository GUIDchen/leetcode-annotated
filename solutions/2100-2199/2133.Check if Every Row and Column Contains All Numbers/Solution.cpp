// 题目：2133. 检查是否每一行每一列都包含全部整数（Check if Every Row and Column Contains All Numbers）
// 思路：用布尔数组记录某个数是否出现，先逐行检查是否有重复，再逐列检查是否有重复；n 个数互不相同即恰好是 1..n。
// 时间复杂度：O(n^2)，行与列各遍历一遍矩阵；空间复杂度：O(n)，一个长度为 n+1 的标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkValid(vector<vector<int>>& matrix) {  // matrix：n × n 的待检查矩阵
        int n = matrix.size();  // 矩阵的阶数 n，也是每行每列应有的元素个数
        bool vis[n + 1];  // 标记数组：vis[x] 表示数字 x 是否已经出现，下标 1..n
        for (const auto& row : matrix) {  // 逐个检查每一行
            memset(vis, false, sizeof(vis));  // 每换一行就清空标记
            for (int x : row) {  // 遍历该行的每个元素
                if (vis[x]) {  // 数字 x 在本行重复出现，说明该行不合法
                    return false;  // 立即返回失败
                }
                vis[x] = true;  // 标记数字 x 已经出现过
            }
        }
        for (int j = 0; j < n; ++j) {  // 逐个检查每一列
            memset(vis, false, sizeof(vis));  // 每换一列就清空标记
            for (int i = 0; i < n; ++i) {  // 沿该列从上到下遍历
                if (vis[matrix[i][j]]) {  // 数字在本列重复出现，说明该列不合法
                    return false;  // 立即返回失败
                }
                vis[matrix[i][j]] = true;  // 标记该数字在本列已经出现过
            }
        }
        return true;  // 行和列都没有重复，说明都恰好包含 1..n，返回合法
    }
};
