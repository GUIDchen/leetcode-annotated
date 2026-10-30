// 题目：3222. 求出硬币游戏的赢家（Find the Winning Player in Coin Game）
// 思路：每次操作固定拿走 1 枚 75 分与 4 枚 10 分硬币（共 115），先算出双方各走一步的完整回合数 k，再看余料是否还够走一步。
// 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    string losingPlayer(int x, int y) {  // x：75 分硬币数；y：10 分硬币数；返回赢家名字
        int k = min(x / 2, y / 8);  // 每次操作消耗 1 枚 75 分 + 4 枚 10 分，k 是「Alice 与 Bob 各走一步」的完整回合数
        x -= k * 2;  // 扣掉 k 个回合用掉的 2k 枚 75 分硬币
        y -= k * 8;  // 扣掉 k 个回合用掉的 8k 枚 10 分硬币
        return x && y >= 4 ? "Alice" : "Bob";  // 余料仍够再走一步（1 枚 75 分且 4 枚 10 分）则轮到先手 Alice 获胜，否则 Bob 获胜
    }
};