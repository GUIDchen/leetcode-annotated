// 题目：1935. 可以输入的最大单词数（Maximum Number of Words You Can Type）
// 思路：用 26 个布尔位记录坏字母，把 text 按空格切分成单词，逐词检查是否含坏字母。
// 时间复杂度：O(|text| + |brokenLetters|)；空间复杂度：O(1)，只有 26 个标记位。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int canBeTypedWords(string text, string brokenLetters) {  // 返回能够完整敲出的单词数
        bool s[26]{};  // 记录每个字母是否损坏，花括号等价于初始化为 false
        for (char c : brokenLetters) {  // 遍历所有损坏的字母
            s[c - 'a'] = true;  // 把对应位置标记为损坏
        }  // for 结束
        int ans = 0;  // 可敲出的单词计数器
        stringstream ss(text);  // 用字符串流把 text 按空白切分成单词
        string w;  // 存放当前取出的单词
        while (ss >> w) {  // 依次取出每个单词，流耗尽时结束
            for (char c : w) {  // 检查单词中的每个字母
                if (s[c - 'a']) {  // 该字母已损坏，这个单词敲不出来
                    --ans;  // 先抵消下面无条件的自增，表示本词不计入
                    break;  // 只要有一个坏字母就跳出检查
                }  // if 结束
            }  // 内层 for 结束
            ++ans;  // 先假定单词可以敲出，坏字母的情况已被上面的自减抵消
        }  // while 结束
        return ans;  // 返回可敲出的单词数
    }  // 方法结束
};  // 类结束
