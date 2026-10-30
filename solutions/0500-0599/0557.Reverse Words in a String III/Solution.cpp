// 题目：557. 反转字符串中的单词 III（Reverse Words in a String III）
// 核心思路：用字符串流按空白切出每个单词，逐个反转后再用一个空格拼回去。
// 时间复杂度：O(n)，每个字符只处理常数次；空间复杂度：O(n)，用于存放结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reverseWords(string s) {  // s：以单个空格分隔的句子，返回每个单词内部反转后的句子
        stringstream ss(s);  // 把输入串包成字符串流，便于按空白逐个取词
        string t;  // t 用于临时接收读到的单词
        string ans;  // ans 用于累积最终结果
        while (ss >> t) {  // 每次读取一个单词，读到结尾即退出
            reverse(t.begin(), t.end());  // 原地反转这个单词的字符顺序
            ans += t;  // 把反转后的单词接到答案末尾
            ans.push_back(' ');  // 单词之间补一个空格（最后一个单词后面也会多补一个，稍后删除）
        }  // 读取完所有单词
        ans.pop_back();  // 去掉末尾多余的那个空格
        return ans;  // 返回每个单词都已反转的句子
    }  // 方法结束
};  // 类定义结束
