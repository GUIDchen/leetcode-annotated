// 题目：819. 最常见的单词（Most Common Word）
// 思路：用非字母字符作分隔符扫描整段文本，把单词统一转小写，跳过禁用词后用哈希表计数，边计数边记录出现次数最多的单词。
// 时间复杂度：O(n + b)，n 为段落长度、b 为禁用词总长；空间复杂度：O(n + b)，用于哈希表与禁用集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string mostCommonWord(string paragraph, vector<string>& banned) {  // paragraph：整段文本；banned：禁用词列表
        unordered_set<string> s(banned.begin(), banned.end());  // 禁用词放入哈希集合，便于 O(1) 判断
        unordered_map<string, int> counter;  // 哈希表：单词（小写）→ 出现次数
        string ans;  // 目前出现次数最多的单词
        for (int i = 0, mx = 0, n = paragraph.size(); i < n;) {  // i 为扫描下标，mx 记录当前最大词频，n 为段落长度
            if (!isalpha(paragraph[i]) && (++i > 0)) continue;  // 非字母字符（空格/标点）直接跳过，++i 保证循环向前推进
            int j = i;  // j 用于寻找当前单词的右端点
            string word;  // 暂存当前单词，统一转成小写
            while (j < n && isalpha(paragraph[j])) {  // 收集连续的字母，遇到非字母字符就停下
                word.push_back(tolower(paragraph[j]));  // 把字符转小写后追加到单词末尾
                ++j;  // 右端点右移
            }  // 单词收集完毕
            i = j + 1;  // 跳过单词后面的那个分隔符，避免重复处理
            if (s.count(word)) continue;  // 禁用词不参与统计
            ++counter[word];  // 该单词计数加一
            if (counter[word] > mx) {  // 出现了新的最高频词
                ans = word;  // 更新答案
                mx = counter[word];  // 更新最大词频
            }  // if 结束
        }  // for 结束
        return ans;  // 返回出现次数最多的非禁用词
    }  // mostCommonWord 方法结束
};  // Solution 类结束