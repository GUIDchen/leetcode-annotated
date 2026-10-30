// 题目：239. 滑动窗口最大值（Sliding Window Maximum）
// 思路：大根堆里存 (数值, -下标)，堆顶永远候选窗口最大值；取堆顶前用下标把已经滑出窗口的堆顶弹出。
// 时间复杂度：O(n log n)，每个元素至多入堆、出堆各一次；空间复杂度：O(n)，堆中最多同时保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {  // nums：输入数组；k：窗口大小
        priority_queue<pair<int, int>> q;  // 大根堆，元素是 (数值, -下标)：先比数值，值相同时小下标优先
        int n = nums.size();  // 数组长度
        for (int i = 0; i < k - 1; ++i) {  // 先把第一个窗口里除最右位置以外的元素全部入堆
            q.push({nums[i], -i});  // 下标取相反数存入，之后用 -second 即可还原真实下标
        }
        vector<int> ans;  // 保存每个窗口的最大值
        for (int i = k - 1; i < n; ++i) {  // 窗口右端从 k-1 开始，逐格右滑到数组末尾
            q.push({nums[i], -i});  // 新进入窗口的元素入堆
            while (-q.top().second <= i - k) {  // 堆顶下标早于窗口左边界 i-k+1，说明它已经滑出窗口
                q.pop();  // 弹出过期的堆顶，直到堆顶属于当前窗口
            }
            ans.emplace_back(q.top().first);  // 此时堆顶就是当前窗口的最大值
        }
        return ans;  // 返回所有窗口的最大值
    }
};