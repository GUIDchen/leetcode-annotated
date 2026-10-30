# 题目：942. 增减字符串匹配（DI String Match）
# 思路：双指针维护可选数字区间 [low, high]，遇到 'I' 取最小值、遇到 'D' 取最大值，最后剩下的数字追加到末尾。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，答案列表长度为 n+1。
class Solution:  # LeetCode 约定的题解类
    def diStringMatch(self, s: str) -> List[int]:  # s 是由 'I'/'D' 组成的字符串，返回满足关系的 0..n 排列
        low, high = 0, len(s)  # 可选数字区间 [low, high]，恰好覆盖 0..len(s)
        ans = []  # 答案列表，边遍历边追加
        for c in s:  # 逐个处理趋势字符
            if c == "I":  # 'I' 表示下一个数要更大
                ans.append(low)  # 填当前最小值，剩余数字都比它大
                low += 1  # 最小值右移，缩小可选区间
            else:  # 否则是 'D'，下一个数要更小
                ans.append(high)  # 填当前最大值，剩余数字都比它小
                high -= 1  # 最大值左移，缩小可选区间
        ans.append(low)  # 最后只剩一个数字，追加到末尾
        return ans  # 返回构造好的排列
