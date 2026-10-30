// 题目：2283. 判断一个数的数字计数是否等于数位的值（Check if Number Has Equal Digit Count and Digit Value）
// 核心思路：用长度 10 的计数数组统计每个数字字符的出现次数，再逐位比较计数与字符所表示的数字是否相等。
// 时间复杂度：O(n)，两趟线性遍历字符串；空间复杂度：O(1)，计数数组长度固定为 10。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool digitCount(string num) {  // num：只含数字字符的字符串，第 i 位声明数字 i 出现 num[i] 次
        int cnt[10]{};  // 10 个数字的出现次数，值初始化为 0
        for (char& c : num) {  // 第一趟：按引用遍历每个字符，避免不必要的拷贝
            ++cnt[c - '0'];  // 字符减 '0' 得到数值，对应计数加一
        }  // 第一趟结束
        for (int i = 0; i < num.size(); ++i) {  // 第二趟：逐位校验声明是否与实际计数一致
            if (cnt[i] != num[i] - '0') {  // 数字 i 的真实出现次数与第 i 位声明的次数不一致
                return false;  // 发现不一致立即返回假
            }  // 判断分支结束
        }  // 校验循环结束
        return true;  // 全部位置都一致，返回真
    }  // 方法结束
};  // 类定义结束