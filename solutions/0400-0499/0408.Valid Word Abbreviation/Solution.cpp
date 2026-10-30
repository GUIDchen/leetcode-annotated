// 题目：408. 有效单词缩写（Valid Word Abbreviation）
// 思路：双指针扫描 word 与 abbr，遇到数字累积成计数器，遇到字母先跳过该数量的字符再逐字比对。
// 时间复杂度：O(m + n)，两个指针都只单向前进；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validWordAbbreviation(string word, string abbr) {  // word 是原词，abbr 是待校验的缩写
        int m = word.size(), n = abbr.size();  // 两个字符串的长度
        int i = 0, j = 0, x = 0;  // i 指向 word 当前位，j 指向 abbr 当前位，x 累积缩写里的数字
        for (; i < m && j < n; ++j) {  // 双指针同步扫描，j 每轮固定自增，i 的推进由分支决定
            if (isdigit(abbr[j])) {  // 遇到数字说明这是缩写长度的一部分
                if (abbr[j] == '0' && x == 0) {  // 数字不能有前导零，否则缩写非法
                    return false;  // 立即判定不合法
                }  // 内层 if 结束
                x = x * 10 + (abbr[j] - '0');  // 把这一位数字拼接到当前数值（字符减 '0' 得到数值）
            } else {  // 否则遇到字母：缩写段结束，先跳过 x 个字符再比对
                i += x;  // 按缩写给出的长度跳过 x 个字符
                x = 0;  // 计数器清零，供后面的数字重新累加
                if (i >= m || word[i] != abbr[j]) {  // 越界或字母对不上都说明缩写无效
                    return false;  // 返回不合法
                }  // 内层 if 结束
                ++i;  // 该字母比对成功，word 指针前进一位
            }  // else 分支结束
        }  // 循环结束：此时可能有一方先走到末尾
        return i + x == m && j == n;  // 两侧必须恰好同时走完：i + x 结算尾部数字，j == n 表示 abbr 也已耗尽
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）