// 题目：2589. 完成所有任务的最少时间（Minimum Time to Complete All Tasks）
// 思路：按截止时间升序排序，先用 bitset 抵扣窗口内已占用的时刻，再从窗口最右端往左补齐剩余时长（越靠后越利于后续任务）。
// 时间复杂度：O(n * maxEnd)，每个任务只扫描自己的时间窗；空间复杂度：O(maxEnd)，bitset 固定 2010 位。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMinimumTime(vector<vector<int>>& tasks) {  // tasks 的每个元素是 [start, end, duration]
        sort(tasks.begin(), tasks.end(), [&](auto& a, auto& b) { return a[1] < b[1]; });  // 按截止时刻 a[1]/b[1] 升序，先安排结束得早的任务
        bitset<2010> vis;  // vis[i] 标记第 i 个时刻是否已被某个任务占用（题目时刻上界约 2000）
        int ans = 0;  // 累计被占用的时刻数，即最少需要的时间
        for (auto& task : tasks) {  // 依次处理每个任务
            int start = task[0], end = task[1], duration = task[2];  // 解包：窗口左端、右端、需要的运行时长度
            for (int i = start; i <= end; ++i) {  // 遍历该任务的可用时间窗
                duration -= vis[i];  // 已被别的任务占用的时刻可以顺便抵扣，无需重复占用
            }
            for (int i = end; i >= start && duration > 0; --i) {  // 仍有剩余时长时，从右往左找空闲时刻（靠后占用对后续任务更友好）
                if (!vis[i]) {  // 该时刻还是空闲的
                    --duration;  // 占用一个时刻，剩余待运行时长减一
                    ans += vis[i] = 1;  // 标记占用，同时把答案计数加一
                }
            }
        }
        return ans;  // 返回最少需要占用的时刻总数
    }
};