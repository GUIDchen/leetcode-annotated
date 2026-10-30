# 题目：744. 寻找比目标字母大的最小字母（Find Smallest Letter Greater Than Target）
# 核心思路：letters 已经升序，用 bisect_right 二分出第一个严格大于 target 的位置，取模让越界时绕回首字母。
# 时间复杂度：O(log n)，一次二分查找；空间复杂度：O(1)，只用了一个下标变量。
class Solution:  # LeetCode 约定的题解类
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:  # letters 是升序字母表，target 是要比较的目标字母
        i = bisect_right(letters, ord(target), key=lambda c: ord(c))  # 按 ASCII 值二分，找到第一个大于 target 的位置；key 让比较统一走 ord，避免字符与整数直接比较
        return letters[i % len(letters)]  # 下标越界（没有更大字母）时取模绕回首字母
