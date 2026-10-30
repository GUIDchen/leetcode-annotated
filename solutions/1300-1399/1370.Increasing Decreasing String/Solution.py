# 题目：1370. 上升下降字符串（Increasing Decreasing String）
# 思路：统计每个字母出现次数，反复做「a→z 取一个、z→a 取一个」的扫描，直到用完所有字符。
# 时间复杂度：O(n + 26·n)，每轮至少取一个字符；空间复杂度：O(26)，计数器。
class Solution:  # LeetCode 约定的题解类
    def sortString(self, s: str) -> str:  # s 是输入字符串，返回按「上升-下降」规则重排的结果
        cnt = Counter(s)  # 统计每个字符出现次数
        cs = ascii_lowercase + ascii_lowercase[::-1]  # 一轮的字符顺序：先 a→z，再 z→a
        ans = []  # ans 保存结果字符
        while len(ans) < len(s):  # 只要还没用完所有字符就继续
            for c in cs:  # 按本轮顺序遍历字符
                if cnt[c]:  # 该字符还有剩余
                    ans.append(c)  # 追加到答案
                    cnt[c] -= 1  # 用掉一个
        return "".join(ans)  # 拼成字符串返回
