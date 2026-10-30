# 3612. Process String with Special Operations I / 用特殊操作处理字符串 I
# 核心思路：按顺序模拟四种操作——小写字母追加、星号删除末尾、井号复制整串、百分号反转整串。
# 复杂度：时间复杂度 O(n^2)（井号复制使串长翻倍），空间复杂度 O(n)，n 为操作串长度。
class Solution:  # 定义题解类
    def processStr(self, s: str) -> str:  # 按操作序列模拟构造最终字符串
        result = []  # 用列表作为字符缓冲区
        for c in s:  # 顺序扫描每个操作字符
            if c.isalpha():  # 情况一：当前字符是英文字母
                result.append(c)  # 直接把字母追加到末尾
            elif c == "*" and result:  # 情况二：星号且缓冲区非空时才删除末尾
                result.pop()  # 弹出最后一个字符
            elif c == "#":  # 情况三：井号表示复制当前整串
                result.extend(result)  # 追加自身使长度翻倍
            elif c == "%":  # 情况四：百分号表示反转整串
                result.reverse()  # 原地反转缓冲区
        return "".join(result)  # 拼接成字符串并返回
