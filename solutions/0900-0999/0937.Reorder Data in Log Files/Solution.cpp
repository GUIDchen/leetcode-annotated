// 题目：937. 重新排列日志文件（Reorder Data in Log Files）
// 思路：用稳定排序加自定义比较器。字母日志按「内容、再标识符」排序并整体排在数字日志之前，数字日志之间保持原有相对顺序。
// 时间复杂度：O(n log n * L)，每次比较都要切出长度为 L 的子串；空间复杂度：O(n)，stable_sort 需要额外缓冲。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> reorderLogFiles(vector<string>& logs) {  // logs 是若干条日志，返回重排后的日志数组
        stable_sort(logs.begin(), logs.end(), [](const string& log1, const string& log2) {  // stable_sort 保证“相等”的日志保持输入顺序，正好满足数字日志不乱序的要求
            int idx1 = log1.find(' ');  // 第一个空格是标识符与内容的分界
            int idx2 = log2.find(' ');  // 另一条日志的分界位置
            string id1 = log1.substr(0, idx1);  // 标识符（空格之前的部分）
            string id2 = log2.substr(0, idx2);  // 另一条日志的标识符
            string content1 = log1.substr(idx1 + 1);  // 标识符之后的内容，用来判断日志类型并参与比较
            string content2 = log2.substr(idx2 + 1);  // 另一条日志的内容
  // 内容首字符是字母 → 字母日志
            bool isLetter1 = isalpha(content1[0]);  // 另一条日志的类型
            bool isLetter2 = isalpha(content2[0]);  // 两条都是字母日志时，按内容字典序排
  // 内容不同就先比内容
            if (isLetter1 && isLetter2) {  // 返回内容的字典序比较结果
                if (content1 != content2) {  // 内容相同则按标识符字典序排
                    return content1 < content2;  // 返回标识符的比较结果
                }
                return id1 < id2;  // 否则：内容首字符是字母的排在数字日志前面
            }
  // 排序结果已经写回 logs，直接返回
            return isLetter1 > isLetter2;  // 函数结束
        });

        return logs;
    }
};
