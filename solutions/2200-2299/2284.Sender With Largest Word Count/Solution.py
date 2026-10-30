# 题目：2284. 最多单词数的发件人（Sender With Largest Word Count）
# 核心思路：用 Counter 按发件人累加每条消息的单词数（空格数 + 1），再遍历取单词最多者，并列时取字典序更大的名字。
# 时间复杂度：O(L + n)，L 是全部消息的总长度；空间复杂度：O(n)，Counter 最多保存 n 个发件人。
class Solution:  # LeetCode 约定的题解类
    def largestWordCount(self, messages: List[str], senders: List[str]) -> str:  # messages 与 senders 按下标一一对应，第 i 条消息由 senders[i] 发出
        cnt = Counter()  # 哈希表：发件人名字 → 累计单词数
        for message, sender in zip(messages, senders):  # zip 把每条消息与它的发件人配对遍历
            cnt[sender] += message.count(" ") + 1  # 空格个数加一即为单词数，累加到该发件人名下
        ans = senders[0]  # 候选答案先取第一个发件人，作为比较基准
        for k, v in cnt.items():  # 遍历每个发件人及其总单词数
            if cnt[ans] < v or (cnt[ans] == v and ans < k):  # 单词数更多，或数量并列但名字字典序更大，就替换答案
                ans = k  # 更新最优发件人
        return ans  # 返回单词数最多且并列时字典序最大的发件人
