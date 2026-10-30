# 3598. 相邻字符串之间的最长公共前缀（Longest Common Prefix Between Adjacent Strings After Removals）
# 核心思路：用 SortedList 维护当前所有相邻串对的 LCP，逐一下标执行“删除两对 → 新增跨过被删下标的一对 → 取最大值 → 恢复”的增量维护。
# 复杂度：时间 O(n · L + n log n)，空间 O(n)，其中 L 为字符串长度上界。
class Solution:  # 主解类
    def longestCommonPrefix(self, words: List[str]) -> List[int]:  # 对每个下标，删除该单词后返回相邻字符串最长公共前缀的最大值
        @cache  # 缓存两串的 LCP，避免重复计算
        def calc(s: str, t: str) -> int:  # 计算两个字符串的最长公共前缀长度
            k = 0  # 已匹配的长度
            for a, b in zip(s, t):  # 把两串按位并排比较
                if a != b:  # 首次出现不同字符
                    break  # 停止比较
                k += 1  # 匹配长度加一
            return k  # 返回公共前缀长度

        def add(i: int, j: int):  # 下标合法时把一对相邻关系的 LCP 加入有序表
            if 0 <= i < n and 0 <= j < n:  # 两个下标都必须落在 [0, n) 内
                sl.add(calc(words[i], words[j]))  # 插入这对的 LCP

        def remove(i: int, j: int):  # 下标合法时把一对相邻关系的 LCP 从有序表移除
            if 0 <= i < n and 0 <= j < n:  # 两个下标都必须落在 [0, n) 内
                sl.remove(calc(words[i], words[j]))  # 移除这对 LCP 的一个副本

        n = len(words)  # 单词个数
        sl = SortedList(calc(a, b) for a, b in pairwise(words))  # 初始所有相邻对的 LCP 有序表
        ans = []  # 答案列表
        for i in range(n):  # 枚举被删除（被跳过）的下标 i
            remove(i, i + 1)  # 删除后 (i, i+1) 不再是相邻对
            remove(i - 1, i)  # 删除后 (i-1, i) 也不再是相邻对
            add(i - 1, i + 1)  # 删除 i 后 i-1 与 i+1 变成新的相邻对
            ans.append(sl[-1] if sl and sl[-1] > 0 else 0)  # 取当前最大 LCP，空表或非正值记 0
            remove(i - 1, i + 1)  # 撤销刚新增的跨过对
            add(i - 1, i)  # 恢复 (i-1, i) 这对相邻关系
            add(i, i + 1)  # 恢复 (i, i+1) 这对相邻关系
        return ans  # 返回每个下标对应的答案
