# 题目：3992. Rearrange String to Avoid Character Pair（3992. 重新排列字符串以避免字符对）
# 核心思路：双指针把所有的 y 依次交换到字符串前部，于是 y 全部位于所有 x 之前，任意排列都满足题意；交换过程中每个字符只是换了位置，结果仍是原串的排列。
# 复杂度：时间 O(n)，空间 O(n)（需要一次 list 转换）。
class Solution:  # 定义题解类
    def rearrangeString(self, s: str, x: str, y: str) -> str:  # 重排 s，使所有 y 都排在所有 x 之前，返回任意合法排列
        t = list(s)  # 转成列表以便原地交换
        i = 0  # i 指向下一个 y 应该被放置的位置
        for j, c in enumerate(t):  # 从左到右枚举每个字符及其下标
            if c == y:  # 遇到字符 y
                t[i], t[j] = c, t[i]  # 把 y 交换到前部 y 区间的下一个空位
                i += 1  # 前部 y 区间扩大一位
        return ''.join(t)  # 拼回字符串返回
