// 题目：1742. 盒子中小球的最大数量（Maximum Number of Balls in a Box）
// 思路：小球编号的数位和就是它要放的盒子编号，用桶数组统计每个盒子的球数，边统计边记录最大值。
// 时间复杂度：O((highLimit-lowLimit+1)*log highLimit)，每个数只拆它的十进制位；空间复杂度：O(1)，桶数组固定 50 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countBalls(int lowLimit, int highLimit) {  // 统计编号区间内小球放入盒子后的最大球数
        int cnt[50] = {0};  // 桶数组：下标是数位和（即盒子编号），值是该盒子里的球数；最大数位和 9*5=45，50 足够
        int ans = 0;  // 记录所有盒子中的最大球数
        for (int i = lowLimit; i <= highLimit; ++i) {  // 逐个处理编号为 i 的小球
            int y = 0;  // y 用来累加 i 的十进制数位和
            for (int x = i; x; x /= 10) {  // 用副本 x 反复取末位，每次整体右移一位，x 为 0 时结束
                y += x % 10;  // 取出当前最低位并累加到数位和
            }
            ans = max(ans, ++cnt[y]);  // 该盒子球数先自增，再和历史最大值比较取较大者
        }
        return ans;  // 返回球数最多的那个盒子的球数
    }
};