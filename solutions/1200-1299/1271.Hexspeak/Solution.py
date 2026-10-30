class Solution:  # LeetCode 约定的题解类
    def toHexspeak(self, num: str) -> str:  # num：十进制数字字符串，返回十六进制形式的魔术数字
        s = set('ABCDEFIO')  # 所有合法的魔术数字字符：A~F 加上 I、O
        t = hex(int(num))[2:].upper().replace('0', 'O').replace('1', 'I')  # 转十六进制 → 去掉 0x 前缀 → 转大写 → 把 0/1 换成 O/I
        return t if all(c in s for c in t) else 'ERROR'  # 所有位都在合法集合内才返回，否则返回 'ERROR'
