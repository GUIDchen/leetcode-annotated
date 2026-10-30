// 题目：3926. 有效单词计数（Count Valid Word Occurrences）
// 思路：先把 chunks 拼成 s，再用双指针切词——空格与孤立的 '-' 是分隔符，被小写字母两侧包围的 '-' 属于单词内部；用哈希表统计词频后逐个回答查询。
// 时间复杂度：O(|s| + 查询总长度)；空间复杂度：O(|s|)，哈希表最多存下所有不同的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {  // chunks：待拼接的片段；queries：要统计出现次数的单词
        string s = "";  // 拼接后的完整字符串
        for (const string& chunk : chunks) {  // 按顺序拼接每个片段
            s += chunk;  // 追加到 s 的末尾
        }  // 拼接结束
        int n = s.length();  // 拼接后的总长度
        unordered_map<string, int> cnt;  // 哈希表：单词 → 出现次数
        int i = 0;  // 当前扫描位置
        while (i < n) {  // 逐个单词地扫描整个字符串
            if (s[i] == ' ' || s[i] == '-') {  // 当前字符是空格或孤立的连字符，属于分隔符
                i++;  // 跳过分隔符
                continue;  // 进入下一轮扫描
            }  // 分隔符分支结束
            int j = i;  // j 从 i 出发向右寻找单词结尾
            while (j < n && s[j] != ' ' && (s[j] != '-' || (j + 1 < n && s[j + 1] != ' ' && s[j + 1] != '-'))) {  // 不是空格，且 '-' 后面紧跟字母时该 '-' 属于单词内部
                j++;  // 单词长度扩展一位
            }  // 单词扫描结束
            cnt[s.substr(i, j - i)]++;  // 用 s[i, j) 切出单词并累加计数
            i = j;  // 从单词结尾继续扫描
        }  // 全部单词处理结束
        vector<int> ans;  // 存放每个查询的答案
        ans.reserve(queries.size());  // 预留空间，避免 push_back 反复扩容
        for (const string& q : queries) {  // 逐个回答查询
            ans.push_back(cnt[q]);  // 未出现过的单词经默认构造取值为 0
        }  // 查询处理结束
        return ans;  // 返回答案数组
    }  // 方法结束
};  // 类定义结束
