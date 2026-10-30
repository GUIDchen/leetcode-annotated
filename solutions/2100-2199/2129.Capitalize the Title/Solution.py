# 题目：2129. 将标题首字母大写（Capitalize the Title）
# 核心思路：按空白切词，长度小于 3 的词全小写，否则首字母大写、其余小写，最后用单个空格拼接。
# 时间复杂度：O(n)，每个字符只处理常数次；空间复杂度：O(n)，保存切分出的单词列表。
class Solution:  # LeetCode 约定的题解类
    def capitalizeTitle(self, title: str) -> str:  # title 是待格式化的标题字符串
        words = [w.lower() if len(w) < 3 else w.capitalize() for w in title.split()]  # 列表推导：短词用 lower 全小写，长词用 capitalize 首字母大写、其余小写
        return " ".join(words)  # 用单个空格把处理后的单词重新拼成标题
