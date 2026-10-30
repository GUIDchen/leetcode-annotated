// 题目：2114. 句子中的最多单词数（Maximum Number of Words Found in Sentences）
// 思路：单个句子的单词数 = 该句空格数 + 1；逐句统计空格数并取最大值。
// 时间复杂度：O(L)，L 为所有句子的总字符数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mostWordsFound(vector<string>& sentences) {  // sentences：所有句子；返回单词数的最大值
        int ans = 0;  // 记录目前的最大单词数
        for (auto& s : sentences) {  // 逐句统计，用引用避免字符串拷贝
            int cnt = 1 + count(s.begin(), s.end(), ' ');  // 单词数 = 空格数 + 1，std::count 负责统计空格
            ans = max(ans, cnt);  // 用当前句子的单词数更新最大值
        }  // 所有句子处理完毕
        return ans;  // 返回最多单词数
    }  // mostWordsFound 方法结束
};  // Solution 类定义结束