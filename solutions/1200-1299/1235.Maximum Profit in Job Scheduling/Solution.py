# 题目：1235. 规划兼职工作（Maximum Profit in Job Scheduling）
# 思路：把工作按开始时间排序后记忆化搜索，dfs(i) 取「跳过第 i 份」与「做第 i 份再接二分找出的 j」中的较大收益。
# 时间复杂度：O(n log n)，排序加每个状态一次二分；空间复杂度：O(n)，缓存与工作列表。
class Solution:  # LeetCode 约定的题解类
    def jobScheduling(  # 三组数组分别给出开始时间、结束时间与收益，返回最大总收益
        self, startTime: List[int], endTime: List[int], profit: List[int]  # 参数继续换行书写（仍在括号内，语法合法）
    ) -> int:  # 返回能取得的最大总收益
        @cache  # 装饰器 @cache：自动缓存 dfs 结果，等价于记忆化搜索
        def dfs(i):  # dfs(i)：从第 i 份工作开始能取得的最大收益（jobs、n 在调用前已赋值）
            if i >= n:  # 越界说明没有工作可选
                return 0  # 没有工作可做时收益为 0
            _, e, p = jobs[i]  # 解构出结束时间 e 与收益 p，开始时间用不到
            j = bisect_left(jobs, e, lo=i + 1, key=lambda x: x[0])  # 二分找第一个开始时间 >= e 的工作下标（key 只看第 0 项）
            return max(dfs(i + 1), p + dfs(j))  # 跳过第 i 份 与 做第 i 份再接上 j 之后，取较大值

        jobs = sorted(zip(startTime, endTime, profit))  # 把三数组合并成 (开始, 结束, 收益) 并按开始时间排序
        n = len(profit)  # 工作数量
        return dfs(0)  # 从第一份工作开始规划
