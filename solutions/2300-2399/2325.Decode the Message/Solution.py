# 题目：2325. 解密消息（Decode the Message）
# 核心思路：按 key 中字母首次出现的顺序建立「密文字母 -> 明文字母」映射表，再用它逐字符解密 message。
# 时间复杂度：O(m + n)，m、n 分别为 key 与 message 的长度；空间复杂度：O(1)，映射表最多 26 个字母。
class Solution:  # LeetCode 约定的题解类
    def decodeMessage(self, key: str, message: str) -> str:  # key：密码表；message：待解密消息
        d = {" ": " "}  # 映射表，空格映射到自身
        i = 0  # 下一个待分配明文字母在 ascii_lowercase 中的下标
        for c in key:  # 按密码表的顺序扫描字符
            if c not in d:  # 只在字符首次出现时建立映射
                d[c] = ascii_lowercase[i]  # 依次分配 a、b、c……
                i += 1  # 指针后移
        return "".join(d[c] for c in message)  # 逐字符查表并拼接成解密结果
