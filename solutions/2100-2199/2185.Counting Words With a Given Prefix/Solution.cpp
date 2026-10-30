// 题目：2185. 统计包含给定前缀的字符串（Counting Words With a Given Prefix）
// 思路：对每个单词调用 find，若前缀首次出现的位置为 0，说明该单词以 pref 开头，把布尔结果累加到答案里。
// 时间复杂度：O(m·n)，m 为单词个数、n 为前缀长度；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int prefixCount(vector<string>& words, string pref) {  // words：单词列表；pref：待匹配前缀
        int ans = 0;  // 计数器：记录以 pref 开头的单词个数
        for (auto& w : words) ans += w.find(pref) == 0;  // find 返回首次出现的位置，等于 0 才表示从头匹配成功
        return ans;  // 返回统计结果
    }  // 方法结束
};  // 类定义结束