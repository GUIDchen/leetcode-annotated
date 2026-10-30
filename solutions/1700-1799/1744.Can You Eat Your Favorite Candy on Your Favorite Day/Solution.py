# 题目：1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？（Can You Eat Your Favorite Candy on Your Favorite Day）
# 思路：对糖果数做前缀和得到第 t 类糖果的下标区间 [s[t], s[t+1])；前 day 天必吃的数量范围是 [day, (day+1)*mx]，两个区间有交集即可行。
# 时间复杂度：O(n + q)，预处理前缀和 O(n)、每条询问 O(1)；空间复杂度：O(n)，前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def canEat(self, candiesCount: List[int], queries: List[List[int]]) -> List[bool]:  # 逐条回答询问
        s = list(accumulate(candiesCount, initial=0))  # 前缀和：s[i] 是前 i 类糖果的累计数量，initial=0 让 s[0]=0
        ans = []  # 按询问顺序保存每条询问的答案
        for t, day, mx in queries:  # t：最喜欢的糖果种类；day：最喜欢的第几天（从 0 起）；mx：每天最多吃几颗
            least, most = day, (day + 1) * mx  # 前 day 天最少吃 day 颗（每天至少 1 颗），最多吃 (day+1)*mx 颗
            ans.append(least < s[t + 1] and most > s[t])  # 最少颗数未越过该种类末位、且最多颗数已越过该种类首位，即区间有交集
        return ans  # 返回所有询问的答案
