# 题目：368. 最大整除子集（Largest Divisible Subset）
# 思路：先排序，f[i] 表示以 nums[i] 结尾的最大整除子集长度，用 j < i 且 nums[i] % nums[j] == 0 转移；再从最长位置 k 向前回溯还原元素。
# 时间复杂度：O(n^2)，双重循环 + O(n) 回溯；空间复杂度：O(n)，f 数组与答案数组。
class Solution:  # LeetCode 约定的题解类
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:  # nums 是输入整数集合，返回其中最大的整除子集
        nums.sort()  # 升序排序，保证整除关系只需从较小元素推到较大元素
        n = len(nums)  # 元素个数
        f = [1] * n  # f[i] 表示以 nums[i] 结尾的最大整除子集长度，初始都为 1
        k = 0  # k 记录当前 f 值最大的位置，即答案的末尾
        for i in range(n):  # 逐个把 nums[i] 当作子集的最后一个元素
            for j in range(i):  # 枚举所有更小的前驱 nums[j]
                if nums[i] % nums[j] == 0:  # nums[i] 能被 nums[j] 整除才满足子集约束
                    f[i] = max(f[i], f[j] + 1)  # 把 nums[i] 接到以 j 结尾的最优子集之后
            if f[k] < f[i]:  # 若当前位置刷新了最长长度
                k = i  # 同步更新最大值位置 k
        m = f[k]  # 目标答案的长度
        i = k  # 从最长末尾开始向前回溯
        ans = []  # 收集结果
        while m:  # 直到把 m 个元素全部补全
            if nums[k] % nums[i] == 0 and f[i] == m:  # 只取既能整除 nums[k] 又长度正好为 m 的前驱
                ans.append(nums[i])  # 该元素属于答案
                k, m = i, m - 1  # 把 k 移到 i，并把剩余待补长度减一
            i -= 1  # 指针统一向前移动一格
        return ans  # 返回最大整除子集
