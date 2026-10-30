// 题目：2325. 解密消息（Decode the Message）
// 核心思路：用 128 大小的字符数组当映射表，按 key 中字母首次出现的顺序依次分配 a、b、c……，再原地替换 message。
// 时间复杂度：O(m + n)，m、n 分别为 key 与 message 的长度；空间复杂度：O(1)，映射表大小固定为 128。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string decodeMessage(string key, string message) {  // key：密码表；message：待解密消息
        char d[128]{};  // 映射表，全零初始化：d[c] 为 0 表示字符 c 还没被分配
        d[' '] = ' ';  // 空格映射到自身，保持原样
        char i = 'a';  // 下一个要分配的明文字母
        for (char& c : key) {  // 按密码表的顺序扫描每个字符
            if (!d[c]) {  // 该字符还没建立映射（空格已被预置，因此会被跳过）
                d[c] = i++;  // 建立映射并让明文字母向后推进
            }  // 结束本轮判断
        }  // 结束建表循环
        for (char& c : message) {  // 遍历密文
            c = d[c];  // 原地查表替换成明文
        }  // 结束替换循环
        return message;  // 返回解密后的消息
    }
};