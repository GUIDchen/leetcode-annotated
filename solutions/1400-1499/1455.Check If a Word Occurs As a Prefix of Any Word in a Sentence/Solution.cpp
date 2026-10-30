// 题目：1455. 检查单词是否为句中其他单词的前缀（Check If a Word Occurs As a Prefix of Any Word in a Sentence）
// 思路：用字符串流按空格切分句子，逐词判断 searchWord 是否为该词的前缀（find 返回 0 即前缀），返回首个匹配单词的 1 基下标。
// 时间复杂度：O(L)，L 为句子总长度，每个字符只被扫描常数次；空间复杂度：O(L)，存放切分出的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int isPrefixOfWord(string sentence, string searchWord) {  // sentence：句子；searchWord：待检查的前缀词
        stringstream ss(sentence);  // 把整个句子包装成字符串流，后面用 >> 按键空格逐个读词
        string s;  // s 用来接收每次从流里读出的一个单词
        for (int i = 1; ss >> s; ++i) {  // i 从 1 开始记录单词序号；ss >> s 读取失败时循环结束
            if (s.find(searchWord) == 0) {  // find 返回 0 说明 searchWord 正好从这个单词的开头出现，即它是前缀
                return i;  // 找到第一个匹配的单词，返回它的 1 基下标
            }  // if 语句块结束
        }  // for 循环体结束
        return -1;  // 所有单词都不是以 searchWord 为前缀，返回 -1
    }  // 方法体结束
};  // 类定义结束