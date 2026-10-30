// 题目：1284. 转化为全零矩阵的最少反转次数（Minimum Number of Flips to Convert Binary Matrix to Zero Matrix）
// 思路：把整个矩阵压成一个二进制整数作为状态，从初始状态做 BFS，每次翻转某格及其上下左右，首次到达 0 即为最少次数。
// 时间复杂度：O(2^(mn)·mn)，状态数不超过 2^(mn)，每个状态尝试 mn 种翻转；空间复杂度：O(2^(mn))。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFlips(vector<vector<int>>& mat) {  // mat 是 0/1 矩阵，返回把它变成全零矩阵的最少翻转次数
        int m = mat.size(), n = mat[0].size();  // m 为行数，n 为列数
        int state = 0;  // 用二进制位表示整个矩阵的状态，先初始化为全 0
        for (int i = 0; i < m; ++i)  // 逐行遍历，把二维矩阵压成一个整数
            for (int j = 0; j < n; ++j)  // 逐列遍历
                if (mat[i][j])  // 当前格子为 1 时才需要在状态里置位
                    state |= (1 << (i * n + j));  // 第 (i, j) 格对应二进制的第 i * n + j 位
        queue<int> q{{state}};  // BFS 队列，从初始状态开始扩展，两层花括号是列表初始化
        unordered_set<int> vis{{state}};  // 已访问状态集合，防止同一状态被重复处理
        int ans = 0;  // ans 记录已翻转的次数，也就是 BFS 当前层数
        vector<int> dirs = {0, -1, 0, 1, 0, 0};  // 五个翻转位置的方向偏移：中心 (0,0) 加上下左右 (0,-1) (-1,0) (0,1) (1,0)
        while (!q.empty()) {  // 按层进行 BFS，每处理完一层翻转次数加一
            for (int t = q.size(); t; --t) {  // 逐个处理本层状态，t 是本层剩余待处理个数，减到 0 即本层结束
                state = q.front();  // 取出队首状态
                if (state == 0) return ans;  // 状态为 0 说明已是全零矩阵，当前层数就是最少翻转次数
                q.pop();  // 该状态处理完毕，弹出队列
                for (int i = 0; i < m; ++i) {  // 枚举本次要翻转的格子所在行
                    for (int j = 0; j < n; ++j) {  // 枚举本次要翻转的格子所在列
                        int nxt = state;  // 复制当前状态，在副本上做一次翻转
                        for (int k = 0; k < 5; ++k) {  // 依次翻转中心格及其上下左右共 5 个位置
                            int x = i + dirs[k], y = j + dirs[k + 1];  // x、y 是被翻转位置的坐标
                            if (x < 0 || x >= m || y < 0 || y >= n) continue;  // 该位置越界则跳过，不做翻转
                            if ((nxt & (1 << (x * n + y))) != 0)  // 该位当前为 1
                                nxt -= 1 << (x * n + y);  // 把这一位清零，即完成 1 → 0 的翻转
                            else  // 否则该位为 0
                                nxt |= 1 << (x * n + y);  // 把这一位置 1，即完成 0 → 1 的翻转
                        }
                        if (!vis.count(nxt)) {  // 这是首次出现的新状态
                            vis.insert(nxt);  // 记录已访问，避免重复入队
                            q.push(nxt);  // 加入队列，留待下一层继续扩展
                        }
                    }
                }
            }
            ++ans;  // 本层全部处理完，翻转次数加一，进入下一层
        }
        return -1;  // 队列耗尽仍无法变成全零矩阵，返回 -1
    }
};  // 题解类定义结束（本文件末尾无换行，已保留）