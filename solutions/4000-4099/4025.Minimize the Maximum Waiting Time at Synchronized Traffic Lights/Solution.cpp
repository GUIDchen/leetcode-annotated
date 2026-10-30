// 4025. 交通灯的最大等待时间 / Minimize the Maximum Waiting Time at Synchronized Traffic Lights
// 核心思路：只有最靠后的灯位 mx 决定通行窗口；对每个到达时刻求周期内相位 r = x % period，若 r >= mx 则需等待 period - r，取全部等待时间的最大值。
// 复杂度：时间 O(n + m)，空间 O(1)（n 为 lights 长度，m 为 arrivalTime 长度）。
class Solution {  // 题解类定义
public:  // 公有成员：判题器调用的接口
    int minPenalty(int period, vector<int>& lights, vector<int>& arrivalTime) {  // 返回所有到达时刻中可能出现的最大等待时间
        int mx = ranges::max(lights);  // 只需关心最靠后的灯位，它决定了周期内可通行的相位长度

        int ans = 0;  // 记录最大等待时间，默认没有等待

        for (int x : arrivalTime) {  // 逐个到达时刻计算等待时间
            int r = x % period;  // 该时刻在同步信号灯周期内的相位

            if (r >= mx) {  // 相位不早于 mx，说明本周期已无法通行，需要等下一个周期
                ans = max(ans, period - r);  // 等待时间为 period - r，用它更新最大值
            }  // 结束条件分支
        }  // 结束到达时刻遍历

        return ans;  // 返回最大等待时间
    }  // 结束函数
};  // 结束类定义