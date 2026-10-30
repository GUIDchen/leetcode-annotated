// 题目：3298. 统计重新排列后包含另一个字符串的子字符串数目 II（Count Substrings That Can Be Rearranged to Contain a String II）
// 思路：与 I 完全相同的滑动窗口：need 记录还差几种字母，窗口满足时不断右移左端点，并累加以当前右端点结尾的合法起点数 l。
// 时间复杂度：O(n + m)，每个字符至多进出窗口一次；空间复杂度：O(1)，两张 26 长度的频次表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long validSubstringCount(string word1, string word2) {  // word1 是长串，word2 是目标串（字符可任意重排）
        if (word1.size() < word2.size()) {  // 长串比目标串还短，不可能包含它
            return 0;  // 直接返回 0
        }  // 分支结束
        int cnt[26]{};  // cnt 记录 word2 中每个字母需要出现的次数
        int need = 0;  // need 记录还有几种字母的频次没被窗口满足
        for (char& c : word2) {  // 统计 word2 中每个字母的出现次数
            if (++cnt[c - 'a'] == 1) {  // 某个字母第一次出现时（自增后为 1）
                ++need;  // 需求的字母种类数加一
            }  // 判断结束
        }  // 频次统计完毕
        long long ans = 0;  // ans 统计合法子串个数
        int win[26]{};  // win 记录当前滑动窗口内每个字母的出现次数
        int l = 0;  // l 是窗口左端点
        for (char& c : word1) {  // 右端点逐字符向右扩展
            int i = c - 'a';  // 把当前字符换算成 0..25 的字母下标
            if (++win[i] == cnt[i]) {  // 该字母在窗口中的数量刚好补齐需求
                --need;  // 少了一种未满足的字母
            }  // 判断结束
            while (need == 0) {  // 窗口已覆盖 word2 的全部需求，尝试收缩左端点
                i = word1[l] - 'a';  // 取出左端点字符的字母下标
                if (win[i] == cnt[i]) {  // 移出这个字符后它的数量就不够了
                    ++need;  // 重新标记为未满足
                }  // 判断结束
                --win[i];  // 真正把左端点字符移出窗口
                ++l;  // 左端点右移
            }  // 收缩结束，此时窗口刚变得不合法
            ans += l;  // 以当前字符结尾、起点在 0..l-1 的子串都合法，共 l 个
        }  // 本轮扩展结束
        return ans;  // 返回合法子串总数
    }  // 方法结束
};  // Solution 类定义结束
