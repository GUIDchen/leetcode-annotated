// 题目：422. 有效的单词方块（Valid Word Square，会员题）
// 思路：单词方块要求第 i 行第 j 列等于第 j 行第 i 列；逐字符检查对称位置是否相等，同时防止行列长度不齐导致越界。
// 时间复杂度：O(L)，L 是所有单词的字符总数；空间复杂度：O(1)，只用了下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validWordSquare(vector<string>& words) {  // words 是单词列表，判断这些单词是否构成有效的单词方块
        int m = words.size();  // m 是行数，同时也是转置后应有的行数
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            int n = words[i].size();  // n 是当前单词的长度
            for (int j = 0; j < n; ++j) {  // 遍历当前单词的每个字符
                if (j >= m || i >= words[j].size() || words[i][j] != words[j][i]) {  // 下标越界或对称位置字符不相等，说明不是单词方块
                    return false;  // 立即判假
                }  // if 分支结束
            }  // 列循环结束
        }  // 行循环结束
        return true;  // 所有位置都对称相等，返回真
    }  // validWordSquare 方法结束
};  // Solution 类结束