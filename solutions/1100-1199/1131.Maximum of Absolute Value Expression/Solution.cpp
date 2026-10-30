// 题目：1131. 绝对值表达式的最大值（Maximum of Absolute Value Expression）
// 思路：把 |a1[i]-a1[j]| + |a2[i]-a2[j]| + |i-j| 展开成四种符号组合下 (a*a1 + b*a2 + i) 之差，符号取遍 (1,-1)、(-1,-1)、(-1,1)、(1,1)；每种组合只需维护表达式的最大值与最小值，其差就是该组合下的最大结果。
// 时间复杂度：O(n)，四种符号组合各扫一遍，常数因子为 4；空间复杂度 O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {  // arr1、arr2：两个等长数组；返回绝对值表达式的最大值
        int dirs[5] = {1, -1, -1, 1, 1};  // 四种符号组合 (1,-1)、(-1,-1)、(-1,1)、(1,1)，用相邻两项配对得到
        const int inf = 1 << 30;  // inf：足够大的数，用于初始化极值
        int ans = -inf;  // ans 初始为负无穷
        int n = arr1.size();  // n：数组长度
        for (int k = 0; k < 4; ++k) {  // 枚举四种符号组合
            int a = dirs[k], b = dirs[k + 1];  // 取出当前组合的两个符号 a、b
            int mx = -inf, mi = inf;  // mx/mi 分别记录该组合表达式的最大值与最小值
            for (int i = 0; i < n; ++i) {  // 枚举每个下标 i
                mx = max(mx, a * arr1[i] + b * arr2[i] + i);  // 更新该组合表达式的最大值
                mi = min(mi, a * arr1[i] + b * arr2[i] + i);  // 更新该组合表达式的最小值
                ans = max(ans, mx - mi);  // 最大值减最小值即为该组合下的最大结果
            }  // 下标循环结束
        }  // 符号组合循环结束
        return ans;  // 返回四种组合中的最大结果
    }  // 方法结束
};  // 类定义结束