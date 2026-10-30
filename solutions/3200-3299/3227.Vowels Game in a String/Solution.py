# 题目：3227. 字符串元音游戏（Vowels Game in a String）
# 思路：玩家每步只能删掉非空且含元音的连续子串，答案只取决于字符串里有没有元音：有元音 Alice 必胜，没有则 Bob 胜。
# 时间复杂度：O(n)，最多扫一遍字符串；空间复杂度：O(1)，只存 5 个元音字母。
class Solution:  # LeetCode 约定的题解类
    def doesAliceWin(self, s: str) -> bool:  # 返回先手 Alice 是否必胜
        vowels = set("aeiou")  # 元音集合，便于 O(1) 判断某个字符是否为元音
        return any(c in vowels for c in s)  # 只要存在任一元音，Alice 就必胜，否则 Bob 获胜
