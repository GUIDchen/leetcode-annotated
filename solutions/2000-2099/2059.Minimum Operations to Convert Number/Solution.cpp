// 题目：2059. 转化数字的最小运算数（Minimum Operations to Convert Number）
// 思路：BFS 求最短路。状态是当前数值 x，每一步可以选 nums 中任一数与 x 做加、减、异或；越界或已访问的数值不再入队。
// 时间复杂度：O(1000 * n)，状态数被限制在 [0, 1000]；空间复杂度：O(1000)，访问数组与队列的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperations(vector<int>& nums, int start, int goal) {  // nums：可用操作数；start：起点；goal：目标值
        using pii = pair<int, int>;  // pii 表示一对「当前数值, 已用步数」
        vector<function<int(int, int)>> ops{  // 把三种运算用 lambda 存进容器，方便统一枚举
            [](int x, int y) { return x + y; },  // 加法
            [](int x, int y) { return x - y; },  // 减法
            [](int x, int y) { return x ^ y; },  // 按位异或
        };
        vector<bool> vis(1001, false);  // 标记 0..1000 内每个数值是否已经入队，避免重复搜索
        queue<pii> q;  // BFS 队列，保证先扩展到的解步数最少
        q.push({start, 0});  // 起点入队，已用步数为 0
        while (!q.empty()) {  // 队列非空就继续扩展
            auto [x, step] = q.front();  // 取出队首状态：当前数值与步数（结构化绑定）
            q.pop();  // 弹出队首
            for (int num : nums) {  // 枚举可以使用的操作数
                for (auto op : ops) {  // 枚举三种运算
                    int nx = op(x, num);  // 计算一步之后得到的新数值
                    if (nx == goal) {  // 一步之后直接命中目标
                        return step + 1;  // 这一步也要计入，所以返回步数加一
                    }
                    if (nx >= 0 && nx <= 1000 && !vis[nx]) {  // 只有落在合法范围内且未访问过的状态才入队
                        q.push({nx, step + 1});  // 新状态入队，步数加一
                        vis[nx] = true;  // 标记已访问，防止重复搜索
                    }
                }
            }
        }
        return -1;  // 队列为空说明目标不可达，返回 -1
    }
};