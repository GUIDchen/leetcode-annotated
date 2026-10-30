# 题目：3106. 满足距离约束且字典序最小的字符串（Lexicographically Smallest String After Operations With Constraint）
# 思路：字典序优先看靠左的字符，于是从左到右贪心：每位都尝试换成比自己小的字符中最小的那个，只要环形距离不超过剩余预算 k 就换掉并扣减预算。
# 时间复杂度：O(n * 26) 即 O(n)，每位最多试 26 个候选；空间复杂度：O(n)，把字符串转成列表便于原地修改。
class Solution:  # LeetCode 约定的题解类
    def getSmallestString(self, s: str, k: int) -> str:  # s：输入字符串；k：总代价；返回字典序最小的结果
        cs = list(s)  # 转成列表，方便逐位原地修改（Python 字符串不可变）
        for i, c1 in enumerate(s):  # 从左到右逐位处理，越靠左越影响字典序
            for c2 in ascii_lowercase:  # 从小到大尝试所有候选字符
                if c2 >= c1:  # 候选已不小于当前字符，后面只会更大
                    break  # 结束内层循环，换下一位
                d = min(ord(c1) - ord(c2), 26 - ord(c1) + ord(c2))  # 环形字母表上的最小距离
                if d <= k:  # 剩余预算够付出这段距离
                    cs[i] = c2  # 把这一位改成更小的字符
                    k -= d  # 扣掉本次消耗的预算
                    break  # 这一位已经最小化，转去处理下一位
        return "".join(cs)  # 用空串连接列表，拼回最终结果
