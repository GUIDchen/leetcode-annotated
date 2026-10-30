# 题目：3000. 对角线最长的矩形的面积（Maximum Area of Longest Diagonal Rectangle）
# 思路：对角线长度的平方就是 l² + w²，一次遍历找最大对角线；对角线等长时取面积更大的那个矩形。
# 时间复杂度：O(n)，只需遍历一遍矩形数组；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def areaOfMaxDiagonal(self, dimensions: List[List[int]]) -> int:  # dimensions：每项形如 [长, 宽]；返回对角线最长的矩形中面积的最大值
        ans = mx = 0  # ans：答案面积；mx：已经出现过的最长对角线长度的平方
        for l, w in dimensions:  # 逐个解包出矩形的长 l 与宽 w
            t = l**2 + w**2  # 对角线长度的平方；用平方比较可以避免开根号的精度问题
            if mx < t:  # 出现了更长的对角线
                mx = t  # 更新最长对角线的平方
                ans = l * w  # 答案改为该矩形的面积
            elif mx == t:  # 对角线等长，此时比较面积大小
                ans = max(ans, l * w)  # 保留两者中更大的面积
        return ans  # 返回最终求得的面积
