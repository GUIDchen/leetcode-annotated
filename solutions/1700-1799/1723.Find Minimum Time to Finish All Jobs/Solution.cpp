// 题目：1723. 完成所有工作的最短时间（Find Minimum Time to Finish All Jobs）难度：困难
// 思路：把工作从大到小排序后做 DFS 回溯，把每件工作分给 k 个工人之一，用 cnt 记录每个工人的当前负载；
// 剪枝：若分给某工人后负载不小于当前最优解就跳过；某工人负载为 0 时只需尝试一次（工人之间等价），分配到空工人后立即 break。
// 时间复杂度：O(k^n) 的最坏回溯（排序与剪枝大幅减少搜索），n 为工作数；空间复杂度：O(n + k)，递归栈与负载数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int ans;  // 全局最优解：所有工作完成的最短时间

    int minimumTimeRequired(vector<int>& jobs, int k) {  // jobs：每件工作的耗时；k：工人数
        vector<int> cnt(k);  // cnt[j]：第 j 个工人当前的负载（已完成工作的总耗时）
        ans = 0x3f3f3f3f;  // 用一个足够大的数（约 10.6 亿）作为初始最优解
        sort(jobs.begin(), jobs.end(), greater<int>());  // 从大到小排序：先安排耗时长的，剪枝更早生效
        dfs(0, k, jobs, cnt);  // 从第 0 件工作开始搜索分配方案
        return ans;  // 返回搜索到的最短完工时间
    }  // minimumTimeRequired 方法结束

    void dfs(int i, int k, vector<int>& jobs, vector<int>& cnt) {  // i：当前待安排的工作下标
        if (i == jobs.size()) {  // 所有工作都分配完了
            ans = min(ans, *max_element(cnt.begin(), cnt.end()));  // 完工时间取所有工人的最大负载，更新最优解
            return;  // 回溯
        }
        for (int j = 0; j < k; ++j) {  // 依次尝试把当前工作交给第 j 个工人
            if (cnt[j] + jobs[i] >= ans) continue;  // 剪枝：这样分配不会优于已知最优解，直接跳过
            cnt[j] += jobs[i];  // 把工作分给第 j 个工人，累加负载
            dfs(i + 1, k, jobs, cnt);  // 递归安排下一件工作
            cnt[j] -= jobs[i];  // 撤销选择，恢复负载（回溯）
            if (cnt[j] == 0) break;  // 剪枝：工人负载为 0 说明这些工人完全等价，只试一次即可
        }
    }  // dfs 方法结束
};  // Solution 类结束