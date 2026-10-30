// 题目：2490. 回环句（Circular Sentence）
// 思路：按空格切出所有单词，检查每个单词的末字符是否等于下一个单词的首字符，最后一个单词接回第一个。
// 时间复杂度：O(n)，切分与检查各线性扫描一遍；空间复杂度：O(n)，保存切出来的全部单词。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    bool isCircularSentence(string sentence) {  // sentence 是以单个空格分隔的句子，判断首尾字符是否首尾相接
        auto ss = split(sentence, ' ');  // 用自定义 split 按空格切成单词数组
        int n = ss.size();  // 单词个数，下面用取模实现回环
        for (int i = 0; i < n; ++i) {  // 逐个单词检查它与下一个单词的衔接
            if (ss[i].back() != ss[(i + 1) % n][0]) {  // 取模把最后一个单词接回第 0 个，比较末字符与首字符
                return false;  // 有一处不衔接，就不是回环句
            }  // 该单词检查完毕
        }  // 所有单词都检查过了
        return true;  // 全部衔接都满足，返回 true
    }  // 方法结束

    vector<string> split(string& s, char delim) {  // 辅助函数：把 s 按 delim 切成若干子串
        stringstream ss(s);  // 用字符串流包装原串，便于 getline 逐段读取
        string item;  // 暂存当前切出的片段
        vector<string> res;  // 保存全部切分结果
        while (getline(ss, item, delim)) {  // 每次读到分隔符 delim 为止，得到一个片段
            res.emplace_back(item);  // 原地构造并追加片段，避免多余拷贝
        }  // 直到字符串流读完，切分结束
        return res;  // 返回切分结果
    }  // 辅助函数结束
};  // 类定义结束