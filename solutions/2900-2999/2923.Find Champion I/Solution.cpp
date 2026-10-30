// 题目：2923. 找到冠军 I（Find Champion I）
// 思路：冠军要战胜其余所有队伍，逐行统计胜场数，胜场数等于 n-1 的队伍就是冠军。
// 时间复杂度：O(n^2)，最坏需要检查整张矩阵；空间复杂度：O(1)，只用了计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findChampion(vector<vector<int>>& grid) {  // grid[i][j]==1 表示 i 比 j 强，返回战胜所有对手的冠军
        int n = grid.size();  // 队伍数量
        for (int i = 0;; ++i) {  // 题目保证存在冠军，逐个队伍检查即可
            int cnt = 0;  // 统计 i 战胜的队伍数
            for (int j = 0; j < n; ++j) {  // 枚举所有对手
                if (i != j && grid[i][j] == 1) {  // 跳过自己，且只统计 i 获胜的场次
                    ++cnt;  // 胜场加一
                }  // 内层 if 结束
            }  // 对手遍历结束
            if (cnt == n - 1) {  // 战胜了其余所有队伍
                return i;  // 这支队伍就是冠军
            }  // 找到冠军，判断结束
        }  // 外层循环结束
    }  // findChampion 结束
};  // 类定义结束