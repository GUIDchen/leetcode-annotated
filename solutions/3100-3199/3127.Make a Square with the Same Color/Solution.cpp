// 题目：3127. 构造相同颜色的正方形（Make a Square with the Same Color）
// 思路：枚举所有 2×2 子方阵，只要某个子方阵里黑白格数量不相等（即 3:1 或 4:0），改一个格子就能变成同色。
// 时间复杂度：O(m * n)，每个 2×2 区域只做常数次比较；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canMakeSquare(vector<vector<char>>& grid) {  // 判断能否只改一个格子，就让某个 2×2 区域里出现 3 个同色格
        int dirs[5] = {0, 0, 1, 1, 0};  // 2×2 区域四个角的相对偏移：(0,0)、(0,1)、(1,1)、(1,0)
        for (int i = 0; i < 2; ++i) {  // 枚举 2×2 区域左上角的行号
            for (int j = 0; j < 2; ++j) {  // 枚举左上角的列号
                int cnt1 = 0, cnt2 = 0;  // cnt1 统计白色格数，cnt2 统计黑色格数
                for (int k = 0; k < 4; ++k) {  // 遍历 2×2 区域中的四个格子
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 由偏移得到格子的实际坐标
                    cnt1 += grid[x][y] == 'W';  // 是白色就累加到 cnt1
                    cnt2 += grid[x][y] == 'B';  // 是黑色就累加到 cnt2
                }  // 结束四个格子的遍历
                if (cnt1 != cnt2) {  // 两色数量不等，说明是 3:1 或 4:0，改一个格子即可统一
                    return true;  // 找到可行区域，直接返回 true
                }  // 结束 if 判断
            }  // 结束列枚举
        }  // 结束行枚举
        return false;  // 所有 2×2 区域都是 2:2，无法只改一个格子
    }  // 结束 canMakeSquare 方法
};  // 结束 Solution 类