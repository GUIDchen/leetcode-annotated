// 题目：1894. 找到需要补充粉笔的学生编号（Find the Student that Will Replace the Chalk）
// 思路：一轮消耗的粉笔总数固定，先把 k 对一轮总和取模跳过整数轮，再从头逐个扣减，第一个扣不动的人就是答案。
// 时间复杂度：O(n)，取模加一次线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int chalkReplacer(vector<int>& chalk, int k) {  // chalk：每位学生消耗的粉笔数；k：初始粉笔总数，返回需要补充粉笔的学生下标
        long long s = accumulate(chalk.begin(), chalk.end(), 0LL);  // 一轮消耗总数；用 0LL 作初值让 accumulate 按 long long 累加，防止溢出
        k %= s;  // 整轮会被反复执行，先取模跳过这些完整轮次
        for (int i = 0;; ++i) {  // 题目保证一定有人需要补充粉笔，所以循环上界可以省略
            if (k < chalk[i]) {  // 剩下的粉笔不够第 i 位学生使用，他就是答案
                return i;  // 返回该学生的下标
            }  // 结束判断
            k -= chalk[i];  // 粉笔够用就扣掉，继续下一位
        }  // 靠 return 退出，循环体正常结束
    }  // 方法结束
};  // 类定义结束