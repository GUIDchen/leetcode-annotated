// 题目：1967. 作为子字符串出现在单词中的字符串数目（Number of Strings That Appear as Substrings in Word）
// 思路：逐个模式串在 word 里做子串查找，find 未命中返回 string::npos，把「是否命中」当成 0/1 累加。
// 时间复杂度：O(sum(|p| * |word|))，每个模式一次朴素匹配；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfStrings(vector<string>& patterns, string word) {  // patterns 是候选子串，word 是主串，返回命中个数
        int ans = 0;  // 统计出现在 word 中的模式数量
        for (auto& p : patterns) {  // 逐个取出候选子串，auto& 避免拷贝
            ans += word.find(p) != string::npos;  // find 命中时返回非 npos，比较结果为 1，直接累加到答案
        }  // for 结束
        return ans;  // 返回满足条件的模式个数
    }  // 方法结束
};  // 类定义结束