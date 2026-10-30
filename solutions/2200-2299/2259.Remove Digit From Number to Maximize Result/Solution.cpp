// 题目：2259. 移除指定数字得到的最大结果（Remove Digit From Number to Maximize Result）
// 思路：枚举每一个等于 digit 的位置，删掉该位拼出候选串，取字典序最大者；长度相同，字典序最大即数值最大。
// 时间复杂度：O(n^2)，每次拼接与比较都要复制长度为 n 的串；空间复杂度：O(n)，用于保存候选项与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeDigit(string number, char digit) {  // number：十进制数字串；digit：必须删掉一位的那个数字字符
        string ans = "0";  // 保存当前最优结果，初值取最小的 "0"（题目保证 number 中至少含一个 digit）
        for (int i = 0, n = number.size(); i < n; ++i) {  // 枚举每一位，n 顺便缓存串长避免重复求值
            char d = number[i];  // 当前位上的字符
            if (d == digit) {  // 只有等于 digit 的位置才允许删除
                string t = number.substr(0, i) + number.substr(i + 1, n - i);  // 拼接「i 之前」与「i 之后」两段得到删除后的串（第二段长度写大了会被自动裁到串尾）
                if (ans < t) {  // 等长字符串的字典序比较等价于数值比较，候选更大才更新
                    ans = t;  // 记录这个更优的候选
                }
            }
        }
        return ans;  // 返回字典序（即数值）最大的结果
    }
};