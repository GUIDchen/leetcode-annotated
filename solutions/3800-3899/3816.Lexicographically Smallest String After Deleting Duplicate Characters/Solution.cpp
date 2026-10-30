// 题目：3816. 删除重复字符后的字典序最小字符串（Lexicographically Smallest String After Deleting Duplicate Characters）
// 思路：单调栈 + 剩余计数。只要栈顶字符比当前字符大、且栈顶字符在后面还会再出现（计数大于 1），就弹出栈顶，让更小的字符顶到前面；扫描结束后如果栈顶字符仍有重复副本，再继续弹出，直到每个字符都只剩一个。
// 时间复杂度：O(n)，每个字符最多进栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个字符，计数数组固定 26 项。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string lexSmallestAfterDeletion(string s) {  // s：输入字符串，可以删掉其中重复出现的字符
        int cnt[26]{};  // cnt[c - 'a'] 记录字符 c 当前还剩下多少个可用的副本
        for (char c : s) {  // 先扫一遍，统计每个字符的出现次数
            ++cnt[c - 'a'];  // 对应字符的计数加一
        }
        string stk;  // 单调栈：栈内字符单调不减，保存当前构造出的最优前缀
        for (char c : s) {  // 再按原顺序扫描每个字符
            while (stk.size() && stk.back() > c && cnt[stk.back() - 'a'] > 1) {  // 栈顶比当前字符大，且栈顶后面还会再出现，就可以放心丢弃
                --cnt[stk.back() - 'a'];  // 被丢弃的那个字符可用数量减一
                stk.pop_back();  // 弹出栈顶，让更小的字符 c 站到前面
            }
            stk.push_back(c);  // 当前字符入栈
        }
        while (cnt[stk.back() - 'a'] > 1) {  // 扫描结束后，如果栈顶字符还有重复副本
            --cnt[stk.back() - 'a'];  // 该字符可用数量减一
            stk.pop_back();  // 弹出冗余的尾部字符，使结果字典序更小
        }
        return stk;  // 返回字典序最小的结果
    }
};
