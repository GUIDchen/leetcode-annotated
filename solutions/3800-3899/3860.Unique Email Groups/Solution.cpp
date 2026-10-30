// 题目：3860. 不同邮件组（Unique Email Groups）
// 思路：按规则规范化地址——本地名丢掉第一个 '+' 之后的内容、忽略所有 '.'，整体转小写；域名只转小写，最后用哈希集合去重计数。
// 时间复杂度：O(L)，L 为所有地址的总长度；空间复杂度：O(L)，需要存放规范化后的地址。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int uniqueEmailGroups(vector<string>& emails) {  // emails：邮箱地址列表
        unordered_set<string> st;  // 存放规范化后的地址，哈希集合天然去重

        for (auto& email : emails) {  // 逐个处理邮件地址
            int atPos = email.find('@');  // 找到 '@' 的位置，用来切分本地名与域名
            string local = email.substr(0, atPos);  // 本地名：'@' 之前的部分
            string domain = email.substr(atPos + 1);  // 域名：'@' 之后的部分

            int plusPos = local.find('+');  // 查找本地名里第一个 '+'
            if (plusPos != string::npos) {  // 存在 '+' 才需要截断
                local = local.substr(0, plusPos);  // 丢掉第一个 '+' 及其之后的所有内容
            }

            string cleaned;  // 存放去掉点号并转小写后的本地名
            for (char c : local) {  // 逐字符处理本地名
                if (c != '.') {  // 点号在本地名中被忽略
                    cleaned += tolower(c);  // 其余字符转小写后追加
                }
            }

            for (char& c : domain) {  // 逐个处理域名字符
                c = tolower(c);  // 域名只做小写化
            }

            st.insert(cleaned + "@" + domain);  // 拼回完整地址并放入集合
        }

        return st.size();  // 集合大小即可不同邮件组数
    }
};
