// 3835. 开销小于等于 K 的子数组数目 / Count Subarrays With Cost Less Than or Equal to K（中等）
// 核心思路：滑动窗口 + 两个单调队列。q1 单调递减维护窗口最大值、q2 单调递增维护窗口最小值，代价 =(最大值-最小值)×长度；当代价超过 k 时右移左端点收缩，收缩后以 r 结尾的合法子数组有 r-l+1 个。
// 复杂度：每个下标最多进出队列一次，时间 O(n)，空间 O(n)。
class Solution {  // 统计代价不超过 k 的子数组个数
public:  // 对外接口区
    long long countSubarrays(vector<int>& nums, long long k) {  // 返回满足条件的子数组数目，结果与代价都可能很大，故用 long long
        long long ans = 0;  // 答案计数
        deque<int> q1, q2;  // q1 维护窗口最大值的下标（单调递减）；q2 维护窗口最小值的下标（单调递增）
        int l = 0;  // 滑动窗口的左端点

        for (int r = 0; r < nums.size(); r++) {  // 右端点从左到右扩展
            int x = nums[r];  // 当前考察的元素

            while (!q1.empty() && nums[q1.back()] <= x) {  // 把队列尾部所有不大于 x 的下标弹出，保持从队首到队尾递减
                q1.pop_back();  // 弹出被 x 击败的较小值
            }
            while (!q2.empty() && nums[q2.back()] >= x) {  // 把队列尾部所有不小于 x 的下标弹出，保持从队首到队尾递增
                q2.pop_back();  // 弹出被 x 击败的较大值
            }
            q1.push_back(r);  // 当前下标进入最大值队列
            q2.push_back(r);  // 当前下标进入最小值队列

            while (l < r && (long long) (nums[q1.front()] - nums[q2.front()]) * (r - l + 1) > k) {  // 当代价 (窗口最大值-窗口最小值)×窗口长度 超过 k 时收缩左端点
                l++;  // 左端点右移，窗口代价单调不增
                if (q1.front() < l) {  // 最大值队首下标已滑出窗口
                    q1.pop_front();  // 从队首弹出
                }
                if (q2.front() < l) {  // 最小值队首下标已滑出窗口
                    q2.pop_front();  // 从队首弹出
                }
            }

            ans += r - l + 1;  // 以 r 结尾、左端点取 l..r 的子数组都合法，共 r-l+1 个
        }
        return ans;  // 返回合法子数组总数
    }
};
