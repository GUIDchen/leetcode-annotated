// 题目：1662. 检查两个字符串数组是否相等（Check If Two String Arrays are Equivalent）
// 思路：用 std::reduce 把每个字符串数组按顺序拼接成一个字符串，再直接比较两者是否相等。
// 时间复杂度：O(L)，L 为拼接后的总长度；空间复杂度：O(L)，reduce 会生成拼接后的临时字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {  // word1/word2 是两个字符串数组，判断它们按序拼接的结果是否相同
        return reduce(word1.cbegin(), word1.cend()) == reduce(word2.cbegin(), word2.cend());  // reduce 以空串为初值依次拼接所有元素，两个拼接结果相等即返回 true
    }  // 方法结束
};  // 类定义结束