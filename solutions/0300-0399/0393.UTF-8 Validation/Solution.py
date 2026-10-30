# 题目：393. UTF-8 编码验证（UTF-8 Validation）
# 思路：用 cnt 记录还欠几个续字节，按首字节的高位前缀确定字符长度，续字节必须以 10 开头，最后 cnt 必须归零。
# 时间复杂度：O(n)，每个字节只看一次；空间复杂度：O(1)，只用常数个计数器。
class Solution:  # LeetCode 约定的题解类
    def validUtf8(self, data: List[int]) -> bool:  # data 的每个元素是一个字节（0..255），判断整段字节流是否为合法 UTF-8
        cnt = 0  # 还需要的后续续字节个数，为 0 表示可以开始新字符
        for v in data:  # 逐字节扫描
            if cnt > 0:  # 当前正处在续字节位置
                if v >> 6 != 0b10:  # 续字节必须以二进制 10 开头
                    return False  # 否则编码非法
                cnt -= 1  # 消耗一个续字节
            elif v >> 7 == 0:  # 0xxxxxxx：单字节 ASCII 字符
                cnt = 0  # 单字节字符不需要续字节
            elif v >> 5 == 0b110:  # 110xxxxx：两字节字符的首字节
                cnt = 1  # 后面还需要 1 个续字节
            elif v >> 4 == 0b1110:  # 1110xxxx：三字节字符的首字节
                cnt = 2  # 后面还需要 2 个续字节
            elif v >> 3 == 0b11110:  # 11110xxx：四字节字符的首字节
                cnt = 3  # 后面还需要 3 个续字节
            else:  # 其余前缀都不是合法首字节
                return False  # 直接判定非法
        return cnt == 0  # 结尾必须没有残留的续字节
