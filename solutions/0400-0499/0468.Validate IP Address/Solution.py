# 题目：468. 验证 IP 地址（Validate IP Address）
# 思路：先按点切分尝试 IPv4（四段、无前导零、0..255），再按冒号切分尝试 IPv6（八段、每段 1..4 位十六进制），都不满足则返回 Neither。
# 时间复杂度：O(L)，L 为地址串长度；空间复杂度：O(L)，存放切分出的各段字符串。
class Solution:  # LeetCode 约定的题解类
    def validIPAddress(self, queryIP: str) -> str:  # queryIP：待校验的地址串
        def is_ipv4(s: str) -> bool:  # 内部函数：判断是否合法 IPv4
            ss = s.split(".")  # 按点切分
            if len(ss) != 4:  # IPv4 必须恰好四段
                return False  # 段数不对直接判负
            for t in ss:  # 逐段校验
                if len(t) > 1 and t[0] == "0":  # 多位时不允许前导零
                    return False  # 直接判负
                if not t.isdigit() or not 0 <= int(t) <= 255:  # 必须全是数字且在 0..255 之间
                    return False  # 直接判负
            return True  # 四段均合法

        def is_ipv6(s: str) -> bool:  # 内部函数：判断是否合法 IPv6
            ss = s.split(":")  # 按冒号切分
            if len(ss) != 8:  # IPv6 必须恰好八段
                return False  # 段数不对直接判负
            for t in ss:  # 逐段校验
                if not 1 <= len(t) <= 4:  # 每段长度必须是 1..4
                    return False  # 直接判负
                if not all(c in "0123456789abcdefABCDEF" for c in t):  # 只允许十六进制字符
                    return False  # 直接判负
            return True  # 八段均合法

        if is_ipv4(queryIP):  # 优先按 IPv4 规则校验
            return "IPv4"  # 合法则返回 IPv4
        if is_ipv6(queryIP):  # 再按 IPv6 规则校验
            return "IPv6"  # 合法则返回 IPv6
        return "Neither"  # 两种都不是
