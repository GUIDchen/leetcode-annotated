// 题目：3330. 找到初始输入字符串 I（Find the Original Typed String I）
// 思路：原串至少可以是 word 本身；每一对相邻且相同的字符都可能是一次多按，说明存在另一种初始串，故答案为 1 加这类相邻对的数量。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int possibleStringCount(string word) {  // word 是敲出来的字符串，其中某些字符可能被多敲了一次
        int f = 1;  // 原串至少可以是 word 本身，这一种先计入
        for (int i = 1; i < word.size(); ++i) {  // 从第二个字符开始与前一字符比较
            f += word[i] == word[i - 1];  // 相等说明这一位可能是多敲的，候选数加一（bool 直接参与加法）
        }  // 扫描结束
        return f;  // 返回可能的初始字符串个数
    }  // 方法结束
};  // 类定义结束
