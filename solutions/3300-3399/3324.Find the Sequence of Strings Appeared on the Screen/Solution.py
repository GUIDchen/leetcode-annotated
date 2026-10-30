# 题目：3324. 出现在屏幕上的字符串序列（Find the Sequence of Strings Appeared on the Screen）
# 思路：模拟。对 target 的每个字符，以上一次得到的完整字符串为前缀，把末位字符从 'a' 一直递增到该字符，每改一次就记录一个屏幕状态。
# 时间复杂度：O(n^2)，n 为 target 长度（每个位置最多追加 26 个长度 O(n) 的字符串）；空间复杂度：O(n^2)，保存全部中间字符串。
class Solution:  # LeetCode 约定的题解类
    def stringSequence(self, target: str) -> List[str]:  # target：最终要拼出的目标字符串
        ans = []  # 按时间顺序记录屏幕上出现的每一个字符串
        for c in target:  # 逐个字符地把 target 构造出来
            s = ans[-1] if ans else ""  # 上一次按键后屏幕上的完整字符串（首次为空串），作为本次的前缀
            for a in ascii_lowercase:  # 末位字符从小写字母 a 开始递增
                t = s + a  # 追加当前字符得到新的屏幕内容
                ans.append(t)  # 每按一次键就记录一次
                if a == c:  # 已经把末位改到目标字符 c
                    break  # 本层结束，跳出内层循环
        return ans  # 返回完整的字符串序列
