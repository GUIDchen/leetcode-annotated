// 题目：2174. 通过翻转行或列来去除所有的 1 II（Remove All Ones With Row and Column Flips II）
// 思路：二进制位压缩网格状态，从初始状态开始 BFS；每步只能对「原本是 1 的格子」所在的行和列清零，第一次得到 0 状态的层数就是答案。
// 时间复杂度：O(2^(m·n) · m · n·(m+n))，状态数最多 2^(m·n)；空间复杂度：O(2^(m·n))，队列与 visited 集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int removeOnes(vector<vector<int>>& grid) {  // grid：0/1 矩阵；返回清除所有 1 所需的最少操作次数，无解返回 -1
        int m = grid.size(), n = grid[0].size();  // m 行 n 列，用位号 i*n+j 表示第 i 行第 j 列
        int state = 0;  // state：当前网格的位压缩表示，第 k 位为 1 表示该格子还是 1
        for (int i = 0; i < m; ++i)  // 逐行展平矩阵
            for (int j = 0; j < n; ++j)  // 枚举行内的每一列
                if (grid[i][j])  // 只把值为 1 的格子写进位掩码
                    state |= (1 << (i * n + j));  // 置位第 i*n+j 位；(1 << ...) 注意 m*n 不超过 30 才安全
        queue<int> q{{state}};  // 队列的初始元素就是初始状态（BFS 第 0 层）
        unordered_set<int> vis{{state}};  // visited 集合用于去重，避免同一状态被反复入队
        int ans = 0;  // ans 记录当前 BFS 的层数，也就是已经做过的操作次数
        while (!q.empty()) {  // 队列非空就继续扩展
            for (int k = q.size(); k > 0; --k) {  // 按层遍历：k 是这一层待处理的节点个数，处理完一层答案加一
                state = q.front();  // 取出队首状态
                q.pop();  // 队首出队
                if (state == 0) return ans;  // 状态为 0 表示所有 1 都被清除，当前层数就是最少操作数
                for (int i = 0; i < m; ++i) {  // 枚举行，寻找可以作为操作锚点的 1
                    for (int j = 0; j < n; ++j) {  // 枚举列
                        if (grid[i][j] == 0) continue;  // 只有原网格该位置是 1 时才允许以它为中心清行清列
                        int nxt = state;  // 从当前状态复制一份作为下一状态
                        for (int r = 0; r < m; ++r) nxt &= ~(1 << (r * n + j));  // 把第 j 列整列清零（按位与非）
                        for (int c = 0; c < n; ++c) nxt &= ~(1 << (i * n + c));  // 把第 i 行整行清零
                        if (!vis.count(nxt)) {  // 新状态没访问过才入队
                            vis.insert(nxt);  // 标记已访问
                            q.push(nxt);  // 加入队列，等待下一层扩展
                        }  // 新状态处理结束
                    }  // 列循环结束
                }  // 行循环结束
            }  // 本层所有节点扩展完毕
            ++ans;  // 层数加一，代表又多做了一次操作
        }  // BFS 结束
        return -1;  // 所有可达状态都试过仍未清空，说明无解
    }  // 方法结束
};  // 类定义结束，源文件到此为止