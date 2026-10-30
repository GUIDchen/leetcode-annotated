// 题目：2114. 句子中的最多单词数（Maximum Number of Words Found in Sentences）
// 思路：单个句子的单词数 = 空格数 + 1；逐句数空格，取最大值。
// 时间复杂度：O(L)，L 为所有句子的总字符数；空间复杂度：O(1)，只用常数个变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏：取两数较大值，避免为这段判题片段额外引入头文件

int mostWordsFound(char** sentences, int sentencesSize) {  // sentences：句子字符串数组；sentencesSize：句子个数；返回单词数的最大值
    int ans = 0;  // 记录目前见过的最大单词数
    for (int i = 0; i < sentencesSize; i++) {  // 逐句统计
        char* s = sentences[i];  // 当前句子
        int count = 1;  // 单词数 = 空格数 + 1，所以初值为 1
        for (int j = 0; s[j]; j++) {  // 顺序扫描句子直到结束符 '\0'
            if (s[j] == ' ') {  // 遇到一个空格
                count++;  // 说明又隔出一个单词
            }  // 非空格字符直接跳过
        }  // 本句扫描结束
        ans = max(ans, count);  // 用当前句子的单词数更新全局最大值
    }  // 所有句子处理完毕
    return ans;  // 返回最多单词数
}  // mostWordsFound 函数结束