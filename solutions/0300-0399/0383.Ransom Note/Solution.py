# 题目：383. 赎金信（Ransom Note）
# 思路：Counter 统计 magazine 各字母数量，再逐字母扣减 ransomNote 的需求，扣成负数即无法拼出。
# 时间复杂度：O(m + n)，m、n 为两串长度；空间复杂度：O(1)，字母表最多 26 个键。
class Solution:  # 题解类
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:  # ransomNote 是赎金信，magazine 是杂志，判断信能否用杂志里的字母拼出
        cnt = Counter(magazine)  # 把杂志转成「字母 → 可用次数」的计数器
        for c in ransomNote:  # 按赎金信逐字母去消耗库存
            cnt[c] -= 1  # 每用掉一个字母，库存减一
            if cnt[c] < 0:  # 库存被扣成负数，说明杂志里这个字母不够
                return False  # 直接判定无法拼出
        return True  # 全部字母都够用，返回 True
