// 题目：2553. 分割数组中数字的数位（Separate the Digits in an Array）
// 思路：逐个数字取最低位压入临时数组（得到逆序数位），再逆序弹出追加到答案，从而恢复高位在前的顺序。
// 时间复杂度：O(总位数)，每个数位只入栈出栈各一次；空间复杂度：O(总位数)，ans 存放全部数位，t 最多存放单个数字的位数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> separateDigits(vector<int>& nums) {  // nums 是输入数组，返回把所有数字按原顺序拆开后的数位数组
        vector<int> ans;  // ans 收集最终结果
        for (int x : nums) {  // 依次处理每个数字（x 是 range-for 的拷贝，可以随意修改）
            vector<int> t;  // t 暂存当前数字的数位，顺序是从低位到高位
            for (; x; x /= 10) {  // 初始化表达式留空以复用 x；每轮除以 10，x 为 0 时结束
                t.push_back(x % 10);  // 取出最低位，压入 t
            }  // 当前数字的数位已全部取出，此时 t 中是逆序的
            while (t.size()) {  // t 非空就继续，从尾部弹出即可得到高位在前
                ans.push_back(t.back());  // 取 t 的末尾元素（当前最高位），追加到答案
                t.pop_back();  // 弹出已用掉的元素
            }  // 当前数字处理完毕
        }  // 所有数字处理完毕
        return ans;  // 返回拆好的数位数组
    }  // separateDigits 方法结束
};  // Solution 类定义结束