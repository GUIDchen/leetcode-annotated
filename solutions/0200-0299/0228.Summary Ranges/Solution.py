# 题目：228. 汇总区间（Summary Ranges）
# 思路：双指针。i 指向当前区间起点，j 向右扩展到不再连续为止，把 [i, j] 拼成一个区间字符串，再令 i = j + 1 处理下一段。
# 时间复杂度：O(n)，每个下标只被扫一次；空间复杂度：O(1)，除返回列表外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def summaryRanges(self, nums: List[int]) -> List[str]:  # nums 是升序且可能含重复值的数组，返回其中连续区间的字符串表示
        def f(i: int, j: int) -> str:  # 内部辅助函数：把闭区间 [i, j] 格式化成题目要求的字符串
            return str(nums[i]) if i == j else f'{nums[i]}->{nums[j]}'  # 单个元素只写自己；多个元素写成 起点->终点

        i = 0  # i 是当前区间起点
        n = len(nums)  # n 是数组长度，先缓存避免重复求 len
        ans = []  # 保存所有区间字符串，最终按顺序返回
        while i < n:  # 从数组开头开始扫描，直到所有元素都被归入某个区间
            j = i  # 区间先从单点 i 开始
            while j + 1 < n and nums[j + 1] == nums[j] + 1:  # 只要下一个数恰好比当前数大 1，区间就能继续向右延伸
                j += 1  # 区间终点右移一格
            ans.append(f(i, j))  # 把 [i, j] 格式化后追加到答案
            i = j + 1  # 下一段的起点跳到 j 的下一位
        return ans  # 返回所有区间字符串
