# 题目：1410. HTML 实体解析器（HTML Entity Parser）
# 思路：字典保存实体到单字符的映射，逐位滑动窗口尝试长度 1..7，命中即整体跳过，否则原样保留当前字符。
# 时间复杂度：O(n * L)，L 为实体最大长度 7，视为 O(n)；空间复杂度：O(n)，答案列表与常数大小的字典。
class Solution:  # LeetCode 约定的题解类
    def entityParser(self, text: str) -> str:  # text 是含 HTML 实体的字符串，返回解析后的字符串
        d = {  # 实体到单字符的映射字典，键是实体原文
            '&quot;': '"',  # &quot; 解析成双引号
            '&apos;': "'",  # &apos; 解析成单引号
            '&amp;': "&",  # &amp; 解析成 & 符号
            "&gt;": '>',  # &gt; 解析成大于号
            "&lt;": '<',  # &lt; 解析成小于号
            "&frasl;": '/',  # &frasl; 解析成斜杠
        }  # 结束字典初始化
        i, n = 0, len(text)  # i 是当前扫描位置，n 是文本长度
        ans = []  # 结果列表，用 append 拼接效率更高
        while i < n:  # 从左到右扫描整段文本
            for l in range(1, 8):  # 实体最长 7 个字符，按长度枚举所有可能
                j = i + l  # 以 i 开头、长度为 l 的子串的右端点（切片不含 j）
                if text[i:j] in d:  # 候选切片正好是一个实体
                    ans.append(d[text[i:j]])  # 追加该实体对应的单个字符
                    i = j  # 跳过整个实体
                    break  # 命中就跳出长度循环，不再尝试更长
            else:  # for 的 else：只有循环没被 break（即没匹配到实体）才执行
                ans.append(text[i])  # 没命中实体，当前字符原样保留
                i += 1  # 后移一位继续扫描
        return ''.join(ans)  # 拼成字符串返回
