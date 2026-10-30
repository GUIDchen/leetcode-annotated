// 题目：139. 单词拆分（Word Break）
// 思路：动态规划，f[i] 表示前缀 s[0..i) 能否被字典完整拆分，枚举最后一段的起点 j 完成转移。
// 时间复杂度：O(n^2) 次子串判断（每次切出子串与查表另计 O(n)）；空间复杂度：O(n)，布尔数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool wordBreak(string s, vector<string>& wordDict) {  // s：待拆分的字符串；wordDict：可用的单词表；返回能否完整拆分
        unordered_set<string> words(wordDict.begin(), wordDict.end());  // 把单词表转成哈希集合，判断某个子串是不是合法单词接近 O(1)
        int n = s.size();  // n：字符串长度，也是 DP 的规模
        bool f[n + 1];  // f[i] 表示 s 的前 i 个字符能否由字典单词拼成
        memset(f, false, sizeof(f));  // 变长数组不会自动清零，先整体置为 false
        f[0] = true;  // 边界：空串视为可以拆分
        for (int i = 1; i <= n; ++i) {  // 按前缀长度从小到大递推，i 即当前要判断的前缀长度
            for (int j = 0; j < i; ++j) {  // 枚举切分点 j：把前缀拆成 s[0..j) 与 s[j..i) 两段
                if (f[j] && words.count(s.substr(j, i - j))) {  // 前半段可拆分，且后半段本身就是字典里的单词
                    f[i] = true;  // 这种切法可行，f[i] 置真
                    break;  // 已经找到一种可行切法，不必再枚举 j
                }
            }
        }
        return f[n];  // 整个字符串能否拆分就是答案
    }
};  // 题解类定义结束