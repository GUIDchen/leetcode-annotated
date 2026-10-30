# 题目：414. 第三大的数（Third Maximum Number）
# 思路：用 m1、m2、m3 记录互不相同的前三大，遇重复值跳过；若凑不齐三个就返回最大值。
# 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，只用三个滚动变量。
class Solution:  # LeetCode 约定的题解类
    def thirdMax(self, nums: List[int]) -> int:  # 返回不同值中第三大的数，不足三个则返回最大值
        m1 = m2 = m3 = -inf  # 用负无穷初始化第一大、第二大、第三大
        for num in nums:  # 遍历数组中的每个数
            if num in [m1, m2, m3]:  # 与已记录的值重复就跳过，保证严格不同
                continue  # 跳过重复值
            if num > m1:  # 比最大值还大，三者整体下移
                m3, m2, m1 = m2, m1, num  # 右侧同时赋值：原第二大→第三大，原最大→第二大，新数→最大
            elif num > m2:  # 落在最大值与第二大之间
                m3, m2 = m2, num  # 原第二大→第三大，新数→第二大
            elif num > m3:  # 落在第二大与第三大之间
                m3 = num  # 更新第三大
        return m3 if m3 != -inf else m1  # 凑不齐第三大时按题意返回最大值
