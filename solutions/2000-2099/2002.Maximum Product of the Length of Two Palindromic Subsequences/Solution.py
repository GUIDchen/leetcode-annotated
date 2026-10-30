# 题目：2002. 两个回文子序列长度的最大乘积（Maximum Product of the Length of Two Palindromic Subsequences）
# 思路：n ≤ 12，用二进制掩码枚举子集，先预处理哪些子集是回文，再对每个回文子集枚举其补集的全部子集，取两个不相交回文子集长度的最大乘积。
# 时间复杂度：O(3^n)，枚举补集的所有子集；空间复杂度：O(2^n)，存每个子集的回文标记。
class Solution:  # LeetCode 约定的题解类
    def maxProduct(self, s: str) -> int:  # s 为只含小写字母的字符串；返回两个不相交回文子序列长度的最大乘积
        n = len(s)  # n 是字符串长度，子集掩码共 1 << n 个
        p = [True] * (1 << n)  # p[mask] 表示只取 mask 中为 1 的那些位置拼成的子序列是否为回文
        for k in range(1, 1 << n):  # 从 1 开始枚举所有非空子集（空子集对乘积没有贡献）
            i, j = 0, n - 1  # 双指针 i、j 分别指向当前子集的首尾位置
            while i < j:  # 只要左右指针没有相遇，就继续比较
                while i < j and (k >> i & 1) == 0:  # 左指针跳过没有选中的位置：(k >> i) & 1 为 1 才表示选中
                    i += 1  # 左指针右移一位
                while i < j and (k >> j & 1) == 0:  # 右指针跳过没有选中的位置
                    j -= 1  # 右指针左移一位
                if i < j and s[i] != s[j]:  # 两端字符不同，说明该子集不是回文
                    p[k] = False  # 打上「非回文」标记
                    break  # 已经确定不是回文，无需继续比较
                i, j = i + 1, j - 1  # 两端同时向中间收缩，进入下一轮比较
        ans = 0  # ans 记录两个回文子序列长度的最大乘积
        for i in range(1, 1 << n):  # 枚举第一个回文子集 i
            if p[i]:  # 只有回文子集才能作为候选
                mx = ((1 << n) - 1) ^ i  # mx 是 i 的补集：在 mx 中取子集就一定与 i 不相交
                j = mx  # j 从补集 mx 开始枚举它的子集
                a = i.bit_count()  # a 是子集 i 的元素个数，也就是对应回文子序列的长度
                while j:  # 经典技巧：不断 (j - 1) & mx，不重不漏地枚举 mx 的所有子集
                    if p[j]:  # 第二个子集也必须回文
                        b = j.bit_count()  # b 是子集 j 的元素个数
                        ans = max(ans, a * b)  # 两个子序列不相交，用长度乘积更新答案
                    j = (j - 1) & mx  # 枚举 mx 的下一个子集
        return ans  # 返回最大乘积
