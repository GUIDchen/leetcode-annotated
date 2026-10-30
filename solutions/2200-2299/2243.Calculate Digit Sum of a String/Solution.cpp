// 题目：2243. 计算字符串的数字和（Calculate Digit Sum of a String）
// 思路：只要串长大于 k 就模拟一轮：每 k 个字符切一组，组内求和后转成字符串拼起来，直到串长不超过 k。
// 时间复杂度：O(n log n)，每轮长度至少缩短到约 n/3，总体呈几何级数；空间复杂度：O(n)，用于存放新串。
class Solution {  // LeetCode 约定的题解类
public:  // 对外提供的解法接口
    string digitSum(string s, int k) {  // s 是数字串，k 是每组的字符个数
        while (s.size() > k) {  // 长度不超过 k 时不再需要分组，循环结束
            string t;  // t 存放本轮各组求和后拼出的新数字串
            int n = s.size();  // 缓存当前串长度，后面判断最后一组边界时要用
            for (int i = 0; i < n; i += k) {  // 每 k 个字符划为一组，i 是组首下标
                int x = 0;  // 本组各位数字之和
                for (int j = i; j < min(i + k, n); ++j) {  // 组内逐个字符求和，最后一组可能不足 k 个
                    x += s[j] - '0';  // 字符转数字：减去字符 '0' 的编码即可得到 0~9
                }
                t += to_string(x);  // 把本组的和转成字符串接到新串末尾
            }
            s = t;  // 用新串替换旧串，进入下一轮
        }
        return s;  // 返回最终的数字串
    }
};