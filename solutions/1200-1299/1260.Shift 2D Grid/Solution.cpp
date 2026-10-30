// 题目：1260. 二维网格迁移（Shift 2D Grid）
// 思路：把 m×n 网格看成一条长度 m·n 的一维数组，每个元素右移 k 位后按 (idx/n, idx%n) 重新落位，取模实现首尾循环。
// 时间复杂度：O(mn)，每个格子恰好处理一次；空间复杂度：O(mn)，需要新建答案网格。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {  // grid 是 m×n 的整数网格，k 是迁移次数（可大于总格数，靠取模处理）
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        vector<vector<int>> ans(m, vector<int>(n));  // 新建同样尺寸的答案网格（不能原地覆盖，否则会读到已被覆盖的元素）
        for (int i = 0; i < m; ++i) {  // 逐行遍历原网格
            for (int j = 0; j < n; ++j) {  // 逐列遍历原网格
                int idx = (i * n + j + k) % (m * n);  // 先压成一维下标 i*n+j，再右移 k 位并对总格数取模，得到环形移动后的新下标
                int x = idx / n, y = idx % n;  // 把新的一维下标还原成行 x、列 y
                ans[x][y] = grid[i][j];  // 把原元素写到迁移后的位置
            }  // 结束列循环
        }  // 结束行循环
        return ans;  // 返回迁移后的网格
    }  // 结束 shiftGrid
};  // 结束题解类