// 题目：3518. 最小回文排列 II（Smallest Palindromic Rearrangement II）
// 思路：回文由左半部分唯一决定，故在左半部分上做逐位贪心：按字母序尝试每一位，用多重集排列数判断第 k 小落在哪个分支。
// 时间复杂度：O(|Σ| * n * |Σ|)，排列数带截断；空间复杂度：O(n + |Σ|)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestPalindrome(string s, int k) {  // s：输入字符串；k：字典序序号；返回第 k 小的回文排列，不存在返回空串
        int freq[26]{};  // freq[x]：字母 x 的出现次数，零初始化
        int n = s.size();  // n：字符串长度
        for (char c : s) {  // 遍历字符串的每个字符
            ++freq[c - 'a'];  // 对应字母的计数加一
        }  // 字符遍历结束
        int odd = 0, mid = 26;  // odd：出现奇数次的字母个数；mid：中心字母，26 表示没有
        for (int i = 0; i < 26; ++i) {  // 扫描 26 个字母
            if (freq[i] & 1) {  // 该字母出现奇数次
                ++odd;  // 奇数次字母数加一
                mid = i;  // 记录中心字母
            }  // 奇数判断结束
        }  // 26 个字母扫描结束
        if (odd > 1) {  // 超过一个奇数次字母就无法构成回文
            return "";  // 不存在回文排列，返回空串
        }  // 奇偶性检查结束
        int half[26]{};  // half[x]：左半部分中字母 x 的个数，零初始化
        int halfLen = 0;  // halfLen：左半部分的长度
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个字母
            half[i] = freq[i] / 2;  // 每个字母成对的个数就是左半部分的用量
            halfLen += half[i];  // 累加左半部分长度
        }  // 26 个字母遍历结束
        if (k > countPermutations(half)) {  // 左半部分的不同排列数不足 k 个
            return "";  // 说明整体也没有 k 个回文排列，返回空串
        }  // 总量检查结束
        string pal(n, 0);  // pal：结果回文串，先分配 n 个字符
        int rank = k, pos = 0;  // rank：当前还在找第几小；pos：左半部分的写入位置
        for (int t = 0; t < halfLen; ++t) {  // 逐位确定左半部分的每个字符
            for (int i = 0; i < 26; ++i) {  // 按字母序尝试，保证字典序最小
                if (half[i] == 0) {  // 该字母已经用完
                    continue;  // 换下一个字母
                }  // 用尽判断结束
                --half[i];  // 假设这一位放字母 i
                int suffix = countPermutations(half);  // 固定这一位后，剩余位置能形成的排列数
                if (suffix >= rank) {  // 第 k 小就落在这一分支里
                    pal[pos++] = char('a' + i);  // 确定这一位，写入并后移
                    break;  // 跳出字母尝试
                }  // 分支判断结束
                rank -= suffix;  // 否则跳过整个分支，排名向前扣减
                ++half[i];  // 恢复计数，尝试下一个字母
            }  // 字母尝试结束
        }  // 逐位确定结束
        if (mid < 26) {  // 存在中心字母
            pal[halfLen] = char('a' + mid);  // 把中心字母放到正中间
        }  // 中心字母判断结束
        for (int i = 0; i < halfLen; ++i) {  // 用左半部分对称填充右半部分
            pal[n - 1 - i] = pal[i];  // 镜像位置赋值，保证整体回文
        }  // 镜像填充结束
        return pal;  // 返回第 k 小的回文排列
    }  // 方法结束

private:  // 私有辅助函数，对外不可见
    static constexpr int LIMIT = 1000001;  // 排列数上限，超过即视为「足够大」

    int countPermutations(const int counts[26]) {  // counts：多重集合各字母的个数；返回不同排列数，超过上限时截断
        int remaining = 0;  // remaining：剩余待安排的字符总数
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个字母
            remaining += counts[i];  // 累加字符总数
        }  // 统计结束
        long long perms = 1;  // perms：排列数，用 long long 防止溢出
        for (int i = 0; i < 26; ++i) {  // 逐个字母用组合数相乘
            int count = counts[i];  // 当前字母的个数
            if (count == 0) {  // 该字母没有出现
                continue;  // 跳过
            }  // 跳过分支结束
            int selected = min(count, remaining - count);  // 取较小的一边算组合数，减少循环次数
            long long combos = 1;  // combos：组合数 C(remaining, selected)
            for (int step = 1; step <= selected; ++step) {  // 逐项累乘组合数
                combos = combos * (remaining - step + 1) / step;  // 乘一项除一项，保证中间结果始终是整数
                if (combos >= LIMIT) {  // 已经达到上限
                    combos = LIMIT;  // 截断到上限，避免溢出
                    break;  // 提前结束累乘
                }  // 截断判断结束
            }  // 组合数累乘结束
            perms *= combos;  // 乘上当前字母的组合数
            if (perms >= LIMIT) {  // 排列数超过上限
                return LIMIT;  // 直接返回上限，后续比较仍然成立
            }  // 上限判断结束
            remaining -= count;  // 该字母安排完毕，剩余数量减少
        }  // 字母遍历结束
        return (int) perms;  // 返回排列数，不超过 LIMIT
    }  // 辅助函数结束
};  // 类结束
