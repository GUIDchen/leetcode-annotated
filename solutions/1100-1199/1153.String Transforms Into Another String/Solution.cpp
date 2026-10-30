// 题目：1153. 字符串转化（String Transforms Into Another String）
// 思路：同一字符必须始终映射到同一字符；两串相同直接成立，否则若 str2 用满 26 个字母就没有空闲字母可做中转，必失败。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用两个长度 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canConvert(string str1, string str2) {  // str1 是原串，str2 是目标串
        if (str1 == str2) {  // 完全相同，无需任何转化
            return true;  // 直接成立
        }  // if 结束
        int cnt[26]{};  // cnt 统计 str2 中每个字母出现的次数
        int m = 0;  // m 记录 str2 中用到的不同字母个数
        for (char& c : str2) {  // 统计目标串用到的字母种类
            if (++cnt[c - 'a'] == 1) {  // 该字母第一次出现
                ++m;  // 种类数加一
            }  // if 结束
        }  // 循环结束
        if (m == 26) {  // 26 个字母全被占用，没有空闲字母可做中转，无法转化
            return false;  // 直接返回失败
        }  // if 结束
        int d[26]{};  // d[a] 记录字符 a 要映射成的字符（存 b + 1 以区分「未映射」）
        for (int i = 0; i < str1.size(); ++i) {  // 逐位检查映射是否一致
            int a = str1[i] - 'a';  // str1 中当前字符的编号
            int b = str2[i] - 'a';  // str2 中当前字符的编号
            if (d[a] == 0) {  // 该字符还没有建立映射
                d[a] = b + 1;  // 建立映射，+1 是为了和默认的 0 区分
            } else if (d[a] != b + 1) {  // 已有映射但与当前要求不符，说明同一字符要变成两个不同字符
                return false;  // 矛盾，返回失败
            }  // else if 结束
        }  // 逐位检查结束
        return true;  // 所有映射都一致，可以转化
    }  // 方法结束
};  // 类定义结束