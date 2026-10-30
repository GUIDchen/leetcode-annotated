// 题目：811. 子域名访问计数（Subdomain Visit Count）
// 思路：每条记录先取出访问次数，再以空格和点号为分隔，反复截取后缀子域名并累加次数。
// 时间复杂度：O(总字符数)，每个分隔点都截一次后缀；空间复杂度：O(不同子域名个数)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> subdomainVisits(vector<string>& cpdomains) {  // cpdomains 是形如 9001 discuss.leetcode.com 的记录数组
        unordered_map<string, int> cnt;  // 哈希表：子域名 -> 累计访问次数
        for (auto& s : cpdomains) {  // 逐条处理记录
            int i = s.find(' ');  // 找到次数与域名之间的第一个空格位置
            int v = stoi(s.substr(0, i));  // 空格前是数字，转成整型访问次数
            for (; i < s.size(); ++i) {  // 从空格位置向右扫描，遇到每个分隔点就切出一个后缀子域名
                if (s[i] == ' ' || s[i] == '.') {  // 空格或点号都是分隔符，其右侧就是一个合法子域名
                    cnt[s.substr(i + 1)] += v;  // 把该后缀子域名的计数加上本次访问次数
                }  // if 结束
            }  // for 结束
        }  // 外层 for 结束
        vector<string> ans;  // 结果数组，元素形如 次数 + 空格 + 子域名
        for (auto& [s, v] : cnt) {  // 结构化绑定遍历哈希表
            ans.push_back(to_string(v) + " " + s);  // 拼成题目要求的输出格式
        }  // for 结束
        return ans;  // 返回统计结果
    }  // 方法结束
};  // 类定义结束