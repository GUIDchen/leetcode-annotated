// 题目：414. 第三大的数（Third Maximum Number）
// 思路：用 m1、m2、m3 维护前三大且互不相同的数，遇到新数按大小落到对应位置；不足三个就返回最大值。
// 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，只用三个滚动变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int thirdMax(vector<int>& nums) {  // 返回不同值中第三大的数，不足三个则返回最大值
        long m1 = LONG_MIN, m2 = LONG_MIN, m3 = LONG_MIN;  // 用 long 初始化，避免与取值恰好为 INT_MIN 的元素混淆；三者分别是第一大、第二大、第三大
        for (int num : nums) {  // 遍历数组中的每个数
            if (num == m1 || num == m2 || num == m3) continue;  // 与已记录的值重复就直接跳过，保证三个数严格不同
            if (num > m1) {  // 比最大值还大：三者整体下移
                m3 = m2;  // 原第二大降为第三大
                m2 = m1;  // 原最大降为第二大
                m1 = num;  // 新数成为最大值
            } else if (num > m2) {  // 落在最大值与第二大之间
                m3 = m2;  // 原第二大降为第三大
                m2 = num;  // 新数成为第二大
            } else if (num > m3) {  // 落在第二大与第三大之间
                m3 = num;  // 新数成为第三大
            }  // 大小分支结束
        }  // 遍历结束
        return (int) (m3 != LONG_MIN ? m3 : m1);  // 存在第三大就返回它，否则按题意返回最大值（先转回 int）
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）