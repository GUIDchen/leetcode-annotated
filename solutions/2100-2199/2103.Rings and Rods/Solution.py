# 题目：2103. 环和杆（Rings and Rods）
# 思路：红/绿/蓝编码成 1/2/4 三个二进制位，按杆号把颜色位或起来，最后统计掩码等于 7 的杆数。
# 时间复杂度：O(n)，一次扫描字符串；空间复杂度：O(1)，固定 10 根杆的掩码列表。
class Solution:  # LeetCode 约定的题解类
    def countPoints(self, rings: str) -> int:  # rings 形如 "R0G1B2"，返回三色齐全的杆数
        mask = [0] * 10  # 每根杆的颜色掩码，下标就是杆号 0~9
        d = {"R": 1, "G": 2, "B": 4}  # 颜色到二进制位的映射：红 1、绿 2、蓝 4
        for i in range(0, len(rings), 2):  # 步长为 2，每次读入一个「颜色 + 杆号」
            c = rings[i]  # 当前环的颜色字符
            j = int(rings[i + 1])  # 当前环所在杆号，转成整数
            mask[j] |= d[c]  # 把这种颜色对应的位并入该杆掩码
        return mask.count(7)  # 统计掩码等于 7（三色齐全）的杆数
