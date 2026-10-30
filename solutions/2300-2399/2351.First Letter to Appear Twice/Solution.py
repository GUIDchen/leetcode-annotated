# 题目：2351. 第一个出现两次的字母（First Letter to Appear Twice）
# 思路：用计数器累加每个字母出现的次数，顺序扫描时一旦某字母的计数达到 2 就立刻返回它。
# 时间复杂度：O(n)，只遍历一次字符串；空间复杂度：O(1)，最多 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def repeatedCharacter(self, s: str) -> str:  # s：只含小写字母的字符串
        cnt = Counter()  # 计数器：键是字母，值是出现次数
        for c in s:  # 按顺序遍历每个字符
            cnt[c] += 1  # 当前字母的出现次数加一
            if cnt[c] == 2:  # 恰好第二次出现
                return c  # 它就是第一个出现两次的字母
