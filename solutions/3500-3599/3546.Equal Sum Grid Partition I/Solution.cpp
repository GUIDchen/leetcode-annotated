// 题目：3546. 等和矩阵分割 I（Equal Sum Grid Partition I）
// 思路：先求总和，为奇数时不可能平分；否则分别累加行前缀和与列前缀和，存在等于总和一半且两侧都非空的切割线即可。
// 时间复杂度：O(m * n)，行扫描与列扫描各遍历一次矩阵；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canPartitionGrid(vector<vector<int>>& grid) {  // grid：m 行 n 列的整数矩阵
        long long s = 0;  // 矩阵所有元素的总和，用 long long 防止溢出
        for (const auto& row : grid) {  // 遍历矩阵的每一行
            for (int x : row) {  // 遍历该行的每个元素
                s += x;  // 把元素累加到总和
            }
        }
        if (s % 2 != 0) {  // 总和为奇数时无法分成两个相等的部分
            return false;  // 直接判定不可能
        }
        int m = grid.size(), n = grid[0].size();  // m：行数；n：列数
        long long pre = 0;  // 前缀和，先用来统计按行切分时的上方部分
        for (int i = 0; i < m; ++i) {  // 枚举行切割线：第一块包含第 0~i 行
            for (int x : grid[i]) {  // 把第 i 行的元素逐个加入前缀和
                pre += x;  // 累加当前行元素
            }
            if (pre * 2 == s && i + 1 < m) {  // 上方和正好是总和一半，且切割后下方还有行
                return true;  // 找到合法的水平切割线
            }
        }
        pre = 0;  // 重置前缀和，改为统计按列切分时的左侧部分
        for (int j = 0; j < n; ++j) {  // 枚举列切割线：第一块包含第 0~j 列
            for (int i = 0; i < m; ++i) {  // 把第 j 列的元素逐个加入前缀和
                pre += grid[i][j];  // 累加当前列元素
            }
            if (pre * 2 == s && j + 1 < n) {  // 左侧和正好是总和一半，且切割后右侧还有列
                return true;  // 找到合法的垂直切割线
            }
        }
        return false;  // 所有切割线都不满足条件
    }
};