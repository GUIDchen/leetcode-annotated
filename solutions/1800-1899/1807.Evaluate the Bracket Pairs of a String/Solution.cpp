// 题目：1807. 替换字符串中的括号内容（Evaluate the Bracket Pairs of a String）
// 思路：先把 knowledge 建成哈希表，再从左到右扫描字符串；遇到括号就整段截出键名并替换，然后跳到右括号继续。
// 时间复杂度：O(n + k)，n 为字符串长度、k 为映射表规模；空间复杂度：O(k)，用于存放哈希表与结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string evaluate(string s, vector<vector<string>>& knowledge) {  // s：待求值的字符串；knowledge：形如 [key, value] 的映射表
        unordered_map<string, string> d;  // 哈希表：把 knowledge 里的键值对存起来，方便 O(1) 查询
        for (auto& e : knowledge) {  // 遍历每一条 [key, value] 记录
            d[e[0]] = e[1];  // 下标 0 是键、下标 1 是值，写入哈希表
        }  // 建表结束
        string ans;  // ans 收集最终结果，边扫描边拼接
        for (int i = 0; i < s.size(); ++i) {  // 从左到右扫描原串；i 在遇到括号时会直接跳到右括号处
            if (s[i] == '(') {  // 遇到左括号，说明接下来是一段待替换的键
                int j = s.find(")", i + 1);  // 找到与之配对的右括号位置 j
                auto t = s.substr(i + 1, j - i - 1);  // 截出括号内部的子串，也就是待查询的键 t
                ans += d.count(t) ? d[t] : "?";  // 表中有这个键就取对应值，否则按题意填一个问号
                i = j;  // 跳过整个括号片段，下一轮直接从右括号之后继续
            } else {  // 普通字符，无需替换
                ans += s[i];  // 原样追加到结果
            }  // if / else 分支结束
        }  // for 结束
        return ans;  // 返回替换完成的结果串
    }  // 方法结束
};  // 类定义结束