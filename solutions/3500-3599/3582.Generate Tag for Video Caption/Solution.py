# 3582. 为视频标题生成标签（Generate Tag for Video Caption）
# 核心思路：按空白切分标题，所有单词转小写、除首词外首字母大写，以 '#' 开头拼接后截断到 100 个字符。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为标题字符总数。
class Solution:  # 定义题解类
    def generateTag(self, caption: str) -> str:  # 把视频标题转换成标签
        words = [s.capitalize() for s in caption.split()]  # 按空白切分并逐词做首字母大写
        if words:  # 存在单词时把首词改回全小写
            words[0] = words[0].lower()  # 首词整体转小写
        return "#" + "".join(words)[:99]  # 加井号并截断到 100 个字符（99 个单词字符 + '#'）
