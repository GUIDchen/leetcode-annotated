# 题目：1898. 可移除字符的最大数目（Maximum Number of Removable Characters）
# 思路：可行性关于删除个数单调，二分 k；判定时标记前 k 个被删位置，再用双指针判断 p 是否为剩余 s 的子序列。
# 时间复杂度：O((m + n) log r)，r = len(removable)；空间复杂度：O(m)，标记数组与 s 等长。
class Solution:  # LeetCode 约定的题解类
    def maximumRemovals(self, s: str, p: str, removable: List[int]) -> int:  # s：原字符串；p：需保持子序列关系的字符串；removable：按顺序可删除的下标
        def check(k: int) -> bool:  # 判定函数：删掉前 k 个下标后 p 是否仍是 s 的子序列
            rem = [False] * len(s)  # 删除标记数组，与 s 等长，初始都没被删
            for i in removable[:k]:  # 标记前 k 个被删除的位置
                rem[i] = True  # 该下标被删除
            i = j = 0  # i 扫描 s，j 扫描 p
            while i < len(s) and j < len(p):  # 双指针匹配子序列
                if not rem[i] and p[j] == s[i]:  # 未被删除且字符相同，匹配上一个字符
                    j += 1  # p 的指针前进
                i += 1  # s 的指针每轮都前进
            return j == len(p)  # p 全部匹配完说明仍是子序列

        l, r = 0, len(removable)  # 二分区间：最多可删除的数目
        while l < r:  # 二分找最大的可行 k
            mid = (l + r + 1) >> 1  # 上取整中点，配合 l = mid 避免死循环
            if check(mid):  # mid 可行
                l = mid  # 答案不小于 mid
            else:  # mid 不可行
                r = mid - 1  # 答案更小
        return l  # 收敛处就是答案
