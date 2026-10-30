// 题目：1235. 规划兼职工作（Maximum Profit in Job Scheduling）
// 思路：把工作按开始时间排序做记忆化搜索：dfs(i) 表示从第 i 份工作起的最大收益，二分出与第 i 份不冲突的下一份工作 j，取「跳过」与「做 i 再接 j」的较大值。
// 时间复杂度：O(n log n)，排序加每个状态一次二分；空间复杂度：O(n)，记忆化数组与三元组数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {  // 三个数组分别给出开始时间、结束时间与收益，返回最大总收益
        int n = profit.size();  // 工作数量
        vector<tuple<int, int, int>> jobs(n);  // 把每份工作打包成 (开始, 结束, 收益) 三元组
        for (int i = 0; i < n; ++i) jobs[i] = {startTime[i], endTime[i], profit[i]};  // 逐个填入三元组
        sort(jobs.begin(), jobs.end());  // 按开始时间升序排序，便于二分查找下一份可接的工作
        vector<int> f(n);  // 记忆化数组：f[i] 表示从第 i 份工作开始能取得的最大收益
        function<int(int)> dfs = [&](int i) -> int {  // 递归函数：考虑从下标 i 开始的工作（按引用捕获外部变量）
            if (i >= n) return 0;  // 没有工作可选，收益为 0
            if (f[i]) return f[i];  // 已经计算过就直接返回（记忆化，0 表示未计算）
            auto [_, e, p] = jobs[i];  // 解构出结束时间 e 与收益 p，开始时间用不到
            tuple<int, int, int> t{e, 0, 0};  // 构造查找键：开始时间取 e，表示只要开始时间 >= e 就不冲突
            int j = lower_bound(jobs.begin() + i + 1, jobs.end(), t, [&](auto& l, auto& r) -> bool { return get<0>(l) < get<0>(r); }) - jobs.begin();  // 在 i+1 之后二分第一个开始时间 >= e 的工作下标 j（比较器只比较第 0 项）
            int ans = max(dfs(i + 1), p + dfs(j));  // 跳过第 i 份 与 做第 i 份再接 j 之后，取收益较大者
            f[i] = ans;  // 记录本状态答案，避免重复计算
            return ans;  // 返回本次结果
        };  // lambda 结束
        return dfs(0);  // 从第一份工作开始规划
    }  // 方法结束
};  // 类定义结束
