// 4068. 考虑空闲时间的会议最大收益  Maximize Meeting Earnings with Idle Gaps
// 核心思路：按结束时间排序后做 DP，preMax 记录“收益-结束时间”的前缀最大值，空闲时长可作为额外收益计入。
// 复杂度：时间 O(n log n)，空间 O(n)。

class Solution {
public:
    long long maxEarnings(vector<vector<int>>& meetings) {  // 返回可获得的最大总收益
        int n = meetings.size();  // 会议数量
        sort(meetings.begin(), meetings.end(), [](auto& a, auto& b) {  // 按会议结束时间升序排序
            return a[1] < b[1];  // 结束早的排在前面
        });

        vector<long long> preMax(n + 1, LLONG_MIN / 2);  // preMax[i] 表示前 i 场会议中“收益-结束时间”的最大值
        long long ans = 0;  // 记录最大总收益

        for (int i = 0; i < n; i++) {  // 依次把第 i 场会议作为最后一场
            int start = meetings[i][0];  // 当前会议的起始时间
            int end = meetings[i][1];  // 当前会议的结束时间
            int revenue = meetings[i][2];  // 当前会议的收益

            long long val = revenue;  // 只选当前会议时的收益
            if (start >= meetings[0][1]) {  // 起始时间不早于最早结束的会议，说明可能存在可衔接的前驱
                int j = upper_bound(meetings.begin(), meetings.begin() + i, start,  // 在前 i 场中二分查找可用前驱
                            [](int x, const vector<int>& y) {  // 比较函数：用会议的结束时间与 x 比较
                                return x < y[1];  // 结束时间小于 x 视为更小
                            })
                    - meetings.begin();  // 减去起始迭代器得到前驱数量
                val += preMax[j] + start;  // 前驱最优收益加上这段空闲时长带来的收益
            }

            ans = max(ans, val);  // 更新最大总收益
            preMax[i + 1] = max(preMax[i], val - end);  // 递推前缀最大值，扣除结束时间供后续衔接使用
        }

        return ans;  // 返回最大总收益
    }
};