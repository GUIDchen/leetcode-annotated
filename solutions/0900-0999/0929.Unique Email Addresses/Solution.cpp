// 题目：929. 独特的电子邮件地址（Unique Email Addresses）
// 思路：按 @ 切出本地名与域名，本地名去掉所有点并截断到第一个 + 之前，拼回后放入哈希集合去重。
// 时间复杂度：O(L)，L 为所有邮件字符总数；空间复杂度：O(L)，用于保存集合中的规范化地址。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numUniqueEmails(vector<string>& emails) {  // emails：原始邮件地址列表
        unordered_set<string> s;  // 哈希集合，用来对规范化后的地址去重
        for (const string& email : emails) {  // 逐个处理每封邮件，用常引用避免字符串拷贝
            size_t atPos = email.find('@');  // 找到 @ 的位置，用它切分本地名与域名
            string local = email.substr(0, atPos);  // @ 之前是本地名
            string domain = email.substr(atPos + 1);  // @ 之后（跳过 @ 本身）是域名
            string t;  // 存放去掉点和 + 后缀之后的本地名
            for (char c : local) {  // 逐字符扫描本地名
                if (c == '.') {  // 规则一：本地名中的点一律忽略
                    continue;  // 直接跳过这个字符
                }  // if 结束
                if (c == '+') {  // 规则二：遇到 + 之后的内容全部丢弃
                    break;  // 直接结束本地名的处理
                }  // if 结束
                t.push_back(c);  // 普通字符保留下来
            }  // for 结束
            s.insert(t + "@" + domain);  // 拼回「规范本地名@域名」并放入集合，重复地址会被自动合并
        }  // for 结束
        return s.size();  // 集合大小就是不同地址的数量
    }  // 方法结束
};  // 类定义结束
