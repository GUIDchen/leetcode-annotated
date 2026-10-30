# 题目：2287. 重排字符形成目标字符串（Rearrange Characters to Make Target String）
# 核心思路：用 Counter 统计 s 与 target 中各字符的个数，字符 c 能拼出的份数是 cnt1[c] // cnt2[c]，对所有需要使用的字符取最小值即为答案。
# 时间复杂度：O(|s| + |target| + 字母种数)，两次计数加一次求最小值；空间复杂度：O(1)，字符集固定为 26 个小写字母。
class Solution:  # LeetCode 约定的题解类
    def rearrangeCharacters(self, s: str, target: str) -> int:  # s：可重排的源字符串；target：目标字符串；返回最多能拼出几个 target
        cnt1 = Counter(s)  # 统计 s 中每个字符出现的次数
        cnt2 = Counter(target)  # 统计 target 中每个字符出现的次数
        return min(cnt1[c] // v for c, v in cnt2.items())  # 每个字符能支撑的份数取最小值，就是最多能拼出的 target 个数
