# 题目：791. 自定义字符串排序（Custom Sort String）
# 思路：把 order 里字符的下标当作排序键，对 s 按该键排序；order 中未出现的字符统一取默认键 0。
# 时间复杂度：O(|order| + |s| log |s|)，瓶颈是排序；空间复杂度：O(|order|)，字典保存字符到下标的映射。
class Solution:  # LeetCode 约定的题解类
    def customSortString(self, order: str, s: str) -> str:  # order 是自定义顺序，s 是待重排的字符串
        d = {c: i for i, c in enumerate(order)}  # 字典推导式：字符 → 它在 order 中的下标（即排序权重）
        return ''.join(sorted(s, key=lambda x: d.get(x, 0)))  # 按权重升序排序后拼回字符串；get 的默认 0 表示 order 中未出现的字符
