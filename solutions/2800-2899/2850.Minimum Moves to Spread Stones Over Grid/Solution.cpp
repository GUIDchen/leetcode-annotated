// 题目：2850. 将石头分散到网格图的最少移动次数（Minimum Moves to Spread Stones Over Grid）
// 核心思路：把 3x3 的石头分布压成 9 位字符串作为状态做按层 BFS，每步把一块石头移到相邻且石头数少于 2 的格子里。
// 时间复杂度：O(状态数 * 9 * 4)，3x3 且总数不超过 9，状态数很小；空间复杂度：O(状态数)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外公开的接口区域
    int minimumMoves(vector<vector<int>>& grid) {  // grid 是 3x3 网格，元素表示该格的石头数
        queue<string> q;  // BFS 队列，存放编码后的状态字符串
        q.push(f(grid));  // 起点状态入队
        unordered_set<string> vis;  // 访问标记集合，防止同一状态被重复扩展
        vis.insert(f(grid));  // 起点同样要标记为已访问
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组，相邻两项组配成一个方向向量（上、右、下、左）

        for (int ans = 0;; ++ans) {  // 按层 BFS，ans 表示当前层数即已经走过的步数
            int sz = q.size();  // 记录本层的节点数，避免把下一层节点也算进来
            while (sz--) {  // 逐层取出本层的所有节点
                string p = q.front();  // 取出队首状态
                q.pop();  // 弹出队首
                if (p == "111111111") {  // 九个格子都是 1，说明石头已经均分，首次到达即为最少步数
                    return ans;  // 返回当前步数
                }  // 结束 if 分支
                vector<vector<int>> cur = g(p);  // 把字符串解码回 3x3 网格，方便枚举格子

                for (int i = 0; i < 3; ++i) {  // 枚举行下标
                    for (int j = 0; j < 3; ++j) {  // 枚举列下标
                        if (cur[i][j] > 1) {  // 只有石头数大于 1 的格子才有石头可以搬走
                            for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                                int x = i + dirs[d];  // 目标格的行坐标
                                int y = j + dirs[d + 1];  // 目标格的列坐标（dirs 相邻两项构成一个方向）
                                if (x >= 0 && x < 3 && y >= 0 && y < 3 && cur[x][y] < 2) {  // 目标必须在界内，且石头数小于 2 才接收，保证每格最终不超过 1
                                    vector<vector<int>> nxt = cur;  // 复制一份网格，构造移动后的新状态
                                    nxt[i][j]--;  // 源格搬走一块石头
                                    nxt[x][y]++;  // 目标格多一块石头
                                    string s = f(nxt);  // 把新网格重新编码成字符串
                                    if (!vis.count(s)) {  // 只有没访问过的状态才继续扩展
                                        vis.insert(s);  // 标记为已访问
                                        q.push(s);  // 入队，等待下一层处理
                                    }  // 结束未访问判断
                                }  // 结束目标合法判断
                            }  // 结束方向循环
                        }  // 结束石头数判断
                    }  // 结束列循环
                }  // 结束行循环
            }  // 本层处理完毕
        }  // 结束无限循环，答案必在有限步内返回
    }  // 结束方法

private:  // 私有辅助函数区
    string f(const vector<vector<int>>& grid) {  // 编码：把 3x3 网格按行拼成 9 位数字字符串
        string s;  // 结果字符串
        for (const auto& row : grid) {  // 逐行扫描
            for (int x : row) {  // 逐格扫描
                s += to_string(x);  // 把该格石头数转成字符追加到末尾
            }  // 结束 for 循环
        }  // 结束 for 循环
        return s;  // 返回编码结果
    }  // 结束函数体

    vector<vector<int>> g(const string& s) {  // 解码：把 9 位字符串还原成 3x3 网格
        vector<vector<int>> grid(3, vector<int>(3));  // 先构造 3 行、每行 3 个 0
        for (int i = 0; i < 3; ++i) {  // 按行填充
            for (int j = 0; j < 3; ++j) {  // 按列填充
                grid[i][j] = s[i * 3 + j] - '0';  // 字符减 '0' 得到数字，下标为 i * 3 + j
            }  // 结束 for 循环
        }  // 结束 for 循环
        return grid;  // 返回解码后的网格
    }  // 结束函数体
};  // 结束类定义
