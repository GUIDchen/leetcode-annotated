# 题目：1769. 移动所有球到每个盒子所需的最小操作数（Minimum Number of Operations to Move All Balls to Each Box）
# 思路：前后缀递推。left[i] 记录 i 左侧所有球移到 i 的代价，right[i] 记录右侧的代价，两者相加就是该盒子所需的最小操作数；扫描时用已出现的球数 cnt 做增量累加。
# 时间复杂度：O(n)，共三次线性扫描；空间复杂度：O(n)，left、right 两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, boxes: str) -> List[int]:  # boxes 是只含 '0'/'1' 的字符串，返回每个盒子所需的最小操作数
        n = len(boxes)  # 盒子的个数
        left = [0] * n  # left[i] 表示把 i 左侧的所有球移到 i 所需的操作数，初始全为 0
        right = [0] * n  # right[i] 表示把 i 右侧的所有球移到 i 所需的操作数，初始全为 0
        cnt = 0  # cnt 记录左侧已经出现的球数
        for i in range(1, n):  # 从左往右扫描区间 [1, n)
            if boxes[i - 1] == '1':  # 上一个盒子里有球
                cnt += 1  # 左侧球数加一
            left[i] = left[i - 1] + cnt  # 递推：左侧代价 = 左一格的代价 + 左侧球数（每个球都要多走一步）
        cnt = 0  # 重置球数，准备从右往左扫描
        for i in range(n - 2, -1, -1):  # 从右往左扫描区间 [n-2, 0]
            if boxes[i + 1] == '1':  # 下一个盒子里有球
                cnt += 1  # 右侧球数加一
            right[i] = right[i + 1] + cnt  # 递推：右侧代价 = 右一格的代价 + 右侧球数
        return [a + b for a, b in zip(left, right)]  # 把左右两侧代价按位相加，得到每个盒子的总操作数
