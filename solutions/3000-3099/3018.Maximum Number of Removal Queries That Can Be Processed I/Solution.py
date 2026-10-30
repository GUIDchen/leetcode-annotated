# 题目：3018. 可处理的最大删除操作数 I（Maximum Number of Removal Queries That Can Be Processed I）
# 思路：每次只能删数组两端，所以已删部分必是「前缀 + 后缀」，剩余部分始终是一段区间 [i, j]。用 f[i][j] 表示已删掉 nums[0..i-1] 与 nums[j+1..n-1] 时最多处理了多少个查询，由大区间递推到小区间，最后枚举唯一剩下的元素收尾取最大值。
# 时间复杂度：O(n²)，共 n² 个区间状态、每个 O(1) 转移；空间复杂度：O(n²)，需要一张 n×n 的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maximumProcessableQueries(self, nums: List[int], queries: List[int]) -> int:  # nums 是可删除的数组，queries 是按顺序到来的查询值，返回能处理的最多查询数
        n = len(nums)  # n：数组长度
        f = [[0] * n for _ in range(n)]  # f[i][j]：已删掉前缀 nums[0..i-1] 与后缀 nums[j+1..n-1] 时最多已处理的查询数，初值全为 0
        m = len(queries)  # m：查询总数，也是答案的上限
        for i in range(n):  # 按左端点 i 从小到大枚举剩余区间（i 即已删掉的前缀长度）
            for j in range(n - 1, i - 1, -1):  # 右端点 j 从 n-1 递减到 i，只枚举合法的非空区间 [i, j]
                if i:  # i 非 0 才有「刚删掉 nums[i-1]」这条转移路径
                    f[i][j] = max(  # 从 f[i-1][j] 转移，max 调用开始
                        f[i][j], f[i - 1][j] + (nums[i - 1] >= queries[f[i - 1][j]])  # 若刚删掉的 nums[i-1] 不小于待处理查询 queries[f[i-1][j]]，处理数就 +1
                    )  # max(...) 调用结束
                if j + 1 < n:  # j+1 < n 才有「刚删掉 nums[j+1]」这条转移路径
                    f[i][j] = max(  # 从 f[i][j+1] 转移，max 调用开始
                        f[i][j], f[i][j + 1] + (nums[j + 1] >= queries[f[i][j + 1]])  # 同理，nums[j+1] 够大就能多处理一个查询
                    )  # max(...) 调用结束
                if f[i][j] == m:  # 已经处理完全部 m 个查询，不可能更优，立刻返回
                    return m  # 返回上限 m
        return max(f[i][i] + (nums[i] >= queries[f[i][i]]) for i in range(n))  # 枚举最后唯一剩下的元素 nums[i]：再删它一次，够大就再 +1，对所有 i 取最大值
