# 题目：482. 密钥格式化（License Key Formatting）
# 思路：非 '-' 字符个数对 k 取余得到第一组的长度（余数为 0 时第一组满 k 个），再从左往右扫描：非 '-' 转大写后追加，凑满一组就补 '-'，最后去掉尾部多余的分隔符。
# 时间复杂度：O(n)，只扫描一遍字符串；空间复杂度：O(n)，结果列表存放全部字符与分隔符。
class Solution:  # LeetCode 约定的题解类
    def licenseKeyFormatting(self, s: str, k: int) -> str:  # s 是原密钥字符串，k 是除第一组外每组的字符数
        n = len(s)  # 记住原串长度，用于判断“是否最后一个下标”
        cnt = (n - s.count("-")) % k or k  # 第一组长度：有效字符数对 k 取余；`or k` 表示余数为 0 时取满组 k
        ans = []  # 用列表收集结果字符，最后再拼接成字符串
        for i, c in enumerate(s):  # 同时拿到下标 i 与字符 c，下标用来判断末尾
            if c == "-":  # 遇到分隔符 '-'
                continue  # 直接跳过，不参与分组
            ans.append(c.upper())  # 字母转大写后加入结果（非字母字符保持不变）
            cnt -= 1  # 本组还差几个字符，减去当前这个
            if cnt == 0:  # 减到 0 说明这一组已经凑满
                cnt = k  # 重置计数器，准备下一组
                if i != n - 1:  # 只有不是原串最后一个字符时才补分隔符
                    ans.append("-")  # 追加分组用的 '-'
        return "".join(ans).rstrip("-")  # 拼接后用 rstrip 去掉末尾可能残留的 '-'（最后一个有效字符可能早于原串末尾）
