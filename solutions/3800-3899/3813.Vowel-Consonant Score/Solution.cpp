// 3813. Vowel-Consonant Score | 元音辅音得分
// 核心思路：一次遍历只统计字母，先累计字母总数 c，再累计元音 v；辅音数 = c - v，题目要求 v 除以辅音数向下取整，辅音数为 0 时返回 0。
// 复杂度：时间 O(|s|)；空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有接口
    int vowelConsonantScore(string s) {  // 返回元音数除以辅音数（向下取整）的得分，没有辅音时返回 0
        int v = 0, c = 0;  // v 统计元音个数，c 先统计字母总个数
        for (char ch : s) {  // 逐字符扫描
            if (isalpha(ch)) {  // 只处理字母，忽略数字与其它符号
                c++;  // 字母总数加一
                if (string("aeiou").find(ch) != string::npos) {  // 在 aeiou 中查找该字符，找不到返回 npos
                    v++;  // 是元音，元音数加一
                }  // 结束元音判断
            }  // 结束字母判断
        }  // 扫描结束
        c -= v;  // 字母总数减去元音数，得到辅音数
        return c == 0 ? 0 : v / c;  // 辅音数为 0 时返回 0，否则返回整数除法结果（自动向下取整）
    }  // 方法结束
};  // 类定义结束
