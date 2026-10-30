// 题目：2135. 统计追加字母可以获得的单词数（Count Words Obtained After Adding a Letter）
// 思路：每个单词用 26 位整数做字母出现掩码（题目保证单词内字母互不相同），起始单词掩码存入哈希集合；对每个目标单词枚举被追加的字母 c，把它的比特位异或清除后查集合，命中即说明该目标单词可被得到。
// 时间复杂度：O(L·(n + m))，L 为单词长度；空间复杂度：O(n)，集合保存 n 个起始单词的掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {  // startWords：起始单词表；targetWords：目标单词表
        unordered_set<int> s;  // 集合 s 保存每个起始单词的 26 位字母掩码
        for (auto& w : startWords) {  // 先枚举所有起始单词
            int x = 0;  // x 是当前单词的掩码：第 c-'a' 位为 1 表示含有该字母
            for (char c : w) {  // 逐字符构造掩码
                x |= 1 << (c - 'a');  // 把字母 c 对应的比特位置 1
            }  // 当前单词的掩码构造完毕
            s.insert(x);  // 把掩码加入集合，供目标单词查询
        }  // 起始单词全部处理完
        int ans = 0;  // ans 统计可由起始单词追加一个字母得到的目标单词数
        for (auto& w : targetWords) {  // 再枚举所有目标单词
            int x = 0;  // 目标单词的字母掩码
            for (char c : w) {  // 逐字符构造目标单词的掩码
                x |= 1 << (c - 'a');  // 把字母 c 对应的比特位置 1
            }  // 目标单词的掩码构造完毕
            for (char c : w) {  // 枚举「被追加的那个字母」c，等价于从掩码中把它去掉
                if (s.contains(x ^ (1 << (c - 'a')))) {  // 异或可清掉该比特：若剩余掩码在集合中，说明原单词加一个 c 就能得到目标单词
                    ++ans;  // 计数加一
                    break;  // 同一个目标单词只计一次，立即跳出
                }  // 当前候选字母判定结束
            }  // 被追加字母枚举结束
        }  // 目标单词全部处理完
        return ans;  // 返回可获得的单词数
    }  // wordCount 方法结束
};  // Solution 类结束