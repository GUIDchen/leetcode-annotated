# 题目：3039. 进行操作使字符串为空（Apply Operations to Make String Empty）
# 思路：每轮删掉每个出现过的字符各一次，总轮数是最大词频；最后一轮前剩下的就是最大词频那些字符各自最后出现的位置。
# 时间复杂度：O(n)，一次计数 + 一次字典 + 一次扫描；空间复杂度：O(|Σ|)，只保存 26 个字母的计数与最后位置。
class Solution:  # LeetCode 约定的题解类
    def lastNonEmptyString(self, s: str) -> str:  # s 是输入字符串
        cnt = Counter(s)  # 统计每个字符在整个字符串中的出现次数
        mx = cnt.most_common(1)[0][1]  # 取出现次数最多的那个字符的频次，就是需要执行的操作轮数
        last = {c: i for i, c in enumerate(s)}  # 字典推导：记录每个字符最后一次出现的下标（后出现的会覆盖前面的）
        return "".join(c for i, c in enumerate(s) if cnt[c] == mx and last[c] == i)  # 按原顺序取出「词频最大且处于自己最后一次出现位置」的字符
