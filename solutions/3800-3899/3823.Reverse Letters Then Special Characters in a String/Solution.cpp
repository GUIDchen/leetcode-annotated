// 3823. Reverse Letters Then Special Characters in a String | 3823. 反转一个字符串里的字母后反转特殊字符
// 核心思路：先把字母与非字母分别收集到两个字符串，再从左往右扫原串、从各自尾部取回，实现两类字符各自逆序
// 复杂度：时间 O(n)，空间 O(n)
class Solution {
public:
    string reverseByType(string s) {  // 把字母与非字母分别原地逆序，其余位置类型不变
        string a, b;  // a 存所有字母，b 存所有非字母字符

        for (char c : s) {  // 第一遍遍历：按字符类别分组
            if (isalpha(c)) {  // 当前字符是字母
                a.push_back(c);  // 放入字母容器
            } else {  // 当前字符不是字母
                b.push_back(c);  // 放入非字母容器
            }
        }

        int j = a.size(), k = b.size();  // j、k 分别是两个容器的尾部下标
        for (int i = 0; i < s.size(); ++i) {  // 第二遍遍历：把各自容器里的字符从尾部倒序填回原位
            if (isalpha(s[i])) {  // 原位置需要放字母
                s[i] = a[--j];  // 取字母容器的末尾元素，实现字母整体逆序
            } else {  // 原位置需要放特殊字符
                s[i] = b[--k];  // 取非字母容器的末尾元素，实现特殊字符整体逆序
            }
        }

        return s;  // 返回处理后的字符串
    }
};
