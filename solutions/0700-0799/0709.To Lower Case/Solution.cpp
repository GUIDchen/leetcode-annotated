// 题目：709. 转换成小写字母（To Lower Case）
// 思路：逐字符扫描，只把大写字母 A 到 Z 通过按位或 32 变成小写，其余字符原样保留。
// 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，就地修改传入字符串的副本。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口：toLowerCase 方法
    string toLowerCase(string s) {  // 就地把 s 中的大写字母转成小写并返回
        for (char& c : s) {  // 用引用遍历，改动会直接写回字符串元素
            if (c >= 'A' && c <= 'Z') {  // 只处理大写字母 A 到 Z
                c |= 32;  // 大小写的 ASCII 码相差 32，按位或 32 即可小写化
            }
        }  // for 循环结束
        return s;  // 返回处理后的字符串
    }  // 方法结束
};  // 类定义结束