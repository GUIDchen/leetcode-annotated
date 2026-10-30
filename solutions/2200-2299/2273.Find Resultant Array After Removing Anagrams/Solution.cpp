// 题目：2273. 移除字母异位词后的结果数组（Find Resultant Array After Removing Anagrams）
// 思路：保留首个单词，之后只把「与前一个单词不是字母异位词」的单词加入答案；用 26 个字母的计数桶判断是否互为字母异位词。
// 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(L)，用于存放结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> removeAnagrams(vector<string>& words) {  // words：输入单词数组；返回删除字母异位词后的数组
        auto check = [](string& s, string& t) -> bool {  // 判断 s 与 t 是否「不是」字母异位词：返回 true 表示 t 需要保留
            if (s.size() != t.size()) {  // 长度不同，不可能是同一组字母的重排
                return true;  // 直接判定为不同，需要保留 t
            }
            int cnt[26]{};  // 26 个小写字母的计数桶；空花括号保证全部初始化为 0
            for (char& c : s) {  // 先统计 s 里每个字母出现了几次
                ++cnt[c - 'a'];  // 字符减去 'a' 即映射到 0~25 的下标
            }
            for (char& c : t) {  // 再用 t 里的字母去抵扣这些计数
                if (--cnt[c - 'a'] < 0) {  // 先减 1 再判断，若变成负数说明 t 中该字母比 s 中多
                    return true;  // 计数对不上，说明不是字母异位词
                }
            }
            return false;  // 所有计数都被抵完，说明二者互为字母异位词，t 应当被删除
        };

        vector<string> ans = {words[0]};  // 第一个单词前面没有词可比，必定保留
        for (int i = 1; i < words.size(); ++i) {  // 从第二个单词开始向右扫描
            if (check(words[i - 1], words[i])) {  // 与原数组中前一个单词比较（字母异位关系可传递，故不必只跟被保留的词比）
                ans.emplace_back(words[i]);  // 不是字母异位词，原地构造把该单词加入答案
            }  // 否则它与前一个单词互为字母异位词，跳过不加
        }
        return ans;  // 返回删除字母异位词后的结果数组
    }
};
