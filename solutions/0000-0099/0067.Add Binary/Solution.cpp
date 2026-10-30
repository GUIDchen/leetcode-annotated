// 题目：67. 二进制求和（Add Binary）
// 思路：双指针从两个字符串末尾逐位相加，用 carry 保存进位，把结果按低位到高位压入答案，最后整体反转。
// 时间复杂度：O(max(m, n))，只扫描较长串的长度；空间复杂度：O(max(m, n))，用于存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string addBinary(string a, string b) {  // a、b：两个二进制数的字符串表示
        string ans;  // 结果先按低位到高位存放，最后再反转
        int i = a.size() - 1, j = b.size() - 1;  // 两个指针分别指向 a、b 的最低位（字符串末尾）
        for (int carry = 0; i >= 0 || j >= 0 || carry; --i, --j) {  // 只要还有位或还有进位就继续循环
            carry += (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0);  // 把两个当前位（越界则补 0）和进位累加，字符减 '0' 转成数值
            ans.push_back((carry % 2) + '0');  // 当前位的值 = 累加和模 2，加 '0' 转回字符后追加
            carry /= 2;  // 剩余部分除以 2 就是向高位的进位
        }
        reverse(ans.begin(), ans.end());  // 前面是从低位往高位追加的，反转后才是正常的二进制书写顺序
        return ans;  // 返回求和结果
    }
};