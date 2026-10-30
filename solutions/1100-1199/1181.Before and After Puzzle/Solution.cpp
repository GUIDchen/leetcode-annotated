// 题目：1181. 前后拼接（Before and After Puzzle）
// 思路：对每个短语记录首词与尾词；两两枚举，若 phrases[i] 的尾词等于 phrases[j] 的首词且 i != j，
//       就把两句话重叠掉重复词拼接起来，用集合去重后排序输出。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {  // phrases 为短语列表，返回所有可拼接出的新短语
        int n = phrases.size();  // 短语个数
        pair<string, string> ps[n];  // ps[i] = {首词, 尾词}，避免在二重循环里反复调用 substr 解析
        for (int i = 0; i < n; ++i) {  // 逐个短语预处理
            int j = phrases[i].find(' ');  // 找第一个空格的位置，用来切出首词
            if (j == string::npos) {  // 单词短语没有空格，首尾是同一个词
                ps[i] = {phrases[i], phrases[i]};  // 首尾词都等于它自己
            } else {  // 至少含两个词的情况
                int k = phrases[i].rfind(' ');  // 找最后一个空格的位置，用来切出尾词
                ps[i] = {phrases[i].substr(0, j), phrases[i].substr(k + 1)};  // 首词 = 开头到第一个空格前；尾词 = 最后一个空格之后
            }  // 首尾词提取完毕
        }  // 所有短语预处理完成
        unordered_set<string> s;  // 集合天然去重，避免同一拼接结果重复出现
        for (int i = 0; i < n; ++i) {  // 枚举作为前缀的短语
            for (int j = 0; j < n; ++j) {  // 枚举作为后缀的短语
                if (i != j && ps[i].second == ps[j].first) {  // 不能自己接自己，且前者的尾词必须等于后者的首词
                    s.insert(phrases[i] + phrases[j].substr(ps[i].second.size()));  // 尾词长度就是重叠部分长度，substr 跳过它即可去掉重复词
                }  // 记录一个拼接结果
            }  // 后缀短语枚举结束
        }  // 前缀短语枚举结束
        vector<string> ans(s.begin(), s.end());  // 把集合内容搬到向量里准备排序
        sort(ans.begin(), ans.end());  // 题目要求按字典序升序输出
        return ans;  // 返回去重并排序后的结果
    }  // 方法体结束
};  // 题解类结束