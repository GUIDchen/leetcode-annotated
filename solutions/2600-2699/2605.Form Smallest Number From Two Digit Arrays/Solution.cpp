// 题目：2605. 从两个数字数组里生成最小数字（Form Smallest Number From Two Digit Arrays）
// 思路：枚举所有数字对；有公共数字时答案是一位数（取最小公共数字），否则在 a*10+b 与 b*10+a 中取较小者。
// 时间复杂度：O(n·m)，枚举全部数字对；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int minNumber(vector<int>& nums1, vector<int>& nums2) {  // nums1/nums2：两个数字数组；返回能组成的最小数字
        int ans = 100;  // 初始上界 100，比任何两位数都大，便于不断取 min
        for (int a : nums1) {  // 枚举 nums1 中的数字 a
            for (int b : nums2) {  // 枚举 nums2 中的数字 b
                if (a == b) {  // 两个数组有公共数字，可以只取一位
                    ans = min(ans, a);  // 一位数时在已有答案与 a 之间取更小者
                } else {  // 没有公共数字，只能拼成两位数
                    ans = min({ans, a * 10 + b, b * 10 + a});  // 两种拼接顺序 a-b、b-a 中取较小者，再与当前答案比较
                }
            }
        }
        return ans;  // 返回找到的最小数字
    }
};