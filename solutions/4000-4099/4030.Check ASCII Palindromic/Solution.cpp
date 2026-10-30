// 4030. 判断 ASCII 值回文 / Check ASCII Palindromic
// 核心思路：把每个字符展开成 8 位二进制串并依次拼接，再判断拼接后的串是否为回文串。
// 复杂度：时间 O(8n)，空间 O(8n)（n 为字符串长度）。
class Solution {  // 题解类定义
public:  // 公有成员：判题器调用的接口
    bool isPalindromic(string s) {  // 判断 s 中所有字符的 8 位二进制串拼接后是否为回文串
        string t;  // 存放所有字符的 8 位二进制表示
        for (unsigned char c : s) {  // 按无符号字节遍历每个字符，避免符号位干扰
            for (int i = 7; i >= 0; --i) {  // 从高位到低位依次取出 8 个比特
                t += char('0' + ((c >> i) & 1));  // 把第 i 位转成字符 '0' 或 '1' 追加到串尾
            }  // 结束比特枚举
        }  // 结束字符遍历
        return ranges::equal(t, t | views::reverse);  // 比较原串与它的反转串是否相等
    }  // 结束函数
};  // 结束类定义
