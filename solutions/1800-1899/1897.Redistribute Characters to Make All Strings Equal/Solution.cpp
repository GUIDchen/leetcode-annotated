// 题目：1897. 重新分配字符使所有字符串都相等（Redistribute Characters to Make All Strings Equal）
// 思路：字符可以在任意位置之间自由移动，所以只要每种字母的总出现次数都能被单词个数 n 整除，就能平均分给每个单词。
// 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(1)，只用固定的 26 个计数桶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool makeEqual(vector<string>& words) {  // words：待重新分配字符的字符串数组
        int cnt[26]{};  // 26 个小写字母的计数桶，空花括号表示全部初始化为 0
        for (const auto& w : words) {  // 逐个字符串统计
            for (const auto& c : w) {  // 逐个字符累加
                ++cnt[c - 'a'];  // 字母 c 的次数加一，c - 'a' 把它映射到 0..25
            }
        }
        int n = words.size();  // 字符串个数，字符要平均分给这 n 个字符串
        for (int i = 0; i < 26; ++i) {  // 检查每一种字母
            if (cnt[i] % n != 0) {  // 总次数不能被 n 整除，就无法均分
                return false;  // 直接判定无法做到
            }
        }
        return true;  // 所有字母都能均分，可以做到
    }
};
