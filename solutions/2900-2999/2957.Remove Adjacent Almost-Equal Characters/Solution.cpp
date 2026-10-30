// 题目：2957. 消除相邻近似相等字符（Remove Adjacent Almost-Equal Characters）
// 思路：从左往右贪心扫描，只要 word[i] 与 word[i-1] 的字符编码差小于 2 就必须改一次，改完这一对不再冲突，可直接跳过下一位。
// 时间复杂度：O(n)，只扫一遍字符串；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int removeAlmostEqualCharacters(string word) {  // word 是待处理的字符串，返回最少修改次数
        int ans = 0, n = word.size();  // ans 记录最少操作次数，n 是字符串长度
        for (int i = 1; i < n; ++i) {  // 从第二个字符开始，与它的前一个字符比较
            if (abs(word[i] - word[i - 1]) < 2) {  // 编码差为 0 或 1 即为“近似相等”，必须修改其中一个
                ++ans;  // 修改次数加一
                ++i;  // 改掉 word[i] 后它与后一个字符也不再冲突，跳过下一位置，避免重复计数
            }  // 冲突分支结束
        }  // 扫描循环结束
        return ans;  // 返回最少修改次数
    }  // 方法体结束
};  // 题解类结束