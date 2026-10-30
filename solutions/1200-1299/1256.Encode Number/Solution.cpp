// 题目：1256. 加密数字（Encode Number）
// 思路：编码序列是 1、2、3、… 的二进制去掉最高位：先把 num 加 1 转成 32 位二进制串，再丢掉前导零和紧随的那个最高位 1 即可。
// 时间复杂度：O(log num)，bitset 与字符串操作都是常数级 32 位；空间复杂度：O(1)，只用了固定长度的 bitset 与字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string encode(int num) {  // num：加密序列中的下标（从 0 开始）；返回它对应的二进制字符串
        bitset<32> bs(++num);  // 先自增得到 num+1，再放进 32 位定长 bitset 里，得到补零后的二进制表示
        string ans = bs.to_string();  // to_string 输出 32 个字符的 0/1 串，高位补零
        int i = 0;  // i 用来跳过前面的补位 0
        while (ans[i] == '0') {  // 一直跳过前导零
            ++i;  // 每跳过一个 0 就前进一位
        }
        return ans.substr(i + 1);  // i 停在最高位 1 上，从它后面开始截取，正好去掉这个最高位
    }
};