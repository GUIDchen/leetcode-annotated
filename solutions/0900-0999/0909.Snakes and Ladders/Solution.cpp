// 题目：909. 蛇梯棋（Snakes and Ladders）
// 核心思路：把棋盘编号 1..n² 当作图的节点做 BFS，每步最多走 6 格，遇到蛇或梯子就跳到目标格，层数即最少步数。
// 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，访问数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int snakesAndLadders(vector<vector<int>>& board) {  // board：蛇梯棋盘（-1 表示普通格，其余表示跳转目标）；返回最少步数
        int n = board.size();  // 棋盘边长，格子编号为 1..n*n
        queue<int> q{{1}};  // BFS 队列，从起点 1 号格开始
        int m = n * n;  // 终点编号，也是掷骰子不能越过的上界
        vector<bool> vis(m + 1);  // 访问标记，避免同一个格子重复入队
        vis[1] = true;  // 起点已访问

        for (int ans = 0; !q.empty(); ++ans) {  // ans 记录 BFS 层数，也就是最少掷骰次数
            for (int k = q.size(); k > 0; --k) {  // 逐层处理，保证同一层的步数相同
                int x = q.front();  // 取出队首格子
                q.pop();  // 弹出已处理的格子
                if (x == m) {  // 到达终点
                    return ans;  // 返回当前层数作为最少步数
                }  // 结束终点判断
                for (int y = x + 1; y <= min(x + 6, m); ++y) {  // 掷骰子走 1..6 步，注意不能超过终点
                    int i = (y - 1) / n, j = (y - 1) % n;  // 把编号换算成行列（行从下往上数）
                    if (i % 2 == 1) {  // 奇数行（从下往上第二行起）的编号方向相反
                        j = n - j - 1;  // 反转列下标，还原蛇形编号的真实位置
                    }  // 结束列反转
                    i = n - i - 1;  // 行号在上方，需要翻转成从上往下数的下标
                    int z = board[i][j] == -1 ? y : board[i][j];  // 普通格停在 y，蛇或梯子则跳到目标格
                    if (!vis[z]) {  // 目标格还没访问过
                        vis[z] = true;  // 标记为已访问
                        q.push(z);  // 加入队列，等待下一层扩展
                    }  // 结束访问判断
                }  // 结束骰子枚举
            }  // 结束本层
        }  // 结束 BFS
        return -1;  // 队列耗尽仍未到达终点，返回 -1
    }  // 结束 snakesAndLadders
};  // 结束 Solution 类