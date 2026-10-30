# 题目：953. 验证外星语词典（Verifying an Alien Dictionary）
# 思路：按列纵向扫描所有单词，每列取值必须非降；某列出现严格递增说明顺序已定，可停止；整列相等则需继续看下一列。
# 时间复杂度：O(20·总字符数)，20 为单词最大长度；空间复杂度：O(1)，26 个字母的映射表。
class Solution:  # LeetCode 约定的题解类
    def isAlienSorted(self, words: List[str], order: str) -> bool:  # words 是待验证的单词表，order 是外星语字母表
        m = {c: i for i, c in enumerate(order)}  # 字典推导：字母 → 它在 order 中的排名
        for i in range(20):  # 逐列扫描，单词长度不超过 20，最多检查 20 列
            prev = -1  # 这一列上一个单词的排名，-1 代表「该单词已结束」
            valid = True  # 标记本列是否全部相等，只有全等才需要继续下一列
            for x in words:  # 按顺序遍历每个单词
                curr = -1 if i >= len(x) else m[x[i]]  # 取第 i 个字符；单词已结束则取 -1，保证更短的排在前面
                if prev > curr:  # 本列出现逆序，说明排序被破坏
                    return False  # 直接返回不合法
                if prev == curr:  # 相邻单词在这一列取值不同，说明全等不成立
                    valid = False  # 于是本列不再是「全列相等」
                prev = curr  # 把当前排名留给下一个单词比较
            if valid:  # 整列都相同，顺序尚未确定
                return True  # 需要继续检查下一列
        return True  # 所有列都合法，返回真
