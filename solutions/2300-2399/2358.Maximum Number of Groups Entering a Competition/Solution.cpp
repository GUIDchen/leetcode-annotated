// 题目：2358. 分组的最大数量（Maximum Number of Groups Entering a Competition）
// 思路：成绩不影响答案，只需凑人数；g 组至少需要 1+2+...+g 人，对 g 二分答案。
// 时间复杂度：O(log n)，二分的区间长度是 n；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumGroups(vector<int>& grades) {  // grades：学生成绩数组；返回最多可以分成的组数
        int n = grades.size();  // n 为学生总数，分组只看人数，成绩本身不参与计算
        int l = 0, r = n;  // 二分答案的区间：组数最少 0 组，最多 n 组
        while (l < r) {  // 在 [l, r] 中二分最大的可行组数
            int mid = (l + r + 1) >> 1;  // 取上中位数，与下面 l = mid 的收缩方式配合，避免区间卡死
            if (1LL * mid * mid + mid > n * 2LL) {  // mid 组至少需要 1+2+...+mid = mid*(mid+1)/2 人；乘 2 并转 long long 防止溢出
                r = mid - 1;  // 人数不够，mid 组不可行，答案缩小到 mid-1
            } else {  // mid 组所需人数没有超过 n
                l = mid;  // mid 可行，保留 mid 并继续向右尝试更大的组数
            }  // 可行性分支结束
        }  // 二分结束，l == r 即为答案
        return l;  // l 是人数约束下能凑出的最大组数
    }  // 方法结束
};  // 类定义结束