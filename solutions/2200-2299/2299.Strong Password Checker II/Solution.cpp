// 题目：2299. 强密码检验器 II（Strong Password Checker II）
// 思路：一次遍历，用位掩码标记小写、大写、数字、特殊字符四类是否出现，同时与前一字符比较排除相邻重复。
// 时间复杂度：O(n)，password 只扫一遍；空间复杂度：O(1)，只用常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool strongPasswordCheckerII(string password) {  // password：待检验的密码串，返回是否满足全部条件
        if (password.size() < 8) {  // 条件一：长度至少 8 位
            return false;  // 长度不够，直接判负
        }  // 长度检查结束
        int mask = 0;  // 位掩码：bit0 小写、bit1 大写、bit2 数字、bit3 其他字符
        for (int i = 0; i < password.size(); ++i) {  // 逐字符扫描
            char c = password[i];  // 当前字符
            if (i && c == password[i - 1]) {  // 条件二：i 大于 0 且与前一字符相同即为相邻重复
                return false;  // 出现相邻重复，判负
            }  // 相邻重复检查结束
            if (c >= 'a' && c <= 'z') {  // 小写字母
                mask |= 1;  // 置上小写字母对应的 bit0
            } else if (c >= 'A' && c <= 'Z') {  // 否则判断大写字母
                mask |= 2;  // 置上大写字母对应的 bit1
            } else if (c >= '0' && c <= '9') {  // 再判断数字
                mask |= 4;  // 置上数字对应的 bit2
            } else {  // 其余字符都按特殊字符处理
                mask |= 8;  // 置上特殊字符对应的 bit3
            }  // 字符分类结束
        }  // 扫描结束
        return mask == 15;  // 四类齐全（15 即 0b1111）才算强密码
    }  // 方法结束
};  // 类定义结束