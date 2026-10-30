// 题目：2193. 得到回文串的最少操作次数（Minimum Number of Moves to Make Palindrome）
// 思路：双指针从两端向中间夹逼；对左端字符在右侧找最近的相同字符并一路交换到对称位置，找不到说明它是落单的中位字符，直接累加挪到中间的步数。
// 时间复杂度：O(n²)，每次配对最多交换 O(n) 次；空间复杂度：O(1)，只用了若干下标与计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMovesToMakePalindrome(string s) {  // s：待构造为回文串的字符串
        int n = s.size();  // 字符串长度
        int ans = 0;  // 累计的最少相邻交换次数
        for (int i = 0, j = n - 1; i < j; ++i) {  // i 从左端、j 从右端，向中间夹逼出待处理区间
            bool even = false;  // 本轮是否在右侧找到了与 s[i] 相同的字符
            for (int k = j; k != i; --k) {  // 从最右端向左找与 s[i] 相同的字符
                if (s[i] == s[k]) {  // 找到配对字符
                    even = true;  // 说明 s[i] 不是落单字符
                    for (; k < j; ++k) {  // 把 s[k] 一路相邻交换到对称位置 j
                        swap(s[k], s[k + 1]);  // 与右邻字符交换，等价于把它右移一位
                        ++ans;  // 交换次数加一
                    }  // 内层 for 结束
                    --j;  // 右端已配对完成，右指针左移
                    break;  // 本轮配对结束
                }  // if 结束
            }  // 内层 for 结束
            if (!even) ans += n / 2 - i;  // 找不到配对：它是落单的中位字符，把它挪到中间需要这么多步
        }  // for 结束
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束