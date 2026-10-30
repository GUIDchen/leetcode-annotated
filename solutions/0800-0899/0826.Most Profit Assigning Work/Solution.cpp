// 题目：826. 安排工作以达到最大收益（Most Profit Assigning Work）
// 思路：贪心。工人按能力升序、工作按难度升序后，用不回退的指针把「难度不超过当前工人」的工作依次纳入候选，并维护候选中的最大收益，每个工人直接领这个最大值。
// 时间复杂度：O(n log n + m log m)，来自排序工作与排序工人；空间复杂度：O(n)，额外的 jobs 数组存工作对。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {  // difficulty/profit：每项工作的难度与收益；worker：每个工人的能力；返回最大总收益
        sort(worker.begin(), worker.end());  // 工人按能力升序，这样能力大的工人一定覆盖前面工人能做的工作
        int n = profit.size();  // 工作数量
        vector<pair<int, int>> jobs;  // 把「难度, 收益」配成 pair，方便一起排序
        for (int i = 0; i < n; ++i) {  // 逐项工作打包成 pair
            jobs.emplace_back(difficulty[i], profit[i]);  // 按顺序把难度与收益放进 jobs
        }  // 结束打包
        sort(jobs.begin(), jobs.end());  // 按难度升序排序，便于后面用指针单调扫描
        int ans = 0, mx = 0, i = 0;  // ans：总收益；mx：当前能力下能拿到的最大单项收益；i：工作指针
        for (int w : worker) {  // 按能力从小到大处理每个工人
            while (i < n && jobs[i].first <= w) {  // 把难度不超过当前工人能力的工作全部纳入候选（i 只前进不回退，整体摊销 O(n)）
                mx = max(mx, jobs[i++].second);  // 用候选工作里的最大收益更新 mx，并让 i 后移
            }  // 结束候选扫描
            ans += mx;  // 当前工人取 mx 即是他能创造的最大收益；无工作可做时 mx 为 0，加 0 无害
        }  // 结束工人循环
        return ans;  // 返回总收益
    }  // 结束方法
};  // 结束类