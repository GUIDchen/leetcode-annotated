// 题目：838. 推多米诺（Push Dominoes）
// 思路：把初始有方向的骨牌当作多源 BFS 起点，time 记录被推动的时刻，force 记录同一时刻作用方向；只有受力唯一时才真正倒下，同时刻受两向力则保持竖直。
// 时间复杂度：O(n)，每块骨牌最多入队常数次；空间复杂度：O(n)，time、force、ans 与队列各 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string pushDominoes(string dominoes) {  // dominoes 由 'L'、'R'、'.' 组成，返回所有推力传播结束后的状态
        int n = dominoes.size();  // 骨牌数量
        queue<int> q;  // BFS 队列：按骨牌被推动的时刻逐层扩展
        vector<int> time(n, -1);  // time[i] 表示骨牌 i 被推动的时刻，-1 表示还没被推动
        vector<string> force(n);  // force[i] 收集同一时刻作用到骨牌 i 上的所有方向
        for (int i = 0; i < n; i++) {  // 初始已经有方向的骨牌作为多源 BFS 的起点
            if (dominoes[i] == '.') continue;  // 竖直的骨牌不是起点，直接跳过
            q.emplace(i);  // 入队，等待它的力向外扩散
            time[i] = 0;  // 初始时刻记为 0
            force[i].push_back(dominoes[i]);  // 把自身方向记为作用在它上面的一份力
        }  // 初始扫描结束

        string ans(n, '.');  // 最终状态先全部置为竖直
        while (!q.empty()) {  // 队列非空说明还有力需要继续传播
            int i = q.front();  // 取出队首骨牌
            q.pop();  // 弹出队首
            if (force[i].size() == 1) {  // 只有受力方向唯一时，这块骨牌才会真正倒下
                char f = force[i][0];  // 取出唯一的方向
                ans[i] = f;  // 写入最终状态
                int j = (f == 'L') ? (i - 1) : (i + 1);  // 力向相邻骨牌传播：L 向左、R 向右
                if (j >= 0 && j < n) {  // 邻居下标必须仍在范围内
                    int t = time[i];  // 当前骨牌被推动的时刻
                    if (time[j] == -1) {  // 邻居第一次被推，需要记录时刻并入队
                        q.emplace(j);  // 邻居入队，轮到它时再继续向外推
                        time[j] = t + 1;  // 邻居被推动的时刻是当前时刻加一
                        force[j].push_back(f);  // 记录这一份方向力
                    } else if (time[j] == t + 1)  // 邻居恰好在同一时刻被反方向也推了一次
                        force[j].push_back(f);  // 两份力并存，邻居受力不唯一，最终保持竖直
                }  // if 结束
            }  // 受力唯一分支结束
        }  // while 结束
        return ans;  // 返回最终状态
    }  // 方法结束
};