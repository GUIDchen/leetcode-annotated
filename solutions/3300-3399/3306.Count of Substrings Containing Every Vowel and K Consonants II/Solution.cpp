// 题目：3306. 元音辅音字符串计数 II（Count of Substrings Containing Every Vowel and K Consonants II）
// 思路：先用滑动窗口求 f(k) = 「辅音数至少 k 且五种元音齐全」的子串数，答案 = f(k) - f(k + 1)，因为「恰好 k 个辅音」正是「至少 k 个」去掉「至少 k+1 个」。
// 复杂度：时间 O(n)，窗口左右端点各自最多移动 n 次，且只调用两次 f；空间 O(1)，哈希表最多只有 5 个元音键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countOfSubstrings(string word, int k) {  // word：只含小写字母的字符串；k：要求的辅音个数；返回满足条件的子串数
        auto f = [&](int k) -> long long {  // 定义辅助函数 f(k)：统计「至少 k 个辅音且五种元音齐全」的子串个数
            long long ans = 0;  // 累加答案，子串个数最多约 n^2/2，必须用 long long 防溢出
            int l = 0, x = 0;  // l：滑动窗口的左端点；x：窗口内辅音字符的数量
            unordered_map<char, int> cnt;  // 记录窗口内每个元音的出现次数，size() 就是当前出现的元音种类数
            auto vowel = [&](char c) -> bool {  // 辅助 lambda：判断字符 c 是否为五种元音之一
                return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 依次与五个元音字母比较，命中任意一个即为元音
            };  // 内层 lambda 定义结束
            for (char c : word) {  // 枚举右端点：依次把 word 中的字符并入窗口
                if (vowel(c)) {  // 当前字符是元音
                    cnt[c]++;  // 对应元音在窗口中的计数加一
                } else {  // 当前字符是辅音
                    ++x;  // 窗口内辅音数量加一
                }  // if/else 分支结束
                while (x >= k && cnt.size() == 5) {  // 窗口已满足「辅音数 >= k 且五种元音齐全」时，反复右移左端点收缩，直到条件被破坏
                    char d = word[l++];  // 取出窗口最左边的字符 d，同时把左端点右移一位
                    if (vowel(d)) {  // 被移出窗口的字符是元音
                        if (--cnt[d] == 0) {  // 该元音计数减一；减到 0 说明这种元音已经不在窗口里了
                            cnt.erase(d);  // 从哈希表中删除该键，保证 size() 始终等于「当前出现的元音种类数」
                        }  // 内层 if 结束
                    } else {  // 被移出窗口的字符是辅音
                        --x;  // 窗口内辅音数量减一
                    }  // if/else 分支结束
                }  // while 收缩结束
                ans += l;  // 以当前位置为右端点时，左端点取 0..l-1 都满足条件，共 l 个子串，累加到答案
            }  // for 循环结束
            return ans;  // 返回本轮 f(k) 的统计结果
        };  // 辅助 lambda 定义结束

        return f(k) - f(k + 1);  // 「至少 k 个」减去「至少 k+1 个」，恰好剩下「正好 k 个辅音」的子串数
    }  // 方法结束
};  // 类定义结束
