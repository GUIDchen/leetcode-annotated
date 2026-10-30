// 题目：2042. 检查句子中的数字是否递增（Check if Numbers Are Ascending in a Sentence）
// 思路：istringstream 按空格切词，首字符是数字的词用 stoi 转成整数，逐个判断是否严格递增。
// 时间复杂度：O(n)，每个字符只被切分一次；空间复杂度：O(n)，字符串流与临时单词占用线性空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool areNumbersAscending(string s) {  // s：只含小写字母、空格和数字的句子
        int pre = 0;  // pre：上一个数字，初始为 0 保证第一个数字一定更大
        istringstream is(s);  // 用字符串流把句子按空格切分成一个个单词
        string t;  // t：当前切出的单词
        while (is >> t) {  // 逐个单词处理
            if (isdigit(t[0])) {  // 首字符是数字，说明这个单词就是一个数字
                int cur = stoi(t);  // stoi 把数字串转成整数
                if (pre >= cur) {  // 不大于上一个数字，不满足严格递增
                    return false;  // 出现不严格递增，判定失败
                }
                pre = cur;  // 更新比较基准
            }
        }
        return true;  // 所有数字都严格递增，返回 true
    }
};