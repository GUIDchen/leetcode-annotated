// 题目：1961. 检查字符串是否为数组前缀（Check If String Is a Prefix of Array）
// 思路：按顺序把 words 里的词拼到临时串 t 上，边拼边比较长度；超过 s 长度即失败，相等则比较内容。
// 时间复杂度：O(L)，L 为不超过 s 长度的字符总数；空间复杂度：O(L)，用于暂存拼接结果 t。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPrefixString(string s, vector<string>& words) {  // s 是目标字符串，words 是候选词数组
        string t;  // t 依次拼接 words 的前缀，用来与 s 比较
        for (auto& w : words) {  // 按顺序取出每个词
            t += w;  // 把当前词接到 t 末尾
            if (t.size() > s.size()) {  // 拼出来的长度已经超过 s，说明不可能再相等
                return false;  // 提前判定不成立，省去后面的无谓比较
            }  // 结束 if
            if (t.size() == s.size()) {  // 长度刚好等于 s 的长度，只需比较内容
                return t == s;  // 相同就是前缀，不同就不是（此处必须返回）
            }  // 结束 if
        }  // 结束 for
        return false;  // 所有词用完仍未达到 s 的长度，说明 s 比拼接结果长
    }  // 结束方法
};  // 结束类