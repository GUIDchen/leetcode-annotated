// 题目：2788. 按分隔符拆分字符串（Split Strings by Separator）
// 思路：对每个单词用 istringstream + getline 按分隔符切段，丢弃空串后汇总。
// 时间复杂度：O(总字符数)，每个字符只被扫描一次；空间复杂度：O(总字符数)，用于存放答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {  // words：待拆分的字符串数组；separator：分隔符字符
        vector<string> ans;  // ans 收集所有非空子串
        for (const auto& w : words) {  // 逐个单词处理
            istringstream ss(w);  // 用字符串流包装当前单词，方便按分隔符读取
            string s;  // s 接收每次切出来的一段
            while (getline(ss, s, separator)) {  // getline 以 separator 为界反复读取，直到流结束
                if (!s.empty()) {  // 跳过空段：开头、结尾或连续分隔符都会切出空串
                    ans.push_back(s);  // 非空段才计入答案
                }  // if 结束
            }  // while 结束
        }  // for 结束
        return ans;  // 返回拆分并过滤后的结果
    }  // 方法结束
};  // 类定义结束