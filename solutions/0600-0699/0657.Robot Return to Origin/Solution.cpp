// 题目：657. 机器人能否返回原点（Robot Return to Origin）
// 核心思路：分别维护水平与垂直位移，遍历完整指令串后判断坐标是否为 (0, 0)。
// 时间复杂度：O(n)，只遍历一次指令串；空间复杂度：O(1)，只用两个计数器。
class Solution {  // LeetCode 约定的题解类
public:
    bool judgeCircle(string moves) {  // moves 是 U/D/L/R 组成的指令串，判断走完后是否回到原点
        int x = 0, y = 0;  // x、y 是当前坐标，初始在 (0, 0)
        for (char c : moves) {  // 逐条处理移动指令
            switch (c) {  // 按方向分支更新坐标
            case 'U': y++; break;  // U 向上：纵坐标加一
            case 'D': y--; break;  // D 向下：纵坐标减一
            case 'L': x--; break;  // L 向左：横坐标减一
            case 'R': x++; break;  // R 向右：横坐标加一
            }  // switch 结束，继续处理下一条指令
        }
        return x == 0 && y == 0;  // 两个坐标都回到 0 才算回到原点
    }
};  // 题解类定义结束
