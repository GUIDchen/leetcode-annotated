// 题目：3271. 哈希分割字符串（Hash Divided String）
// 思路：把字符串按长度 k 依次切块，每块内部把字符折算成 0..25 求和后对 26 取模，再映射回小写字母拼成结果。
// 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(n/k)，用于存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string stringHash(string s, int k) {  // s：输入字符串；k：每个块的字符个数；返回各块哈希后拼成的字符串
        string ans;  // ans：保存拼接的结果
        int n = s.length();  // n：字符串长度
        for (int i = 0; i < n; i += k) {  // 每 k 个字符为一个块，i 是当前块的首下标
            int t = 0;  // t：当前块内所有字符折算值之和
            for (int j = i; j < i + k; ++j) {  // 遍历当前块内的每个字符
                t += s[j] - 'a';  // 把字符折算成 0..25 的数字并累加
            }
            int hashedChar = t % 26;  // 对 26 取模，得到哈希后的数字
            ans += ('a' + hashedChar);  // 数字映射回小写字母，追加到结果末尾
        }
        return ans;  // 返回拼好的哈希结果
    }
};
