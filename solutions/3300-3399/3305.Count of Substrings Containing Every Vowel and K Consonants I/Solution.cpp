// 题目：3305. 元音辅音字符串计数 I（Count of Substrings Containing Every Vowel and K Consonants I）
// 思路：把「恰好 k 个辅音」转成「至少 k 个」减去「至少 k+1 个」，用滑动窗口分别 O(n) 统计。
// 时间复杂度：O(n)，每个字符至多进出窗口一次；空间复杂度：O(1)，计数器最多存 5 个元音。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOfSubstrings(string word, int k) {  // word：待统计字符串；k：恰好要包含的辅音个数；返回满足条件的子串个数
        auto f = [&](int k) -> int {  // 闭包 f(k)：统计「含全部 5 个元音且辅音数 >= k」的子串个数（至少型）
            int ans = 0;  // ans 累加满足条件的子串数
            int l = 0, x = 0;  // l：窗口左端点；x：窗口内辅音个数
            unordered_map<char, int> cnt;  // cnt：窗口内各元音出现次数，其大小即出现的元音种类数
            auto vowel = [&](char c) -> bool {  // 闭包 vowel：判断字符是否为元音
                return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 五个元音字母之一即为元音
            };
            for (char c : word) {  // 右端点逐个扩展窗口
                if (vowel(c)) {  // 当前字符是元音
                    cnt[c]++;  // 累加该元音的计数
                } else {  // 否则是辅音
                    ++x;  // 辅音计数 +1
                }
                while (x >= k && cnt.size() == 5) {  // 在「辅音数足够且 5 种元音齐全」的前提下尽量收缩左端点
                    char d = word[l++];  // 取出左端点字符并右移左端点
                    if (vowel(d)) {  // 移出的是元音
                        if (--cnt[d] == 0) {  // 该元音计数减到 0
                            cnt.erase(d);  // 从表中删除，保证 cnt.size() 表示元音种类数
                        }
                    } else {  // 移出的是辅音
                        --x;  // 辅音计数 -1
                    }
                }
                ans += l;  // 收缩结束后，左端点取 0..l-1 的窗口都合法，共贡献 l 个
            }
            return ans;  // 返回至少型计数
        };

        return f(k) - f(k + 1);  // 恰好 k 个 = 「至少 k 个」-「至少 k+1 个」
    }
};
