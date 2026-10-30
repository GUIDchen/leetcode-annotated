# 题目：2271. 毯子覆盖的最多白色砖块数（Maximum White Tiles Covered by a Carpet）
# 思路：把区间按起点排序，用双指针滑动窗口：i 是毯子左端所在区间、j 是窗口右边界，s 记录窗口内完整区间的砖数和，毯子若伸入下一区间再补上部分覆盖的砖数，过程中取最大值。
# 时间复杂度：O(n log n)，排序主导，双指针各自只前进一次；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumWhiteTiles(self, tiles: List[List[int]], carpetLen: int) -> int:  # tiles：若干 [起点, 终点] 区间；carpetLen：毯子长度
        tiles.sort()  # 按区间起点升序排序，保证窗口内区间连续
        n = len(tiles)  # 区间个数
        s = ans = j = 0  # s：窗口内完整区间的砖数和；ans：历史最大值；j：窗口右边界
        for i, (li, ri) in enumerate(tiles):  # 枚举毯子左端所在的区间 i，同时取出该区间的左右端点
            while j < n and tiles[j][1] - li + 1 <= carpetLen:  # 区间 j 能被毯子完整覆盖时，把它的砖数计入窗口
                s += tiles[j][1] - tiles[j][0] + 1  # 该区间砖块数 = 终点 - 起点 + 1
                j += 1  # 右边界右移，尝试纳入下一个区间
            if j < n and li + carpetLen > tiles[j][0]:  # 毯子右端伸入下一区间内部，只能部分覆盖
                ans = max(ans, s + li + carpetLen - tiles[j][0])  # 完整区间砖数加部分覆盖的砖数（毯子右端 - 该区间起点）
            else:  # 毯子右端没有触及下一区间
                ans = max(ans, s)  # 只能取完整覆盖区间的砖数
            s -= ri - li + 1  # 把区间 i 移出窗口，为左边界右移做准备
        return ans  # 返回最多能覆盖的白砖块数
