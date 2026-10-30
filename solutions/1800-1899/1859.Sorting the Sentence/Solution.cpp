// 题目：1859. 将句子排序（Sorting the Sentence）
// 思路：按空格切分出所有单词，每个单词末位字符就是它的位次号，直接以「编号 - 1」为下标把去掉编号的单词放进结果数组，再按顺序用空格拼成一个句子。
// 时间复杂度：O(L)，L 为句子长度，切分与拼接各扫一遍；空间复杂度：O(L)，存放单词与结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string sortSentence(string s) {  // s：每个单词末尾带 1..9 位次号的乱序句子
        istringstream iss(s);  // 用字符串流按空格切分句子
        string w;  // 暂存当前读出的单词
        vector<string> ws;  // 按原顺序保存所有单词
        while (iss >> w) {  // 逐个单词读取，>> 会自动跳过空白
            ws.push_back(w);  // 收集单词
        }  // 切分结束
        vector<string> ss(ws.size());  // 按位次号直接把单词放到最终位置，省掉排序
        for (auto& w : ws) {  // 遍历每个带编号的单词
            ss[w.back() - '1'] = w.substr(0, w.size() - 1);  // 末位字符是 1..9 的编号，减一得到 0 基下标作为位置，存入去掉编号的单词
        }  // 放置结束
        string ans;  // 拼接结果
        for (auto& w : ss) {  // 按恢复出的正确顺序遍历
            ans += w + " ";  // 每个单词后面加一个空格，稍后统一去掉末尾多余的空格
        }  // 拼接结束
        ans.pop_back();  // 去掉最后一个多余的空格
        return ans;  // 返回排好序的句子
    }  // 方法结束
};  // 类定义结束