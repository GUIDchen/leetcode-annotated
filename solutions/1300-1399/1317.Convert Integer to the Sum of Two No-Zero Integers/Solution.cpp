// 题目：1317. 将整数转换为两个无零整数的和（Convert Integer to the Sum of Two No-Zero Integers）
// 思路：从 1 开始枚举第一个加数 a，令 b = n - a，检查两者十进制写法都不含 0 即返回。
// 时间复杂度：O(n) 级别的枚举，实际很快命中；空间复杂度：O(1)，只用常数字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getNoZeroIntegers(int n) {  // 把 n 拆成两个各位都不含 0 的正整数之和
        for (int a = 1;; ++a) {  // 从小到大枚举第一个加数 a，题目保证一定有解，故省略上界
            int b = n - a;  // 第二个加数由 a 唯一确定
            if ((to_string(a) + to_string(b)).find('0') == -1) {  // 转成字符串后拼接，检查是否含字符 0；find 返回 -1 说明不含 0
                return {a, b};  // 两个加数都无零，即为答案
            }  // 否则继续尝试下一个 a
        }  // 循环结束（题目保证有解，此处不可达）
    }  // 方法结束
};  // 类定义结束