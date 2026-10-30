// 题目：2284. 最多单词数的发件人（Sender With Largest Word Count）
// 核心思路：用哈希表按发件人累加单词数（空格数 + 1），再遍历哈希表取单词最多者，并列时取字典序更大的名字。
// 时间复杂度：O(L + n)，L 是全部消息的总长度；空间复杂度：O(n)，哈希表最多保存 n 个发件人。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestWordCount(vector<string>& messages, vector<string>& senders) {  // messages 与 senders 按下标一一对应，第 i 条消息由 senders[i] 发出
        unordered_map<string, int> cnt;  // 哈希表：键是发件人名字，值是他累计发出的单词数
        for (int i = 0; i < messages.size(); ++i) {  // 逐条消息统计单词数
            int v = count(messages[i].begin(), messages[i].end(), ' ') + 1;  // 空格个数加一就是一整条消息的单词数
            cnt[senders[i]] += v;  // 把这条消息的单词数累加到对应发件人名下
        }  // 消息遍历结束
        string ans = senders[0];  // 候选答案先取第一个发件人，保证后面比较时能查到它的单词数
        for (auto& [k, v] : cnt) {  // 结构化绑定遍历哈希表中的每个「名字 → 单词数」
            if (cnt[ans] < v || (cnt[ans] == v && ans < k)) {  // 单词数更多，或数量并列但名字字典序更大，就替换答案
                ans = k;  // 更新当前最优发件人
            }  // 比较分支结束
        }  // 遍历结束
        return ans;  // 返回单词数最多、并列时字典序最大的发件人
    }  // 方法结束
};  // 类定义结束