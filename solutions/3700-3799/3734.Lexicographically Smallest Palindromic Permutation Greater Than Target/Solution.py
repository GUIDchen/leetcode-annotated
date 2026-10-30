# 3734. 大于目标字符串的最小字典序回文排列 / Lexicographically Smallest Palindromic Permutation Greater Than Target
# 核心思路：回文由左半边唯一决定，因此只在左半边做 next-permutation 式贪心：先尽量沿用 target 左半的前缀，再从最靠右的位置把某位换成更大字母，剩余位置按字母序最小填充，拼成回文后校验是否大于 target。
# 复杂度：时间 O(26 * n^2)（每个候选位置重建一次左半），空间 O(n + 26)。
class Solution:  # 定义 LeetCode 解法类
    def lexPalindromicPermutation(self, s: str, target: str) -> str:  # 求字典序大于 target 的最小回文排列
        def build(left: str, middle: str, n: int) -> str:  # 用左半边、中位字符与总长度拼出完整回文
            right = left[::-1]  # 反转左半边得到镜像的右半边
            if n % 2:  # 总长度为奇数时需要中位字符
                return left + middle + right  # 左半 + 中位 + 右半
            return left + right  # 偶数长度直接左右拼接

        n = len(s)  # 字符串长度
        freq = [0] * 26  # 统计每个字母的出现次数
        for c in s:  # 遍历原串
            freq[ord(c) - 97] += 1  # 计入当前字母
        odd = 0  # 出现奇数次的字母个数
        middle = ""  # 唯一的奇数频次字母会放在正中间
        for i, v in enumerate(freq):  # 遍历 26 个字母
            if v % 2:  # 该字母出现奇数次
                odd += 1  # 奇数频次计数加一
                middle = chr(97 + i)  # 记为中位字符候选
        if odd > 1:  # 多于一个奇频字母时无法构成回文
            return ""  # 返回空串表示无解

        half = [v // 2 for v in freq]  # 左半边每个字母可用的次数
        half_len = n // 2  # 左半边的长度
        target_half = target[:half_len]  # 只取 target 的左半边做比较
        remaining = half[:]  # 剩余可用字母计数
        prefix = []  # 已构造出的左半前缀
        matched = 0  # 与 target 左半边已匹配的字符数
        for i in range(half_len):  # 贪心地按 target 左半边逐位匹配
            x = ord(target_half[i]) - 97  # 当前位需要的字母
            if remaining[x] == 0:  # 该字母已经用完
                break  # 无法继续沿用 target 前缀，退出匹配
            prefix.append(target_half[i])  # 把该字符追加到前缀
            remaining[x] -= 1  # 消耗一个该字母
            matched += 1  # 匹配长度加一

        if matched == half_len:  # 左半边与 target 左半边完全一致
            cand = build("".join(prefix), middle, n)  # 拼出对应的完整回文
            if cand > target:  # 回文整体字典序大于 target
                return cand  # 它就是最小候选，直接返回

        last = half_len - 1 if matched == half_len else matched  # 从最靠右的、仍可改动的位置开始回溯
        for pos in range(last, -1, -1):  # 逐位尝试把该位换成更大的字母
            rem = half[:]  # 重置剩余字母计数
            valid = True  # 前缀是否可行的标记
            for i in range(pos):  # 重放 pos 之前的前缀
                x = ord(target_half[i]) - 97  # 前缀需要的字母
                if rem[x] == 0:  # 该字母数量不足
                    valid = False  # 标记前缀不可行
                    break  # 提前退出重放
                rem[x] -= 1  # 消耗该字母
            if not valid:  # 前缀不合法
                continue  # 换更靠左的位置继续尝试
            target_char = ord(target_half[pos]) - 97  # 该位置在 target 中的字符
            for c in range(target_char + 1, 26):  # 寻找比它更大的可用字母
                if rem[c] == 0:  # 该字母不可用
                    continue  # 尝试下一个字母
                left = target_half[:pos] + chr(97 + c)  # 保留前缀并放入一个更大的字母
                rem[c] -= 1  # 消耗一个该字母
                for x in range(26):  # 剩余位置按字母序从小到大填充
                    left += chr(97 + x) * rem[x]  # 一次追加该字母的全部剩余次数
                    rem[x] = 0  # 该字母已被用尽
                cand = build(left, middle, n)  # 拼出完整回文
                if cand > target:  # 确认字典序大于 target
                    return cand  # 字母从小到大枚举，第一个满足的即最小
                rem = half[:]  # 恢复剩余计数，尝试同位置的下一个字母
                for i in range(pos):  # 重新扣掉前缀消耗的字母
                    rem[ord(target_half[i]) - 97] -= 1  # 扣减前缀用掉的字母
        return ""  # 所有位置都无法构造，返回空串
