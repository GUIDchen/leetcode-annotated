// 题目：3019. 按键变更的次数（Number of Changing Keys）
// 思路：先把整个字符串统一转成小写，消除大小写差异，然后从第 2 个字符开始逐个与前一个字符比较，不同就说明换了一次键。
// 时间复杂度：O(n)，n 为字符串长度，只扫一遍；空间复杂度：O(1)，只用了常数个变量（原地转换小写）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countKeyChanges(string s) {  // s 是按键序列，返回需要变更按键的次数
        transform(s.begin(), s.end(), s.begin(), ::tolower);  // 原地把 s 中所有字符转成小写，因为大小写不同不算换键
        int ans = 0;  // ans 记录按键变更的次数
        for (int i = 1; i < s.size(); ++i) {  // 从第 2 个字符开始，逐个与它的前一个字符比较
            ans += s[i] != s[i - 1];  // s[i] != s[i-1] 为真说明换了键，布尔值 true 当作 1 直接累加到 ans
        }  // for 结束
        return ans;  // 返回按键变更的总次数
    }  // 方法结束
};  // 题解类结束