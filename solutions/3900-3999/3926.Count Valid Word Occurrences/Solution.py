# 题目：3926. 有效单词计数（Count Valid Word Occurrences）
# 思路：先把 chunks 拼成 s，再用双指针切词——空格与孤立的 '-' 是分隔符，被小写字母两侧包围的 '-' 属于单词内部；用哈希表统计词频后逐个回答查询。
# 时间复杂度：O(|s| + 查询总长度)；空间复杂度：O(|s|)，哈希表最多存下所有不同的单词。
class Solution:  # LeetCode 约定的题解类
    def countWordOccurrences(self, chunks: list[str], queries: list[str]) -> list[int]:  # chunks：待拼接的片段；queries：要统计出现次数的单词
        s = "".join(chunks)  # 一次性拼接出完整字符串
        n = len(s)  # 拼接后的总长度
        cnt = defaultdict(int)  # 单词 → 出现次数，缺失的键默认取 0
        i = 0  # 当前扫描位置
        while i < n:  # 逐个单词地扫描整个字符串
            if s[i] in " -":  # 当前字符是空格或孤立的连字符，属于分隔符
                i += 1  # 跳过分隔符
                continue  # 进入下一轮扫描
            j = i  # j 从 i 出发向右寻找单词结尾
            while (  # 判断 s[j] 是否仍属于当前单词
                j < n  # 尚未越界
                and s[j] != " "  # 不是空格
                and (s[j] != "-" or (j + 1 < n and s[j + 1] not in " -"))  # '-' 后面紧跟字母时该 '-' 属于单词内部
            ):  # 条件结束
                j += 1  # 单词长度扩展一位
            cnt[s[i:j]] += 1  # 切出 s[i, j) 作为单词并累加计数
            i = j  # 从单词结尾继续扫描
        return [cnt[q] for q in queries]  # 逐个查询取计数，未出现过的单词即为 0
