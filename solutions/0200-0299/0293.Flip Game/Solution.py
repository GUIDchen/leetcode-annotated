# 题目：293. 翻转游戏（Flip Game）—— 一次把相邻的两个 "++" 翻成 "--"，列出所有翻转后可能得到的状态，不能重复。
# 核心思路：从左到右枚举每对相邻字符，遇到 "++" 就原地翻转、收集当前串、再翻回原状，保证后续枚举基于原始状态。
# 时间复杂度：O(n²)，共 O(n) 个位置、每次拼接答案 O(n)；空间复杂度：O(n²)，答案最多存 O(n) 个长度为 n 的串。
class Solution:  # LeetCode 约定的题解类
    def generatePossibleNextMoves(self, currentState: str) -> List[str]:  # currentState：只包含 '+' 和 '-' 的当前状态
        s = list(currentState)  # str 不可变，先转成列表才能原地改字符
        ans = []  # 收集所有可能的下一状态
        for i, (a, b) in enumerate(pairwise(s)):  # pairwise 成对产出相邻元素，i 是左边元素的下标
            if a == b == "+":  # 链式比较：两个字符都是 '+' 才能翻转
                s[i] = s[i + 1] = "-"  # 原地把这两个字符翻成 '-'
                ans.append("".join(s))  # 把翻转后的完整字符串收进答案
                s[i] = s[i + 1] = "+"  # 再翻回 '+'，保证后面的枚举仍基于原始状态
        return ans  # 返回全部可能的下一状态
