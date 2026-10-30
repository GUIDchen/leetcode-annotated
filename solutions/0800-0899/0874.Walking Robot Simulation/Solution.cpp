// 题目：874. 模拟行走机器人（Walking Robot Simulation）
// 核心思路：方向增量表模拟转向，障碍物坐标编码成整数存入哈希集合，按步逐格前进、撞障碍物即提前停下并记录最远距离平方。
// 时间复杂度：O(m + n)，m 为障碍物数量、n 为指令中需要走的步数总和；空间复杂度：O(m)，哈希集合存放障碍物。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {  // commands：指令序列（-2 左转、-1 右转、正数前进步数）；obstacles：障碍物坐标列表
        int dirs[5] = {0, 1, 0, -1, 0};  // 方向增量表：相邻两项组成一个方向向量，dirs[k] 与 dirs[k+1] 就是当前朝向的 dx、dy，k=0 表示朝北（y 正方向）
        auto f = [](int x, int y) {  // 局部 lambda：把二维坐标压缩成一个 long long 整数，作为哈希集合的键
            return 1LL * x * 200001 + y;  // 障碍物 y 的绝对值不超过 100000，乘 200001 后不同 x 的坐标不会撞到同一个键
        };  // 坐标编码 lambda 结束
        unordered_set<long long> s;  // 哈希集合：存放所有障碍物的编码，便于 O(1) 判断某一格能否落脚
        for (auto& e : obstacles) {  // 遍历每个障碍物
            s.insert(f(e[0], e[1]));  // 把障碍物坐标编码后放入集合
        }  // 障碍物预处理完成
        int ans = 0, k = 0;  // ans 记录途中离原点最远的距离平方；k 是当前朝向在 dirs 中的下标，0 表示朝北
        int x = 0, y = 0;  // 机器人当前坐标，初始在原点
        for (int c : commands) {  // 按顺序执行每一条指令
            if (c == -2) {  // -2 表示左转 90 度
                k = (k + 3) % 4;  // 左转等价于在方向环上后退一格，加 3 再对 4 取模可避免出现负数下标
            } else if (c == -1) {  // -1 表示右转 90 度
                k = (k + 1) % 4;  // 右转等价于在方向环上前进一格
            } else {  // 其余情况是正数，表示朝当前方向前进 c 步
                while (c--) {  // 一步一步地走，这样才能走到障碍物前就立刻停住
                    int nx = x + dirs[k], ny = y + dirs[k + 1];  // 按当前朝向算出下一步的候选坐标
                    if (s.count(f(nx, ny))) {  // 候选位置上有障碍物
                        break;  // 这一步走不动，剩余步数全部作废
                    }  // 没有障碍物则继续前进
                    x = nx;  // 真正更新横坐标
                    y = ny;  // 真正更新纵坐标
                    ans = max(ans, x * x + y * y);  // 每走一步都刷新一次最远距离平方
                }  // 本段步数处理完毕
            }  // 单条指令处理完毕
        }  // 所有指令执行完毕
        return ans;  // 返回途中离原点距离平方的最大值，正是题目要求的答案
    }  // robotSim 结束
};  // Solution 类结束