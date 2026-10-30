// 题目：2398. 预算内的最多机器人数目（Maximum Number of Robots Within Budget）
// 思路：滑动窗口 + 单调队列；窗口代价 = 窗口长度 * 运行成本之和 + 窗口内最大充电时间，超预算就收缩左端点。
// 时间复杂度：O(n)，每个下标最多入队、出队一次；空间复杂度：O(n)，单调队列最多保存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {  // chargeTimes：各机器人充电时间；runningCosts：各机器人运行成本；budget：总预算
        deque<int> q;  // 单调递减队列，存下标；队首始终是窗口内充电时间最大的那个
        long long s = 0;  // 当前窗口内所有机器人的运行成本之和
        int ans = 0;  // 满足预算的最大窗口长度，也就是最多能选的机器人数目
        int n = chargeTimes.size();  // 机器人总数，作为右端点的上界
        for (int l = 0, r = 0; r < n; ++r) {  // 右端点 r 逐个扩张，l 是窗口左端点
            s += runningCosts[r];  // 把第 r 个机器人的运行成本计入窗口总和
            while (q.size() && chargeTimes[q.back()] <= chargeTimes[r]) {  // 维护单调递减：队尾充电时间不大于当前值的都弹掉，它们再也当不了最大值
                q.pop_back();  // 弹出被当前元素压过的下标
            }
            q.push_back(r);  // 当前下标入队，成为新的候选最大值
            while (q.size() && (r - l + 1) * s + chargeTimes[q.front()] > budget) {  // 代价 = 人数 * 成本之和 + 最大充电时间，超预算就收缩左端点
                if (q.front() == l) {  // 左端点正是队首那个最大值元素
                    q.pop_front();  // 它即将离开窗口，从队首移除，让次大值顶上
                }
                s -= runningCosts[l++];  // 扣掉左端点的运行成本，并把 l 右移一格
            }
            ans = max(ans, r - l + 1);  // 用当前满足预算的窗口长度更新答案
        }
        return ans;  // 返回预算内能选出的最多机器人数目
    }
};
