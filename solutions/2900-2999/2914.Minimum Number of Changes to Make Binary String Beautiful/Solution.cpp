// 题目：2914. 使二进制字符串变美丽的最少修改次数（Minimum Number of Changes to Make Binary String Beautiful）
// 思路：把字符串按长度 2 切成若干块，块内两个字符不同就必须改掉一个，各块互不影响，答案是这些块的个数。
// 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minChanges(string s) {  // s 是长度为偶数的二进制串；返回把它切成若干『00/11』块所需的最少修改次数
        int ans = 0;  // ans 记录最少修改次数
        int n = s.size();  // 字符串长度，题目保证是偶数
        for (int i = 1; i < n; i += 2) {  // 每两个字符一组，i 指向每组的第二个下标
            ans += s[i] != s[i - 1];  // 组内两个字符不同就必须改其中一个，把比较结果（0 或 1）累加到答案
        }
        return ans;  // 返回最少修改次数
    }
};