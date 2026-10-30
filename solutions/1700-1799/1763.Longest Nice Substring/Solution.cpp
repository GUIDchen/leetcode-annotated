// 题目：1763. 最长的美好子字符串（Longest Nice Substring）
// 思路：枚举所有子串的起点 i 与终点 j，用集合记录子串中出现的字符，逐个检查每个字符的大小写伙伴是否也在集合里，取最长者。
// 时间复杂度：O(n^3)，枚举 O(n^2) 个子串且每次 O(n) 检查；空间复杂度：O(n)，集合最多存 52 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestNiceSubstring(string s) {  // s：由大小写字母组成的字符串
        int n = s.size();  // 字符串长度
        int k = -1, mx = 0;  // k 记录最优子串起点，mx 记录其长度；k 为 -1 表示还没找到
        for (int i = 0; i < n; ++i) {  // 枚举子串起点
            unordered_set<char> ss;  // 记录子串 s[i..j] 中出现过的所有字符
            for (int j = i; j < n; ++j) {  // 枚举子串终点，逐步向右扩展
                ss.insert(s[j]);  // 把新字符加入集合
                bool ok = true;  // 先假设当前子串是美好子串
                for (auto& a : ss) {  // 检查集合中的每个字符
                    char b = a ^ 32;  // 大小写字母的 ASCII 只差第 5 位（32），异或 32 即可切换大小写
                    if (!(ss.count(a) && ss.count(b))) {  // a 本身必在集合中，实质是检查其大小写伙伴是否存在
                        ok = false;  // 缺少大小写伙伴，不是美好子串
                        break;  // 无需继续检查，提前退出
                    }
                }
                if (ok && mx < j - i + 1) {  // 是美好子串且长度比已记录的更优
                    mx = j - i + 1;  // 更新最优长度
                    k = i;  // 记录该子串的起点
                }
            }
        }
        return k == -1 ? "" : s.substr(k, mx);  // 从未找到则返回空串，否则截取最优子串
    }
};