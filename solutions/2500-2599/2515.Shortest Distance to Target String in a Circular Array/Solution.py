# 题目：2515. 到目标字符串的最短距离（Shortest Distance to Target String in a Circular Array）
# 思路：枚举所有等于 target 的下标，环形数组上两点距离为 min(|i-start|, n-|i-start|)，取所有候选中的最小值。
# 时间复杂度：O(n)，一遍遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:  # words 为环形数组，target 是目标串，startIndex 是起点
        n = len(words)  # 环形数组长度
        ans = n  # 初值取最大可能距离 n，同时充当「未找到」的哨兵
        for i, w in enumerate(words):  # 同时取得下标 i 与字符串 w
            if w == target:  # 找到与目标串相等的位置
                t = abs(i - startIndex)  # 两个下标差的绝对值
                ans = min(ans, t, n - t)  # 取原答案、正向距离、反向绕行距离中的最小值
        return -1 if ans == n else ans  # 从未更新说明目标串不存在，返回 -1；否则返回最短距离
