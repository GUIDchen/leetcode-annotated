// 题目：313. 超级丑数（Super Ugly Number）
// 思路：小根堆逐个生成丑数：每次弹出最小值，再乘以各质数入堆；利用「x 能被 k 整除就 break」去重。
// 时间复杂度：O(n·p·log(np))，p 为质数个数；空间复杂度：O(np)，堆可能存放的候选数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int nthSuperUglyNumber(int n, vector<int>& primes) {  // n：要找第 n 个超级丑数；primes：给定的质数集合
        priority_queue<int, vector<int>, greater<int>> q;  // 小根堆：每次取出当前最小的候选丑数（greater 让它变成小根堆）
        q.push(1);  // 1 是第一个超级丑数，作为起点
        int x = 0;  // 保存每次弹出的丑数，循环结束时它就是答案
        while (n--) {  // 循环 n 次，第 n 次弹出的堆顶就是答案
            x = q.top();  // 取出当前最小的丑数
            q.pop();  // 把它从堆中弹出
            for (int& k : primes) {  // 用每个质数分别生成新丑数
                if (x <= INT_MAX / k) {  // 用除法判断，避免 k * x 溢出 int
                    q.push(k * x);  // 生成新丑数并入堆
                }  // 提前判断：x 能被当前质数整除
                if (x % k == 0) {  // 说明更小的质数已覆盖后续生成，继续乘会产生重复
                    break;  // 跳出内层循环，减少冗余入堆
                }
            }
        }
        return x;  // 第 n 次弹出的值就是答案
    }
};