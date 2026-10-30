// 题目：2979. 最贵的无法购买的商品（Most Expensive Item That Can Not Be Bought）
// 思路：麦乐鸡定理（Frobenius 数）：两个互质的正整数 a、b，不能用 ax+by（x,y≥0）表示的最大整数恰为 a*b-a-b；题目保证 primeOne、primeTwo 为质数因而互质，直接套公式。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mostExpensiveItem(int primeOne, int primeTwo) {  // primeOne、primeTwo 为两个不同的质数，互质是公式成立的前提
        return primeOne * primeTwo - primeOne - primeTwo;  // 直接返回 a*b-a-b：这是只用这两种商品时最大的不可表示价格
    }  // 方法结束
};  // 类定义结束