# 题目：1153. 字符串转化（String Transforms Into Another String）
# 思路：同一字符必须始终映射到同一字符；两串相同直接成立，否则若 str2 用满 26 个字母就没有空闲字母可做中转，必失败。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，字典最多存 26 个键值对。
class Solution:  # LeetCode 约定的题解类
    def canConvert(self, str1: str, str2: str) -> bool:  # str1 是原串，str2 是目标串
        if str1 == str2:  # 两串完全相同，无需任何转化
            return True  # 直接成立
        if len(set(str2)) == 26:  # 目标串用满 26 个字母，没有空闲字母可做中转
            return False  # 必然无法转化
        d = {}  # d 记录「原字符 → 目标字符」的映射
        for a, b in zip(str1, str2):  # 逐位检查映射是否一致
            if a not in d:  # 该字符还没有建立映射
                d[a] = b  # 建立唯一的映射
            elif d[a] != b:  # 已有映射但与当前位置要求不符
                return False  # 同一字符要变成两个不同字符，矛盾
        return True  # 所有映射都一致，可以转化
