// 题目：1451. 重新排列句子中的单词（Rearrange Words in a Sentence）
// 核心思路：先把句子按空格切分成单词，首字母转小写，再按单词长度稳定排序（等长保持原相对顺序），拼接后用空格连接并把首字母改回大写。
// 时间复杂度：O(L + k log k)，L 为句子长度、k 为单词数；空间复杂度：O(L)，存放切分出的所有单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string arrangeWords(string text) {  // 把句子按单词长度重新排列后返回
        vector<string> words;  // 存放切分出来的所有单词
        stringstream ss(text);  // 用字符串流按空白切分 text
        string t;  // 临时变量，存放每次读到的单词
        while (ss >> t) {  // 不断从流中提取单词，直到没有单词为止
            words.push_back(t);  // 把取到的单词依次存入数组，保持原始顺序
        }  // while 循环结束
        words[0][0] = tolower(words[0][0]);  // 首单词的首字母统一转小写（题目要求重排后整句以小写为主处理）
        stable_sort(words.begin(), words.end(), [](const string& a, const string& b) {  // 按单词长度稳定排序，长度相同的单词保持原有先后顺序
            return a.size() < b.size();  // 比较规则：短的单词排在前面
        });  // lambda 与 stable_sort 调用结束
        string ans = "";  // 结果字符串，先置为空串
        for (auto& s : words) {  // 按排好序的顺序依次拼接单词
            ans += s + " ";  // 每个单词后面补一个空格，最后会多出一个空格
        }  // for 循环结束
        ans.pop_back();  // 删掉末尾多余的那个空格
        ans[0] = toupper(ans[0]);  // 把整句的首字母改回大写
        return ans;  // 返回重排后的句子
    }  // arrangeWords 方法结束
};  // 类定义结束（源文件此处无结尾换行，保持原样）