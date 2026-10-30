// 题目：3091. 执行操作使数据元素之和大于等于 K（Apply Operations to Make Sum of Array Greater Than or Equal to k）
// 思路：最终数组一定是同一个值 x 重复 c 份；枚举「增大」次数 a（x = a + 1），再用向上取整除法算出复制次数 b，取 a + b 的最小值。
// 时间复杂度：O(k)，枚举 x 从 1 到 k；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(int k) {  // k 是目标总和
        int ans = k;  // 答案初值取宽松上界 k（把 1 增大到 k 需要 k-1 次，循环内会被压到最小值）
        for (int a = 0; a < k; ++a) {  // 枚举「增大」操作的次数 a，取值范围 0..k-1
            int x = a + 1;  // 从 1 增大 a 次后得到的基准值
            int b = (k + x - 1) / x - 1;  // 向上取整除法：还需要复制出多少个 x 才能让总和 >= k
            ans = min(ans, a + b);  // 总操作数 = 增大次数 + 复制次数，取更小的
        }
        return ans;  // 返回最少操作次数
    }
};