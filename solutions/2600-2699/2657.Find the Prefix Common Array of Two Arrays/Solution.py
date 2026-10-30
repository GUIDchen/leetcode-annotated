# 题目：2657. 找到两个数组的前缀公共数组（Find the Prefix Common Array of Two Arrays）
# 核心思路：逐位扩展前缀，同时维护两个数组前缀内各值的出现次数，累加每个值两次出现次数的较小值就是公共元素个数。
# 时间复杂度：O(n^2)，每扩展一位都要遍历一次计数字典；空间复杂度：O(n)，两个计数字典。
class Solution:  # 题解类
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:  # A、B 都是 1..n 的排列；返回每个前缀的公共元素个数
        ans = []  # ans[i] 存前 i+1 个位置的公共元素个数
        cnt1 = Counter()  # 统计 A 前缀中各值的出现次数
        cnt2 = Counter()  # 统计 B 前缀中各值的出现次数
        for a, b in zip(A, B):  # 同步扩展两个数组的前缀
            cnt1[a] += 1  # A 的前缀加入 a
            cnt2[b] += 1  # B 的前缀加入 b
            t = sum(min(v, cnt2[x]) for x, v in cnt1.items())  # 对每个值取两边出现次数的较小值再求和，即为公共元素个数
            ans.append(t)  # 记录当前前缀的答案
        return ans  # 返回结果
