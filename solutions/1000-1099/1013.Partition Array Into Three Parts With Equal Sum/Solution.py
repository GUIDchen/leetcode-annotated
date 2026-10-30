# 题目：1013. 将数组分成和相等的三个部分（Partition Array Into Three Parts With Equal Sum）
# 思路：三段和相等必然等于总和的三分之一，所以总和必须能被 3 整除；随后顺序累加，每凑满目标和就切走一段，切出至少 3 段即满足。
# 时间复杂度：O(n)，求总和加一次遍历；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:  # arr：待划分的整数数组
        s, mod = divmod(sum(arr), 3)  # 同时得到「每段的目标和」与「总和除以 3 的余数」
        if mod:  # 余数不为 0 说明总和不能被 3 整除
            return False  # 不可能三等分
        cnt = t = 0  # cnt 已切出的段数，t 当前段正在累加的和
        for x in arr:  # 顺序遍历每个元素
            t += x  # 把当前元素累加到当前段
            if t == s:  # 当前段恰好凑够目标和，就把它切走
                cnt += 1  # 段数加一
                t = 0  # 清零，重新开始累计下一段
        return cnt >= 3  # 能切出至少 3 段（剩余部分和为 0）即可三等分
