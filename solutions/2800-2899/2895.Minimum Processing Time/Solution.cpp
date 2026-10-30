// 题目：2895. 最小处理时间（Minimum Processing Time）
// 思路：处理器时间与任务时间都升序排序，最早空闲的处理器领走当前最长的 4 个任务中的最大值，贪心使完成时间的最大值最小。
// 时间复杂度：O(n log n + m log m)，开销来自两次排序；空间复杂度：O(log n + log m)，排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) {  // processorTime：各处理器开始时间；tasks：任务耗时
        sort(processorTime.begin(), processorTime.end());  // 处理器时间升序，最先空闲的排在最前
        sort(tasks.begin(), tasks.end());  // 任务时间升序，最长的任务排在最后
        int ans = 0, i = tasks.size() - 1;  // ans：完成时间上界；i：当前最长任务的下标，从末尾开始
        for (int t : processorTime) {  // 按处理器时间从小到大依次分配
            ans = max(ans, t + tasks[i]);  // 该处理器承担 4 个任务中最长的一个，更新完成时间上界
            i -= 4;  // 一个处理器一次处理 4 个任务，任务下标前移 4 位
        }  // 返回所有任务完成所需的最小时间
        return ans;
    }
};