# 题目：3860. 不同邮件组（Unique Email Groups）
# 思路：按规则规范化地址——本地名丢掉第一个 '+' 之后的内容、忽略所有 '.'，整体转小写；域名只转小写，最后用集合去重计数。
# 时间复杂度：O(L)，L 为所有地址的总长度；空间复杂度：O(L)，需要存放规范化后的地址。
class Solution:  # LeetCode 约定的题解类
    def uniqueEmailGroups(self, emails: list[str]) -> int:  # emails：邮箱地址列表
        st = set()  # 存放规范化后的地址，集合天然去重
        for email in emails:  # 逐个处理邮件地址
            local, domain = email.split("@")  # 以 '@' 切成 本地名 / 域名
            local = local.split("+")[0].replace(".", "").lower()  # 去掉第一个 '+' 之后的内容、忽略所有点号并转小写
            domain = domain.lower()  # 域名只做小写化
            normalized = local + "@" + domain  # 拼回规范化的完整地址
            st.add(normalized)  # 放入集合，重复地址自动合并
        return len(st)  # 集合大小即可不同邮件组数
