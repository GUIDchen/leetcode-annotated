// 题目：3100. 换水问题 II（Water Bottles II）
// 思路：直接模拟兑换过程，每换一次所需空瓶数加一，直到空瓶数少于当前兑换门槛为止。
// 时间复杂度：O(√numBottles)，兑换次数 t 满足 t(t+1)/2 ≤ numBottles；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxBottlesDrunk(int numBottles, int numExchange) {  // numBottles：初始满瓶数；numExchange：当前兑换一瓶所需空瓶数
        int ans = numBottles;  // 累计喝掉的瓶数，先把初始满瓶全部计入
        while (numBottles >= numExchange) {  // 空瓶数够兑换就继续换
            numBottles -= numExchange;  // 交出 numExchange 个空瓶用于兑换，空瓶数相应减少
            ++numExchange;  // 每完成一次兑换，下一次所需空瓶数加一
            ++ans;  // 换来的这瓶也喝掉，答案加一
            ++numBottles;  // 喝完后又多出一个空瓶
        }  // 结束模拟循环
        return ans;  // 返回总共喝掉的瓶数
    }  // 结束题解方法
};  // 结束题解类