# 题目：811. 子域名访问计数（Subdomain Visit Count）
# 思路：拆出本次访问次数后扫描整串，遇到空格或点号就把其后的后缀子域名计数加上该次数。
# 时间复杂度：O(总字符数)；空间复杂度：O(不同子域名个数)。
class Solution:  # LeetCode 约定的题解类
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:  # cpdomains 是 次数+空格+域名 形式的字符串数组
        cnt = Counter()  # 计数器：子域名 -> 累计访问次数
        for s in cpdomains:  # 逐条处理记录
            v = int(s[: s.index(' ')])  # 第一个空格前是次数，切片后转成整数
            for i, c in enumerate(s):  # 扫描字符串的每个位置与字符
                if c in ' .':  # 空格和点号都是分隔符
                    cnt[s[i + 1 :]] += v  # 分隔符右侧的后缀就是合法子域名，累加本次次数
        return [f'{v} {s}' for s, v in cnt.items()]  # 按 次数+空格+子域名 的格式拼出结果列表
