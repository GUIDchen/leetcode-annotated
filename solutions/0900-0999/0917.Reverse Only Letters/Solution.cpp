// 题目：917. 仅仅反转字母（Reverse Only Letters）
// 思路：左右双指针，跳过非字母字符，遇到两边都是字母就交换，直到两指针相遇。
// 时间复杂度：O(n)，每个字符最多被访问一次；空间复杂度：O(1)，只用了两个指针。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reverseOnlyLetters(string s) {  // s 为输入字符串；返回字母逆序、非字母保持原位的结果
        int i = 0, j = s.size() - 1;  // 双指针：i 从左往右，j 从右往左
        while (i < j) {  // 两指针尚未相遇就继续处理
            while (i < j && !isalpha(s[i])) {  // 左指针跳过非字母字符
                ++i;  // 左指针右移一位
            }  // 结束左指针跳过
            while (i < j && !isalpha(s[j])) {  // 右指针跳过非字母字符
                --j;  // 右指针左移一位
            }  // 结束右指针跳过
            if (i < j) {  // 两指针都指向字母且尚未交叉
                swap(s[i++], s[j--]);  // 交换两个字母，并让两个指针各自内收一步
            }  // 结束 if (i < j)
        }  // 结束 while 循环
        return s;  // 返回处理后的字符串
    }  // 结束 reverseOnlyLetters 方法
};  // 结束 Solution 类