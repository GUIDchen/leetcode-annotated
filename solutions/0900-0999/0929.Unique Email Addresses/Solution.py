# 题目：929. 独特的电子邮件地址（Unique Email Addresses）
# 思路：按 @ 切出本地名与域名，本地名去掉所有点并截断到第一个 + 之前，拼回后加入集合去重，集合大小即答案。
# 时间复杂度：O(L)，L 为所有邮件字符总数；空间复杂度：O(L)，用于保存集合中的规范化地址。
class Solution:  # LeetCode 约定的题解类
    def numUniqueEmails(self, emails: List[str]) -> int:  # emails：原始邮件地址列表
        s = set()  # 用集合存放规范化后的地址，天然去重
        for email in emails:  # 逐个处理每封邮件
            local, domain = email.split("@")  # 按 @ 拆成本地名与域名两部分
            t = []  # 存放去掉点和 + 后缀之后的本地名（用列表逐字符收集）
            for c in local:  # 逐字符扫描本地名
                if c == ".":  # 规则一：本地名中的点一律忽略
                    continue  # 跳过这个字符
                if c == "+":  # 规则二：遇到 + 之后的内容全部丢弃
                    break  # 结束本地名的处理
                t.append(c)  # 普通字符保留下来
            s.add("".join(t) + "@" + domain)  # 拼回「规范本地名@域名」并加入集合
        return len(s)  # 集合大小就是不同地址的数量
