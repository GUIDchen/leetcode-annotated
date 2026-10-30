# 题目：2262. 字符串的总引力（Total Appeal of A String）
# 思路：按右端点递推，t 表示以 i 结尾的所有子串引力之和；字符 c 只在起点位于它上次出现位置之后的 i-pos[c] 个子串中首次出现，于是 t += i-pos[c]，再累加进 ans。
# 时间复杂度：O(n)，一趟遍历；空间复杂度：O(1)，只用了 26 个下标。
class Solution:  # LeetCode 约定的题解类
    def appealSum(self, s: str) -> int:  # s 是输入字符串，返回所有子串的引力总和
        ans = t = 0  # ans 累加总答案；t 是以当前位置结尾的所有子串的引力之和
        pos = [-1] * 26  # pos[ch] 记录字符 ch 最近一次出现的下标，-1 表示尚未出现
        for i, c in enumerate(s):  # 从左到右枚举结束位置 i 和对应字符 c
            c = ord(c) - ord('a')  # 把字符映射成 0~25 的整数下标，此后 c 表示下标而不是字符
            t += i - pos[c]  # 起点在 pos[c] 之后的 i-pos[c] 个子串因该字符首次出现而各多 1 点引力
            ans += t  # 把以 i 结尾的全部子串引力累加进总答案
            pos[c] = i  # 更新该字符的最新出现位置
        return ans  # 返回所有子串的引力总和
