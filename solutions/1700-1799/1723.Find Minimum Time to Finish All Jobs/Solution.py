# 题目：1723. 完成所有工作的最短时间（Find Minimum Time to Finish All Jobs）难度：困难
# 思路：把工作从大到小排序后做 DFS 回溯，把每件工作分给 k 个工人之一，用 cnt 记录每个工人的当前负载；
# 剪枝：若分给某工人后负载不小于当前最优解就跳过；某工人负载为 0 时只需尝试一次（工人之间等价），分配到空工人后立即 break。
# 时间复杂度：O(k^n) 的最坏回溯（排序与剪枝大幅减少搜索），n 为工作数；空间复杂度：O(n + k)，递归栈与负载数组。
class Solution:  # LeetCode 约定的题解类
    def minimumTimeRequired(self, jobs: List[int], k: int) -> int:  # jobs：每件工作的耗时；k：工人数
        def dfs(i):  # i：当前待安排的工作下标
            nonlocal ans  # 声明要修改外层的最优解变量
            if i == len(jobs):  # 所有工作都分配完了
                ans = min(ans, max(cnt))  # 完工时间取所有工人的最大负载，更新最优解
                return  # 回溯
            for j in range(k):  # 依次尝试把当前工作交给第 j 个工人
                if cnt[j] + jobs[i] >= ans:  # 剪枝：这样分配不会优于已知最优解
                    continue  # 直接跳过这个工人
                cnt[j] += jobs[i]  # 把工作分给第 j 个工人，累加负载
                dfs(i + 1)  # 递归安排下一件工作
                cnt[j] -= jobs[i]  # 撤销选择，恢复负载（回溯）
                if cnt[j] == 0:  # 剪枝：工人负载为 0 说明这些工人完全等价
                    break  # 只需尝试一次，后续空工人无需再试

        cnt = [0] * k  # cnt[j]：第 j 个工人当前的负载
        jobs.sort(reverse=True)  # 从大到小排序：先安排耗时长的，剪枝更早生效
        ans = inf  # 用一个无穷大值作为初始最优解
        dfs(0)  # 从第 0 件工作开始搜索分配方案
        return ans  # 返回搜索到的最短完工时间
