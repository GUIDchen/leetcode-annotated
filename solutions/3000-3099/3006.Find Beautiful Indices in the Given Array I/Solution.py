# 题目：3006. 找出数组中的美丽下标 I（Find Beautiful Indices in the Given Array I）
# 核心思路：先用 KMP 分别求出两个模式串在 s 中的全部出现下标，再用双指针在两组下标之间滑动，判断是否存在距离不超过 k 的配对。
# 时间复杂度：O(n + m + |A| + |B|)，KMP 线性扫描加双指针线性推进；空间复杂度：O(n + m)，存放两串的出现下标与前缀函数。
class Solution:  # LeetCode 约定的题解类
    def beautifulIndices(self, s: str, a: str, b: str, k: int) -> List[int]:  # s 是主串，a、b 是两个模式串，k 是下标差的绝对值上限
        def build_prefix_function(pattern):  # 构造模式串的前缀函数（KMP 的 next 数组）
            prefix_function = [0] * len(pattern)  # pi[i] 表示 pattern[0..i] 的最长相等前后缀长度，先全部置 0
            j = 0  # j 是当前已经匹配的前缀长度
            for i in range(1, len(pattern)):  # 从第二个字符开始递推
                while j > 0 and pattern[i] != pattern[j]:  # 失配时沿前缀函数回退
                    j = prefix_function[j - 1]  # 回退到次长的相等前后缀长度
                if pattern[i] == pattern[j]:  # 当前字符能与前缀的下一位接上
                    j += 1  # 匹配长度加一
                prefix_function[i] = j  # 记录当前位置的最长相等前后缀长度
            return prefix_function  # 返回前缀函数数组

        def kmp_search(pattern, text, prefix_function):  # KMP：返回 pattern 在 text 中出现的所有起始下标
            occurrences = []  # 保存所有匹配起点
            j = 0  # j 表示当前已经匹配的模式串长度
            for i in range(len(text)):  # 逐字符扫描主串
                while j > 0 and text[i] != pattern[j]:  # 失配时回退
                    j = prefix_function[j - 1]  # 取次长的相等前后缀长度
                if text[i] == pattern[j]:  # 当前字符能与模式串下一位接上
                    j += 1  # 匹配长度加一
                if j == len(pattern):  # 匹配长度达到模式串长度，说明找到一次完整出现
                    occurrences.append(i - j + 1)  # 起点是 i - j + 1
                    j = prefix_function[j - 1]  # 继续寻找可能重叠的下一次出现
            return occurrences  # 返回全部出现下标

        prefix_a = build_prefix_function(a)  # 预处理模式串 a 的前缀函数
        prefix_b = build_prefix_function(b)  # 预处理模式串 b 的前缀函数

        resa = kmp_search(a, s, prefix_a)  # a 在 s 中的所有出现位置
        resb = kmp_search(b, s, prefix_b)  # b 在 s 中的所有出现位置

        res = []  # 收集美丽下标
        i = 0  # i 是 resa 的游标
        j = 0  # j 是 resb 的游标：resa、resb 都递增，所以 j 只需单向推进
        while i < len(resa):  # 逐个考察 A 的出现位置
            while j < len(resb):  # 在 B 的出现位置里找距离最近的一个
                if abs(resb[j] - resa[i]) <= k:  # 距离在 k 以内，满足美丽条件
                    res.append(resa[i])  # 记录这个美丽下标
                    break  # 找到一个就够，跳出内层循环
                elif j + 1 < len(resb) and abs(resb[j + 1] - resa[i]) < abs(  # j 仍然在范围内，且下一个 B 下标更接近 resa[i]
                    resb[j] - resa[i]  # 这一行是上面 abs(...) 拆行书写的第二个参数，仍属于同一个表达式
                ):  # elif 的条件表达式在此闭合
                    j += 1  # 让 j 前移，向目标靠近
                else:  # 否则无论怎么前移都不会更近
                    break  # 直接放弃这个 A 下标，跳出内层循环
            i += 1  # 处理下一个 A 的出现位置
        return res  # 返回升序的美丽下标列表
