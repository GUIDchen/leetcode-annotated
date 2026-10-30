# 题目：2670. 找出不同元素数目差数组（Find the Distinct Difference Array）
# 核心思路：先从右往左预处理后缀不同元素个数 suf[i]，再用一个集合从左往右维护前缀不同元素个数，两者相减即为每个位置的答案。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，后缀数组与集合。
class Solution:  # LeetCode 约定的题解类
    def distinctDifferenceArray(self, nums: List[int]) -> List[int]:  # nums：输入数组，返回每个下标的「前缀不同数 - 后缀不同数」结果数组
        n = len(nums)  # 数组长度
        suf = [0] * (n + 1)  # suf[i]：nums[i..n-1] 后缀中不同元素个数，多开一位让空后缀取到 0
        s = set()  # 集合：统计当前后缀里出现过的不同元素
        for i in range(n - 1, -1, -1):  # 从右往左扫描，逐步形成后缀
            s.add(nums[i])  # 把当前元素加入集合（重复元素不会改变集合大小）
            suf[i] = len(s)  # 记录从 i 开始的后缀的不同元素个数
        s.clear()  # 清空集合，改为前缀统计复用
        ans = [0] * n  # 答案数组，长度与原数组相同
        for i, x in enumerate(nums):  # 从左往右扫描，同时取得下标 i 与元素 x
            s.add(x)  # 把当前元素加入前缀集合
            ans[i] = len(s) - suf[i + 1]  # 前缀不同数减去后缀 nums[i+1..] 的不同数，即为该位置的差
        return ans  # 返回算好的差数组
