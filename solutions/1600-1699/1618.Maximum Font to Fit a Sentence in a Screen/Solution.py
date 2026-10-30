# 题目：1618. 找出适应屏幕的最大字号（Maximum Font to Fit a Sentence in a Screen）
# 思路：字号可行与否具有单调性（越大越放不下），于是在有序的 fonts 上二分，用上取整中点逼近最后一个可行下标。
# 时间复杂度：O(k log m)，k 为句子长度、m 为可选字号数；空间复杂度：O(1)，只用常数个变量。
# """
# This is FontInfo's API interface.
# You should not implement it, or speculate about its implementation
# """
# class FontInfo(object):
#    Return the width of char ch when fontSize is used.
#    def getWidth(self, fontSize, ch):
#        """
#        :type fontSize: int
#        :type ch: char
#        :rtype int
#        """
#
#    def getHeight(self, fontSize):
#        """
#        :type fontSize: int
#        :rtype int
#        """
class Solution:  # LeetCode 约定的题解类
    def maxFont(  # 返回能放下的最大字号，都放不下则返回 -1
        self, text: str, w: int, h: int, fonts: List[int], fontInfo: 'FontInfo'  # text：句子；w/h：宽高上限；fonts：递增的可选字号；fontInfo：度量接口
    ) -> int:  # 返回类型标注：最大字号
        def check(size):  # 判断字号 size 能否把整句放进屏幕
            if fontInfo.getHeight(size) > h:  # 高度超标直接判负
                return False  # 放不下，提前返回
            return sum(fontInfo.getWidth(size, c) for c in text) <= w  # 逐字符宽度求和，不超过屏幕宽度才算放得下

        left, right = 0, len(fonts) - 1  # 二分的闭区间：答案一定落在 [left, right] 内
        ans = -1  # 预留的答案变量（本解法最终直接返回二分结果，未使用它）
        while left < right:  # 区间未收敛就继续二分
            mid = (left + right + 1) >> 1  # 上取整中点，避免 left/right 相邻时死循环
            if check(fonts[mid]):  # 该字号可行，答案至少是 mid
                left = mid  # 收缩左边界到 mid
            else:  # 该字号太大了
                right = mid - 1  # 收缩右边界到 mid 的前一个位置
        return fonts[left] if check(fonts[left]) else -1  # 收敛点可行就返回该字号，否则一个都放不下返回 -1
