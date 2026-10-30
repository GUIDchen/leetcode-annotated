# 题目：859. 亲密字符串（Buddy Strings）
# 思路：长度与字符频次都必须相同；再统计同位置不同字符的个数：恰好 2 个就交换这两个位置，0 个则必须存在重复字符才能靠「交换相同字符」完成。
# 时间复杂度：O(n + |Σ|)，n 为字符串长度、Σ 为字符集；空间复杂度：O(|Σ|)，两个计数器。
class Solution:  # LeetCode 约定的题解类
    def buddyStrings(self, s: str, goal: str) -> bool:  # 判断能否只交换 s 中的两个字符就得到 goal
        m, n = len(s), len(goal)  # 分别取两个字符串的长度
        if m != n:  # 长度不同，一次交换不可能改变长度
            return False  # 直接判定不成立
        cnt1, cnt2 = Counter(s), Counter(goal)  # 分别统计两个字符串的字符频次
        if cnt1 != cnt2:  # 频次不同说明字符集合有差异，交换不会增删字符
            return False  # 直接判定不成立
        diff = sum(s[i] != goal[i] for i in range(n))  # 统计同下标上字符不同的位置个数
        return diff == 2 or (diff == 0 and any(v > 1 for v in cnt1.values()))  # 恰好两处不同可互换使其相等；或完全相同且含重复字符
