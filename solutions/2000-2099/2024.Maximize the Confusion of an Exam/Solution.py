# 题目：2024. 考试的最大困扰度（Maximize the Confusion of an Exam）
# 思路：分别以 'T' 和 'F' 为目标字符，用滑动窗口求「窗口内该字符个数不超过 k」的最长区间；窗口里这些字符全部改写即可连成一段，两种目标取较大值。
# 时间复杂度：O(n)，字符串被扫描两遍；空间复杂度：O(1)，只用了几个计数器。
class Solution:  # LeetCode 约定的题解类
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:  # answerKey 是只有 'T'/'F' 的答题串，k 是最多可改写的字符数
        def f(c: str) -> int:  # 内部函数 f：求「窗口内字符 c 的个数不超过 k」的最长窗口长度
            cnt = l = 0  # l 是滑动窗口左边界，cnt 是窗口内等于 c 的字符个数
            for ch in answerKey:  # 右边界 ch 依次扫过整个字符串
                cnt += ch == c  # 新字符进窗：等于 c 时计数加 1（布尔值可直接参与加法）
                if cnt > k:  # 窗口内 c 的个数超过可改写次数，需要从左侧收缩
                    cnt -= answerKey[l] == c  # 左端出窗：只有出窗字符正好是 c 才把计数减 1
                    l += 1  # 左边界右移一位
            return len(answerKey) - l  # 最优窗口长度 = 总长度 - 左边界

        return max(f("T"), f("F"))  # 把两段分别改成全 'T'、全 'F'，取较优的一种
