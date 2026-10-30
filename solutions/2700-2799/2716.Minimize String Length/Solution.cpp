// 题目：2716. 最小化字符串长度（Minimize String Length）
// 思路：重复字符可以全部删掉，最终只剩每种出现过的字符各一个，因此答案就是不同字符的种数。
// 时间复杂度：O(n)，遍历一次字符串建集合；空间复杂度：O(Σ)，Σ 为字符集大小（本题为 26）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizedStringLength(string s) {  // s：输入字符串，返回最少能剩下的字符个数
        return unordered_set<char>(s.begin(), s.end()).size();  // 用字符区间构造 unordered_set 完成去重，集合大小即不同字符种数
    }
};
