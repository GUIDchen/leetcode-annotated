# 题目：966. 元音拼写检查器（Vowel Spellchecker）
# 思路：同时维护原始单词集合、小写到原词的映射、元音换成 '*' 的模式到原词的映射，查询按这三级的优先级依次匹配。
# 时间复杂度：O((|wordlist| + |queries|) * L)，L 为单词长度；空间复杂度：O(|wordlist| * L)，三套索引的存储。
class Solution:  # LeetCode 约定的题解类
    def spellchecker(self, wordlist: List[str], queries: List[str]) -> List[str]:  # wordlist 是词典，queries 是待检查单词，返回等长的结果列表
        def f(w):  # 辅助函数：把单词的元音都换成 '*'，得到忽略大小写与元音差异的模式
            t = []  # 收集模式字符
            for c in w:  # 逐字符扫描单词
                t.append("*" if c in "aeiou" else c)  # 元音换成 '*'，辅音原样保留
            return "".join(t)  # 拼回一个字符串作为模式

        s = set(wordlist)  # 原始单词集合，用于第一优先级「完全相同」的匹配
        low, pat = {}, {}  # low：小写 -> 原词；pat：元音模式 -> 原词
        for w in wordlist:  # 遍历词典建立索引
            t = w.lower()  # 转成小写，供第二、第三优先级使用
            low.setdefault(t, w)  # setdefault 只在键不存在时写入，保证留下词典中最靠前的原词
            pat.setdefault(f(t), w)  # 同理，记录元音模式到原词的映射

        ans = []  # 存放每个查询的结果
        for q in queries:  # 按顺序处理每个查询
            if q in s:  # 第一优先级：词典里有完全相同的词
                ans.append(q)  # 原样返回
                continue  # 处理下一个查询
            q = q.lower()  # 第二优先级：忽略大小写，先把查询词转成小写
            if q in low:  # 小写形式在词典中出现过
                ans.append(low[q])  # 返回词典中的原始拼写
                continue  # 处理下一个查询
            q = f(q)  # 第三优先级：把查询词的元音也模糊化
            if q in pat:  # 模糊模式在词典中出现过
                ans.append(pat[q])  # 返回词典中的原始拼写
                continue  # 处理下一个查询
            ans.append("")  # 三级都不匹配，返回空串表示无匹配
        return ans  # 返回全部查询的结果
