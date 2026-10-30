// 题目：1861. 旋转盒子（Rotating the Box）
// 思路：先按顺时针 90° 把 m×n 的矩阵搬到 n×m 的 ans（原 (i, j) → 新 (j, m-1-i)），再逐列从底往上用队列记录空位，模拟石头受重力下落，遇到障碍 '*' 就清空队列。
// 时间复杂度：O(mn)，旋转与下落各扫描一遍；空间复杂度：O(mn)，存放旋转后的答案矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {  // boxGrid：m 行 n 列的原始盒子
        int m = boxGrid.size(), n = boxGrid[0].size();  // m 为行数，n 为列数
        vector<vector<char>> ans(n, vector<char>(m));  // 旋转后尺寸变成 n 行 m 列
        for (int i = 0; i < m; ++i) {  // 外层循环：遍历原矩阵的每一行
            for (int j = 0; j < n; ++j) {  // 内层循环：遍历这一行的每一列
                ans[j][m - i - 1] = boxGrid[i][j];  // 顺时针旋转公式：原 (i, j) 落到新 (j, m-1-i)
            }  // 一行搬完
        }  // 整个矩阵旋转完成
        for (int j = 0; j < m; ++j) {  // 逐列模拟重力，ans 共 m 列、每列 n 个格子
            queue<int> q;  // 队列保存当前列可落空的空位行号，队首是最靠下的空位
            for (int i = n - 1; ~i; --i) {  // 从列底往上扫描，~i 等价于 i >= 0
                if (ans[i][j] == '*') {  // 遇到固定障碍：它上方的石头无法再穿过这里
                    queue<int> t;  // 借助一个空队列 t
                    swap(t, q);  // 用 swap 清空 q：障碍上方的空位对下方石头不再可用
                } else if (ans[i][j] == '.') {  // 空格子：记录为一个可以落石的位置
                    q.push(i);  // 自下而上入队，队首始终是最底部的空位
                } else if (!q.empty()) {  // 剩下只能是石头 '#'：若下方还有空位就让石头下落
                    ans[q.front()][j] = '#';  // 石头落到最靠下的空位
                    q.pop();  // 该空位已被占用，出队
                    ans[i][j] = '.';  // 石头原来的位置变成空
                    q.push(i);  // 新空出来的位置可以继续承接上方石头
                }  // 石头处理结束：队列为空说明它被下方堵住，只能原地不动
            }  // 这一列的下落模拟结束
        }  // 所有列处理完毕
        return ans;  // 返回旋转并重排后的盒子
    }  // 方法结束
};  // 类定义结束
