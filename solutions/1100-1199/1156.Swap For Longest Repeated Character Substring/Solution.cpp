// 题目：1156. 单字符重复子串的最大长度（Swap For Longest Repeated Character Substring）
// 思路：统计每个字符总数，再双指针找出「连续段 + 隔一个字符 + 连续段」，长度受该字符总数限制。
// 时间复杂度：O(n)；空间复杂度：O(1)（字符集固定为 26 个字母）。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int maxRepOpt1(string text) {  // 允许交换一次任意两个字符，求同字符重复子串的最大长度
        int cnt[26] = {0};  // 统计每个字母在整串中的总出现次数
        for (char& c : text) {  // 遍历字符串的每个字符
            ++cnt[c - 'a'];  // 对应字母的计数加一
        }  // 结束统计
        int n = text.size();  // 字符串长度
        int ans = 0, i = 0;  // ans 记录答案；i 是当前连续段的起点
        while (i < n) {  // 逐个处理连续相同字符段
            int j = i;  // j 用于探测当前段 [i, j) 的右端点
            while (j < n && text[j] == text[i]) {  // 向后找与 text[i] 相同的连续字符
                ++j;  // 右端点右移
            }  // 结束当前段探测
            int l = j - i;  // l：当前连续段的长度
            int k = j + 1;  // k 从隔一个位置开始，即跳过中间被换掉的那个字符
            while (k < n && text[k] == text[i]) {  // 找下一段同字符的连续段
                ++k;  // 继续右移
            }  // 结束第二段探测
            int r = k - j - 1;  // r：第二段长度（两段中间隔了 1 个字符）
            ans = max(ans, min(l + r + 1, cnt[text[i] - 'a']));  // 两段拼起来最多用完全部同字母，取较小值
            i = j;  // 从下一段继续扫描
        }  // 结束主循环
        return ans;  // 返回最大长度
    }  // 方法结束
};  // 类定义结束