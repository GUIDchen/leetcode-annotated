// 题目：862. 和至少为 K 的最短子数组（Shortest Subarray with Sum at Least K）
// 思路：前缀和 + 单调队列。子数组和化为两个前缀和之差，队列中前缀和保持单调递增；队首满足差值 ≥ k 时立即更新答案并弹出。
// 时间复杂度：O(n)，每个下标至多入队、出队各一次；空间复杂度：O(n)，前缀和数组与双端队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestSubarray(vector<int>& nums, int k) {  // nums：可能含负数的数组；k：目标和；返回和 ≥ k 的最短非空子数组长度
        int n = nums.size();  // 数组长度
        vector<long> s(n + 1);  // 前缀和数组：s[i] 表示前 i 个元素之和，用 long 防止累加溢出
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + nums[i];  // 递推计算每个前缀和，公差为 nums[i]
        deque<int> q;  // 单调队列：存下标，其对应的前缀和从队首到队尾严格递增
        int ans = n + 1;  // 答案初值取不可能达到的 n+1，方便最后判断无解
        for (int i = 0; i <= n; ++i) {  // 枚举每个前缀和下标作为子数组的右端点（含 0 表示空前缀）
            while (!q.empty() && s[i] - s[q.front()] >= k) {  // 队首前缀和与当前前缀和之差 ≥ k 时，找到了一个合法子数组
                ans = min(ans, i - q.front());  // 用当前区间长度更新答案
                q.pop_front();  // 同一队首再往后只会更长，直接弹出，不会错过更优解
            }  // 内层 while 结束
            while (!q.empty() && s[q.back()] >= s[i]) q.pop_back();  // 维护队列的单调性：队尾前缀和不小于当前值时它不可能再给出更短区间，弹出
            q.push_back(i);  // 把当前下标入队，作为后续右端点的候选左端点
        }  // 外层 for 结束
        return ans > n ? -1 : ans;  // 答案仍为初值说明没有合法子数组，返回 -1
    }  // shortestSubarray 方法结束
};  // Solution 类定义结束