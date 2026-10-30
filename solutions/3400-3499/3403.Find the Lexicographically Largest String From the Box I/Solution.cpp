// 3403. 从盒子中找出字典序最大的字符串 I / Find the Lexicographically Largest String From the Box I
// 核心思路：其余 numFriends - 1 个朋友至少各分 1 个字符，故以 i 开头的段最长只能取 min(n - i, n - numFriends + 1)，枚举 i 取字典序最大者
// 复杂度：时间 O(n^2)（字符串比较），空间 O(n)
class Solution {  // 定义题目解答类
public:
    string answerString(string word, int numFriends) {  // 方法入口：把 word 切成 numFriends 段，返回其中字典序最大的段
        if (numFriends == 1) {  // 只有一个朋友时整串就是唯一答案
            return word;  // 直接返回原串
        }
        int n = word.length();  // 记录串长
        string ans = "";  // 记录当前字典序最大的段
        for (int i = 0; i < n; ++i) {  // 枚举该段的起点
            string t = word.substr(i, min(n - i, n - (numFriends - 1)));  // 其余段至少各占 1 个字符，故本段长度上限为 min(n - i, n - numFriends + 1)
            if (ans < t) {  // 当前段字典序更大
                ans = t;  // 更新答案
            }
        }
        return ans;  // 返回字典序最大的段
    }
};
