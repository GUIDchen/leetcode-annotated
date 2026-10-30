// 题目：2054. 两个最好的不重叠活动（Two Best Non-Overlapping Events）
// 思路：按开始时间排序后预处理后缀最大价值 f；枚举第一个活动，二分找第一个开始时间严格大于其结束时间的活动，用 f 取第二个活动的最优值。
// 时间复杂度：O(n log n)，排序加每个活动一次二分；空间复杂度：O(n)，后缀最大值数组。
class Solution {  // 题解类
public:  // 对外接口
    int maxTwoEvents(vector<vector<int>>& events) {  // events[i] = {开始, 结束, 价值}，返回最多参加两个不重叠活动的最大价值和
        ranges::sort(events);  // 按开始时间升序排序（C++20 ranges 版）
        int n = events.size();  // 活动个数
        vector<int> f(n + 1);  // f[i] 表示从第 i 个活动开始到末尾的最大价值
        for (int i = n - 1; ~i; --i) {  // 从后往前递推后缀最大值；~i 等价于 i >= 0
            f[i] = max(f[i + 1], events[i][2]);  // 不选第 i 个（f[i+1]）或选它（events[i][2]），取较大者
        }  // 后缀最大值计算结束
        int ans = 0;  // 答案至少为 0
        for (const auto& e : events) {  // 枚举作为第一个活动的 e
            int v = e[2];  // v 累积当前活动的价值
            int left = 0, right = n;  // 在 [0, n] 内二分，找第一个开始时间晚于 e 结束时间的活动
            while (left < right) {  // 标准左闭右开二分
                int mid = (left + right) >> 1;  // 取中点（右移一位等价于除以 2）
                if (events[mid][0] > e[1]) {  // 中点活动开始时间严格大于当前结束时间，说明可以接在后面
                    right = mid;  // 收缩右边界
                } else {  // 否则中点活动与当前活动重叠
                    left = mid + 1;  // 收缩左边界
                }  // 分支结束
            }  // 二分结束
            if (left < n) {  // 确实存在可以接的第二个活动
                v += f[left];  // 叠加后缀最大价值
            }  // 判断结束
            ans = max(ans, v);  // 尝试更新答案
        }  // 第一个活动枚举结束
        return ans;  // 返回最多两个活动的最大价值和
    }  // 方法结束
};  // 类定义结束
