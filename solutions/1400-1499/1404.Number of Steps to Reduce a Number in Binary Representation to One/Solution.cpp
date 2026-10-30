// 题目：1404. 将二进制表示减到 1 的步骤数（Number of Steps to Reduce a Number in Binary Representation to One）
// 思路：从最低位向高位模拟「奇加一、偶除二」，用 carry 表示进位；遇到 1 记一次加一操作并产生进位，每处理一位再记一次除以二操作。
// 时间复杂度：O(n)，n 为二进制串长度；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSteps(string s) {  // s 为不含前导零的二进制字符串
        int ans = 0;  // 累计操作步数
        bool carry = false;  // 来自低位的进位标志（由「加一」产生）
        for (int i = s.size() - 1; i; --i) {  // 从最低位扫到下标 1，下标 0 留到最后单独判断
            char c = s[i];  // 取出当前位字符，便于叠加进位
            if (carry) {  // 有进位时先处理 0/1 的翻转
                if (c == '0') {  // 当前位是 0，加进位后变 1
                    c = '1';  // 本位置 1
                    carry = false;  // 进位被消化，不再向高位传递
                } else  // 当前位是 1，加进位后变 0 且继续进位
                    c = '0';  // 本位置 0，carry 保持 true
            }  // 进位处理结束
            if (c == '1') {  // 当前位为奇数，需要执行一次加一
                ++ans;  // 计入这次加一操作
                carry = true;  // 加一后向高位进位
            }  // 加一分支结束
            ++ans;  // 变成偶数后必有一次除以二操作
        }  // 位数循环结束
        if (carry) ++ans;  // 最高位仍有进位说明又多出一步，补记一次
        return ans;  // 返回总步数
    }  // numSteps 方法结束
};  // Solution 类结束