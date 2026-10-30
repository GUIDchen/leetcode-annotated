# 3481. 应用替换 🔒（Apply Substitutions）
# 核心思路：把替换关系整理成字典，递归扫描字符串中成对的 %...% 占位符，先递归展开占位符对应的替换串，再拼接前缀与递归展开的后缀，从而支持多层嵌套。
# 复杂度：时间 O(L × 嵌套层数)，空间 O(L)（L 为展开后的字符串长度）
class Solution:  # 解题类
    def applySubstitutions(self, replacements: List[List[str]], text: str) -> str:  # 返回把 text 中所有 %key% 占位符替换后的结果
        def dfs(s: str) -> str:  # 递归函数：把 s 中的占位符全部展开
            i = s.find("%")  # 找到第一个 %
            if i == -1:  # 没有占位符起始符
                return s  # 原样返回
            j = s.find("%", i + 1)  # 找到与之配对的第二个 %
            if j == -1:  # 没有配对的结束符
                return s  # 原样返回
            key = s[i + 1 : j]  # 截取两个 % 之间的占位符名
            replacement = dfs(d[key])  # 先递归展开该占位符对应的替换串，避免遗留嵌套占位符
            return s[:i] + replacement + dfs(s[j + 1 :])  # 拼接：前缀 + 展开后的替换内容 + 递归展开的后缀

        d = {s: t for s, t in replacements}  # 把替换规则整理成字典
        return dfs(text)  # 从整串 text 开始递归展开
