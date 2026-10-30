// 题目：1914. 循环轮转矩阵（Cyclically Rotating a Grid）
// 思路：逐层处理，把第 p 圈按顺时针展开成一维数组，整体右移 k 位（k 对圈长取模），再按同样顺序写回。
// 时间复杂度：O(m*n)，每个格子被读写常数次；空间复杂度：O(min(m, n))，只保存当前这一圈的元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {  // grid：待轮转的矩阵；k：顺时针轮转步数
        int m = grid.size(), n = grid[0].size();  // m、n：矩阵的行数与列数
        auto rotate = [&](int p, int k) {  // lambda rotate(p, k)：处理第 p 圈（p 从 0 开始，向外层到内层）
            vector<int> nums;  // nums：按顺时针顺序暂存这一圈的所有元素
            for (int j = p; j < n - p - 1; ++j) {  // 上边：从左到右（不含右上角，避免重复）
                nums.push_back(grid[p][j]);  // 收集上边元素
            }
            for (int i = p; i < m - p - 1; ++i) {  // 右边：从上到下
                nums.push_back(grid[i][n - p - 1]);  // 收集右边元素
            }
            for (int j = n - p - 1; j > p; --j) {  // 下边：从右到左
                nums.push_back(grid[m - p - 1][j]);  // 收集下边元素
            }
            for (int i = m - p - 1; i > p; --i) {  // 左边：从下到上
                nums.push_back(grid[i][p]);  // 收集左边元素，四条边首尾相接正好覆盖整圈
            }
            int l = nums.size();  // l：这一圈的元素个数
            k %= l;  // 轮转 k 位等价于 k 对圈长取模，避免多余绕圈
            if (k == 0) {  // 余数为 0 说明这一圈不需要移动
                return;  // 直接返回，省掉一次无意义的写回
            }
            for (int j = p; j < n - p - 1; ++j) {  // 重新走上边：从 nums 的下标 k 开始依次写回
                grid[p][j] = nums[k++ % l];  // k 每用一个就自增并对 l 取模，实现循环右移
            }
            for (int i = p; i < m - p - 1; ++i) {  // 重新走右边
                grid[i][n - p - 1] = nums[k++ % l];  // 同样取下一个轮转后的值
            }
            for (int j = n - p - 1; j > p; --j) {  // 重新走下边
                grid[m - p - 1][j] = nums[k++ % l];  // 同样取下一个轮转后的值
            }
            for (int i = m - p - 1; i > p; --i) {  // 重新走左边
                grid[i][p] = nums[k++ % l];  // 写完最后一个元素，整圈右移完成
            }
        };  // lambda 定义结束
        for (int p = 0; p < min(m, n) / 2; ++p) {  // 圈数最多为 min(m, n) / 2，从外到内逐层处理
            rotate(p, k);  // 处理第 p 圈
        }
        return grid;  // 返回原地修改后的矩阵
    }  // 方法结束
};  // 类定义结束