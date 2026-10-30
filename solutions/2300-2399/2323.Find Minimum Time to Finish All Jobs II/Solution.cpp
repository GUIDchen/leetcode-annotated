// 题目：2323. 完成所有工作的最短时间 II（Find Minimum Time to Finish All Jobs II）
// 核心思路：排序后按「小活配产能小的工人」一一配对，每人所需天数为 jobs[i] / workers[i] 向上取整，答案取最大值。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，除排序内部开销外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTime(vector<int>& jobs, vector<int>& workers) {  // jobs：各工作耗时；workers：各工人每天能完成的工作量
        ranges::sort(jobs);  // 工作按耗时升序排列
        ranges::sort(workers);  // 工人按产能升序排列
        int ans = 0;  // 答案：所有工人完成各自工作的最晚时间
        int n = jobs.size();  // 工作数量（与工人数量相同）
        for (int i = 0; i < n; ++i) {  // 按排序后的顺序一一配对
            ans = max(ans, (jobs[i] + workers[i] - 1) / workers[i]);  // 向上取整求这位工人所需天数，并用最大值更新答案
        }  // 结束配对循环
        return ans;  // 返回最短完成时间
    }
};
