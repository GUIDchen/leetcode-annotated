// 题目：1002. 查找共用字符（Find Common Characters）
// 思路：对 26 个小写字母分别统计它在每个单词中出现次数，取所有单词中的最小值，就是该字符在答案里应出现的次数。
// 时间复杂度：O(L + 26n)，L 为所有单词总长度；空间复杂度：O(26)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> commonChars(vector<string>& words) {  // words：单词数组；返回在所有单词中都出现过的字符（按最少出现次数计）
        vector<int> cnt(26, 20000);  // cnt[c] 记录字符 c 在各单词中出现次数的最小值，初值取一个足够大的数
        for (const auto& w : words) {  // 逐个单词统计各自的字符频次
            vector<int> t(26, 0);  // 当前单词内 26 个字母的出现次数
            for (char c : w) {  // 遍历当前单词的每个字符
                ++t[c - 'a'];  // 用 c - 'a' 把字母映射到 0..25 的下标
            }
            for (int i = 0; i < 26; ++i) {  // 逐个小写字母比较
                cnt[i] = min(cnt[i], t[i]);  // 共用字符必须在每个单词里都出现，因此取各单词中的最小次数
            }
        }
        vector<string> ans;  // 收集最终答案
        for (int i = 0; i < 26; ++i) {  // 按字母表顺序输出
            for (int j = 0; j < cnt[i]; ++j) {  // 该字符一共要出现 cnt[i] 次，就放入 cnt[i] 份
                ans.push_back(string(1, 'a' + i));  // 把字符 'a' + i 构造成长度为 1 的字符串追加到答案
            }
        }
        return ans;  // 返回所有共用字符（含重复份数）
    }
};
