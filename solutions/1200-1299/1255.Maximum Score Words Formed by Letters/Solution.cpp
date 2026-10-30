// 题目：1255. 得分最高的单词集合（Maximum Score Words Formed by Letters）
// 思路：单词最多 14 个，直接枚举所有子集（用二进制位表示选不选）；对每个子集统计字母用量，若不超过可用字母就按 score 累计得分，取最大值。
// 时间复杂度：O(2^n · n · L)，L 为单词平均长度（外加每子集 26 次统计）；空间复杂度：O(1)，只用了两个长度 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {  // words：候选单词；letters：可用字母（每个只能用一次）；score：26 个字母各自的得分
        int cnt[26]{};  // cnt 统计手中每个字母的可用次数，花括号初始化保证全部为 0
        for (char& c : letters) {  // 逐个遍历可用字母
            cnt[c - 'a']++;  // 把字符折算成 0~25 的下标并累加计数
        }
        int n = words.size();  // n 是单词个数，决定了子集枚举的范围
        int ans = 0;  // ans 记录所有可行子集中的最高得分
        for (int i = 0; i < 1 << n; ++i) {  // 用 n 位二进制数 i 枚举所有子集：第 j 位为 1 表示选第 j 个单词
            int cur[26]{};  // cur 统计当前子集里每个字母被用掉多少次
            for (int j = 0; j < n; ++j) {  // 逐位检查第 j 个单词是否被选中
                if (i >> j & 1) {  // 第 j 位为 1，说明该单词参与本子集
                    for (char& c : words[j]) {  // 把这个单词的每个字符也计入用量
                        cur[c - 'a']++;  // 累加该字符的消耗次数
                    }
                }
            }
            bool ok = true;  // ok 表示当前子集是否只用了手里有的字母
            int t = 0;  // t 累积当前子集能拿到的分数
            for (int j = 0; j < 26; ++j) {  // 逐字母核对用量是否够用，顺带算分
                if (cur[j] > cnt[j]) {  // 某个字母用得比手里的还多，本子集不合法
                    ok = false;  // 标记为不合法
                    break;  // 没必要继续核对，直接跳出
                }
                t += cur[j] * score[j];  // 字母够用则累加「该字母个数 × 该字母分值」
            }
            if (ok && ans < t) {  // 子集合法且得分更高时更新答案
                ans = t;  // 记录新的最高分
            }
        }
        return ans;  // 返回所有可行子集中的最高得分
    }
};