// 题目：1946. 子字符串突变后可能得到的最大整数（Largest Number After Mutating Substring）
// 思路：从左到右贪心，只在能把数字变大的连续区间内替换；一旦已开始替换又遇到会变小的位就立即停止，保证只突变一个子串。
// 时间复杂度：O(n)，只需一次线性扫描；空间复杂度：O(1)，除返回值外只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string maximumNumber(string num, vector<int>& change) {  // num：数字字符串；change：0~9 每个数字替换后的值
        int n = num.size();  // 记录数字串长度，供循环使用
        bool changed = false;  // 标记是否已经进入「正在突变的子串」
        for (int i = 0; i < n; ++i) {  // 从左到右逐位考察
            char d = '0' + change[num[i] - '0'];  // num[i]-'0' 得到数字，查表后加 '0' 转回字符
            if (changed && d < num[i]) {  // 已在替换中且这一位替换后会变小，说明突变子串该在此结束
                break;  // 再往后替换只会让结果更小，立即停止
            }
            if (d > num[i]) {  // 替换后变大，属于值得突变的位置
                changed = true;  // 从这一位开始进入突变区间
                num[i] = d;  // 真正完成这一位的替换
            }
        }
        return num;  // 返回突变后能得到的最大数字串
    }
};
