// 题目：2414. 最长的字母序连续子字符串的长度（Length of the Longest Alphabetical Continuous Substring）
// 思路：一次扫描相邻字符，若 ASCII 码恰好差 1 则当前连续段长度加一，否则把长度重置为 1，过程中维护最大值。
// 时间复杂度：O(n)，只遍历一遍字符串；空间复杂度：O(1)，只用常数个计数变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏：返回两个值中较大的那个

int longestContinuousSubstring(char* s) {  // s 是只含小写字母的字符串，返回最长字母序连续子串的长度
    int n = strlen(s);  // 先取字符串长度，避免循环里重复求长度
    int ans = 1, cnt = 1;  // ans 保存历史最长长度；cnt 保存当前连续段长度，单个字符长度为 1
    for (int i = 1; i < n; ++i) {  // 从第二个字符开始，逐个与前一个字符比较
        if (s[i] - s[i - 1] == 1) {  // 相邻字符的 ASCII 码相差 1，说明字母序连续
            ++cnt;  // 当前连续段长度加一
            ans = max(ans, cnt);  // 用当前长度刷新历史最大值
        } else {  // 连续性中断
            cnt = 1;  // 以当前字符为起点重新计数
        }
    }
    return ans;  // 返回最长字母序连续子串的长度
}
