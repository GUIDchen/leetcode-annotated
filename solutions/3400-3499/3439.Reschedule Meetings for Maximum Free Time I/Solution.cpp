// 3439. 重新安排会议得到最多空余时间 I / Reschedule Meetings for Maximum Free Time I
// 核心思路：把空闲时长抽成 n+1 段数组，连续 k+1 段空闲可用平移 k 场会议合并成一段，故用定长滑动窗口求最大和。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有方法
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {  // 最多平移 k 场会议，返回可获得的最大空余时间
        int n = endTime.size();  // 会议场数
        vector<int> nums(n + 1);  // nums[i] 为第 i 段空闲时长，共 n+1 段
        nums[0] = startTime[0];  // 首场会议之前的空闲
        for (int i = 1; i < n; ++i) {  // 枚举相邻会议之间的间隙
            nums[i] = startTime[i] - endTime[i - 1];  // 上一场结束到本场开始的空闲
        }  // 结束间隙计算
        nums[n] = eventTime - endTime[n - 1];  // 最后一场会议之后的空闲

        int ans = 0, s = 0;  // ans 为答案，s 为当前窗口内的空闲和
        for (int i = 0; i <= n; ++i) {  // 滑动窗口遍历所有空闲段
            s += nums[i];  // 右端元素加入窗口
            if (i >= k) {  // 窗口长度达到 k+1，说明这 k 场会议可被平移合并
                ans = max(ans, s);  // 用窗口和更新答案
                s -= nums[i - k];  // 左端元素移出窗口
            }  // 结束窗口收缩
        }  // 结束滑动窗口
        return ans;  // 返回最大空余时间
    }  // 结束 maxFreeTime 方法
};  // 结束 Solution 类
