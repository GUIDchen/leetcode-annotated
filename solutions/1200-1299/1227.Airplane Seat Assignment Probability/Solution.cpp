// 题目：1227. 飞机座位分配概率（Airplane Seat Assignment Probability）
// 思路：第一位乘客随机坐，第 n 位乘客的座位要么早被占、要么恰好留到最后，两种结局等概率，因此 n ≥ 2 时答案恒为 1/2。
// 时间复杂度：O(1)，只做一次比较；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    double nthPersonGetsNthSeat(int n) {  // n：乘客（座位）总数，返回第 n 位乘客坐到自己座位的概率
        return n == 1 ? 1 : .5;  // n 为 1 时必定坐对，概率为 1；否则由对称性答案恒为 0.5
    }  // 方法结束
};  // 类定义结束